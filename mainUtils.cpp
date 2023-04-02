#include "mainUtils.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <tuple>

Img* LoadBitmapFile(char* filename)
{
    BITMAPFILEHEADER bmpFileHeader = {};
    BITMAPINFOHEADER bmpInfoHeader = {};


    FILE *fileptr = fopen(filename, "rb");
    assert (fileptr != nullptr);

    fread(&bmpFileHeader, sizeof(bmpFileHeader), 1, fileptr);

    if (bmpFileHeader.bfType !=0x4D42)
    {
        fclose(fileptr);
        return NULL;
    }

    fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fileptr);

    fseek(fileptr, bmpFileHeader.bfOffBits, SEEK_SET);

    unsigned char* bmpImg = (unsigned char*)malloc(bmpInfoHeader.biSizeImage);
    assert(bmpImg != nullptr);

    fread(bmpImg, bmpInfoHeader.biSizeImage, 1, fileptr);
    assert (bmpImg != nullptr);

    fclose(fileptr);

    Img* imgInf  = (Img*) calloc(1, sizeof(*imgInf));
    imgInf->width   = bmpInfoHeader.biWidth;
    imgInf->height  = bmpInfoHeader.biHeight;
    imgInf->imgBuff = (Pixel*) bmpImg;

    return imgInf;
}

void AlphaBlend (Img* front, Img* back, int x_pos, int y_pos)
{


    for (int y = 0; y < front->height; y++)
    {
        for (int x = 0; x < front->width; x++)
        {
            Pixel bkPixel = back->imgBuff[(y_pos + y) * back->width + x_pos + x];
            Pixel frPixel = front->imgBuff[y * front->width + x];

            Pixel finalPixel = {bkPixel.alpha, getColor(frPixel.red ,  frPixel.alpha, bkPixel.red),
                                               getColor(frPixel.blue,  frPixel.alpha, bkPixel.blue),
                                               getColor(frPixel.green, frPixel.alpha, bkPixel.green)};


            back->imgBuff[(y_pos + y) * back->width + x_pos + x] = finalPixel;
        }
    }
}

unsigned char getColor (unsigned char frClr, unsigned char frAlp, unsigned char bkClr)
{
    return frClr * frAlp + bkClr * (255 - frAlp);
}
