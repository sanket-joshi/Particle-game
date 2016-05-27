#ifndef UTILS_H
#define UTILS_H

#include <SDL/SDL.h>

struct ColorRGB
{
public:
    int r;
    int g;
    int b;

    ColorRGB(Uint8 r, Uint8 g, Uint8 b);
    ColorRGB();
};

void screen(int width = 640, int height = 400);
void cls(const ColorRGB& color = ColorRGB(0,0,0));

bool drawLine(int x1, int y1, int x2, int y2, const ColorRGB& color);
bool drawDisk(int xc, int yc, int radius, const ColorRGB& color);

void update();
void blur();
void getMouseState(int& x, int& y, bool& left, bool& middle, bool& right);
bool keyDown(int k);

float randFloat(float min,float max);
int randInt(int min,int max);
#endif // UTILS_H
