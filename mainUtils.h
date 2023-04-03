#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <immintrin.h>

//=============================================
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef long LONG ;
//=============================================

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
    Pixel* pixels;
    sf::Image image;
};


Img* LoadBitmapFile(char* filename);
void AlphaBlend (Img* front, Img* back, int x_pos, int y_pos);
unsigned char getColor (unsigned char frClr, unsigned char frAlp, unsigned char bkClr);
void imgCtor(char* filename, Img* img);
