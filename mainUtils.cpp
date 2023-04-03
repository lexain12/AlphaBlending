#include "mainUtils.h"
#include <SFML/Config.hpp>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include "string.h"

void imgCtor(char* filename, Img* img)
{
    img->image.loadFromFile(filename);
    img->height = img->image.getSize().y;
    img->width  = img->image.getSize().x;
    img->pixels = (unsigned int*) img->image.getPixelsPtr();
}

void AlphaBlend (Img* front, Img* back, int x_pos, int y_pos)
{

    for (int y = 0; y < front->height; y++)
    {
        for (int x = 0; x < front->width; x++)
        {
            unsigned int backPixel  =  back->pixels[(y_pos + y) * back->width + x_pos + x];
            unsigned int frontPixel = front->pixels[y * front->width + x];

            unsigned char frontAlpha = frontPixel>> 24;
            unsigned char backAlpha  = backPixel>> 24;

            unsigned int newColor =  backAlpha << 24;

            for (int idx = 0; idx < 17; idx += 8)
            {

                unsigned char frontColor = ((0xFF << idx) & frontPixel) >> idx;
                unsigned char backColor  = ((0xFF << idx) & backPixel) >> idx;

                newColor += getColor(frontColor, frontAlpha, backColor) << idx;
            }

            back->pixels[(y_pos + y) * back->width + x_pos + x] = newColor;
        }

    }

    back->image.create(back->width, back->height, (sf::Uint8*) back->pixels);
}

unsigned char getColor (unsigned char frontClr, unsigned char frontAlpha, unsigned char backClr)
{
    return ((unsigned short) frontClr * frontAlpha + (unsigned short) backClr * (255 - frontAlpha))/255;
}
