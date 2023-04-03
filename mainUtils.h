#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <immintrin.h>

//=============================================
typedef unsigned DWORD;
typedef unsigned short WORD;
typedef long LONG ;
//=============================================

struct
{
    int width  = 800;
    int height = 600;
} Init;

#pragma pack(push, 1)

struct BITMAPFILEHEADER
{
    WORD bfType;  //specifies the file type
    DWORD bfSize;  //specifies the size in bytes of the bitmap file
    WORD bfReserved1;  //reserved; must be 0
    WORD bfReserved2;  //reserved; must be 0
    DWORD bfOffBits;  //specifies the offset in bytes from the bitmapfileheader to the bitmap bits
};

#pragma pack(pop)

#pragma pack(push, 1)

struct BITMAPINFOHEADER
{
    DWORD biSize;  //specifies the number of bytes required by the struct
    LONG biWidth;  //specifies width in pixels
    LONG biHeight;  //specifies height in pixels
    WORD biPlanes;  //specifies the number of color planes, must be 1
    WORD biBitCount;  //specifies the number of bits per pixel
    DWORD biCompression;  //specifies the type of compression
    DWORD biSizeImage;  //size of image in bytes
    LONG biXPelsPerMeter;  //number of pixels per meter in x axis
    LONG biYPelsPerMeter;  //number of pixels per meter in y axis
    DWORD biClrUsed;  //number of colors used by the bitmap
    DWORD biClrImportant;  //number of colors that are important
};

#pragma pack(pop)


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
    Pixel* imgBuff;
    BITMAPINFOHEADER* infoHeader;
    BITMAPFILEHEADER* fileHeader;
};


Img* LoadBitmapFile(char* filename);
void AlphaBlend (Img* front, Img* back, int x_pos, int y_pos);
unsigned char getColor (unsigned char frClr, unsigned char frAlp, unsigned char bkClr);
void saveBmpFile (char* fileName, Img* img);
