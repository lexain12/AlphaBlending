#include "mainUtils.h"
#include <SFML/Config.hpp>
#include <cassert>
#include <cstdio>
#include <cstdlib>

void imgCtor(char* filename, Img* img)
{
    img->image.loadFromFile(filename);
    img->height = img->image.getSize().y;
    img->width  = img->image.getSize().x;
    img->pixels = (Pixel*) img->image.getPixelsPtr();
}

void AlphaBlend (Img* front, Img* back, int x_pos, int y_pos)
{
    for (int y = 0; y < front->height; y++)
    {
        for (int x = 0; x < front->width; x++)
        {
            fprintf(stderr, "back %d %d\n", (y_pos + y), x_pos + x);
            fprintf(stderr, "front %d %d\n", (y), x);
            Pixel bkPixel = back->pixels[(y_pos + y) * back->width + x_pos + x];
            Pixel frPixel = front->pixels[y * front->width + x];

            Pixel finalPixel = {bkPixel.alpha, getColor(frPixel.red ,  frPixel.alpha, bkPixel.red),
                                               getColor(frPixel.blue,  frPixel.alpha, bkPixel.blue),
                                               getColor(frPixel.green, frPixel.alpha, bkPixel.green)};


            back->pixels[(y_pos + y) * back->width + x_pos + x] = finalPixel;
        }
    }

    back->image.create(back->width, back->height, (sf::Uint8*) back->pixels);
}

unsigned char getColor (unsigned char frClr, unsigned char frAlp, unsigned char bkClr)
{
    return frClr * frAlp + bkClr * (255 - frAlp);
}
