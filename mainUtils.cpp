#include "mainUtils.h"
#include <SFML/Config.hpp>
#include <SFML/System/Clock.hpp>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <emmintrin.h>
#include <emmintrin.h>
#include <smmintrin.h>
#include <tmmintrin.h>
#include <xmmintrin.h>
#include "string.h"
#define zero 0xFF

void imgCtor(char* filename, Img* img)
{
    img->image.loadFromFile(filename);
    img->height = img->image.getSize().y;
    img->width  = img->image.getSize().x;
    img->pixels = (unsigned int*) img->image.getPixelsPtr();
}

#ifndef SSE

void AlphaBlend (Img* front, Img* back, int x_pos, int y_pos)
{
    sf::Clock clock;

    for (int y = 0; y < front->height; y++)
    {
        for (int x = 0; x < front->width; x++)
        {
            volatile unsigned int backPixel  =  back->pixels[(y_pos + y) * back->width + x_pos + x];
            volatile unsigned int frontPixel = front->pixels[y * front->width + x];

            volatile unsigned char frontAlpha = frontPixel >> 24;
            volatile unsigned char backAlpha  = backPixel >> 24;

            volatile unsigned int newColor =  backAlpha << 24;

            for (int idx = 0; idx < 17; idx += 8)
            {

                unsigned char frontColor = ((0xFF << idx) & frontPixel) >> idx;
                unsigned char backColor  = ((0xFF << idx) & backPixel) >> idx;

                newColor += getColor(frontColor, frontAlpha, backColor) << idx;
            }

            back->pixels[(y_pos + y) * back->width + x_pos + x] = newColor;
        }

    }
    sf::Time elapsed = clock.restart();
    printf ("FPS %f\n", 1 / elapsed.asSeconds());

    back->image.create(back->width, back->height, (sf::Uint8*) back->pixels);
}
#else


void AlphaBlend(Img *front, Img *back, int x_pos, int y_pos)
{
    __m128i Zeros = _mm_set1_epi8(0);
    __m128i _255  = _mm_set1_epi16(255);
    sf::Clock clock;

    for (int y = 0; y < front->height; y++)
    {
        for (int x = 0; x < front->width; x+=4)
        {
            CalculateAndStoreSSE (front, back, x_pos, y_pos, x, y, Zeros, _255);
        }

    }
    sf::Time elapsed = clock.restart();
    printf ("FPS %f\n", 1/elapsed.asSeconds());

    back->image.create(back->width, back->height, (sf::Uint8*) back->pixels);
}

#endif


inline void CalculateAndStoreSSE (Img* front, Img* back, int x_pos, int y_pos, int x, int y, __m128i Zeros, __m128i _255)
{
        __m128i frontLow = _mm_load_si128 ((__m128i const*) &(front->pixels[y * front->width + x]));
        __m128i backLow  = _mm_load_si128 ((__m128i const*) &( back->pixels[(y_pos + y) * back->width + x_pos + x]));

        __m128i frontHigh = (__m128i) _mm_movehl_ps((__m128) Zeros, (__m128) frontLow);
        __m128i  backHigh = (__m128i) _mm_movehl_ps((__m128) Zeros, (__m128) backLow);

        frontLow  = _mm_cvtepi8_epi16 (frontLow);
        backLow   = _mm_cvtepi8_epi16 (backLow);
        frontHigh = _mm_cvtepi8_epi16 (frontHigh);
        backHigh  = _mm_cvtepi8_epi16 (backHigh);

        __m128i moveAlpha = _mm_set_epi8 (zero, 14, zero, 14, zero, 14, zero, 14,
                                          zero,  6, zero,  6, zero,  6, zero,  6);

        __m128i alphaLow  = _mm_shuffle_epi8 (frontLow,  moveAlpha);
        __m128i alphaHigh = _mm_shuffle_epi8 (frontHigh, moveAlpha);

        frontLow  = _mm_mullo_epi16 (frontLow,  alphaLow);
        frontHigh = _mm_mullo_epi16 (frontHigh, alphaHigh);
        backLow   = _mm_mullo_epi16 (backLow,  _mm_sub_epi16(_255, alphaLow));
        backHigh  = _mm_mullo_epi16 (backHigh, _mm_sub_epi16(_255, alphaHigh));

        __m128i sumLow  = _mm_add_epi16 (frontLow, backLow);
        __m128i sumHigh = _mm_add_epi16 (frontHigh, backHigh);

        __m128i moveSum = _mm_set_epi8 (zero, zero, zero, zero, zero, zero, zero, zero,
                                        15,   13,   11,   9,    7,    5,    3,    1);

        sumLow  = _mm_shuffle_epi8 (sumLow,  moveSum);
        sumHigh = _mm_shuffle_epi8 (sumHigh, moveSum);

        __m128i fourPixels = (__m128i) _mm_movelh_ps ((__m128) sumLow, (__m128) sumHigh);

        _mm_store_si128 ((__m128i*) &(back->pixels[(y_pos + y) * back->width + x_pos + x]), fourPixels) ;
}

unsigned char getColor (unsigned char frontClr, unsigned char frontAlpha, unsigned char backClr)
{
    return ((unsigned short) frontClr * frontAlpha + (unsigned short) backClr * (255 - frontAlpha))/255;
}
