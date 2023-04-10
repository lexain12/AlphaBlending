#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <immintrin.h>

struct Pixel
{
    unsigned char alpha;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

struct Img
{
    int width;
    int height;
    unsigned int* pixels;
    sf::Image image;
};

#define ShowXmmReg(Name) \
    printf ("-----" # Name  "-----\n");            \
    for (int Name##_ = 0;Name##_ < 4; ++ Name##_)\
{                                               \
    printf ("%X\n", ((unsigned int*) &Name)[Name##_]);        \
}                                               \
    printf ("----------\n");

Img* LoadBitmapFile(char* filename);
void AlphaBlend (Img* front, Img* back, int x_pos, int y_pos);
unsigned char getColor (unsigned char frClr, unsigned char frAlp, unsigned char bkClr);
void imgCtor(char* filename, Img* img);
inline void CalculateAndStoreSSE (Img* front, Img* back, int x_pos, int y_pos, int x, int y, __m128i Zeros, __m128i _255);
