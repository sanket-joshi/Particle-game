#include "utils.h"
#include <cmath>
#include<stdlib.h>//for random numbers

SDL_Surface* scr;
Uint8* keyState;
int w, h;
SDL_Event event = {0};

ColorRGB::ColorRGB(Uint8 r, Uint8 g, Uint8 b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

ColorRGB::ColorRGB()
{
}

void screen(int width, int height)
{
    int colorDepth = 32;
    w = width;
    h = height;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    scr = SDL_SetVideoMode(width, height, colorDepth, SDL_HWSURFACE | SDL_HWPALETTE);

    if(scr == NULL)
    {
        printf("Unable to set video: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    SDL_WM_SetCaption("Final project", NULL);

    SDL_EnableUNICODE(1); //for the text input things
}

//Clears the screen to white
void cls(const ColorRGB& color)
{
    SDL_FillRect(scr, NULL, 65536 * color.r + 256 * color.g + color.b);
}

void blur()
{
    for(int x=0; x<25; x++)
    {
        drawLine(randInt(0,w-1), randInt(0,h-1),randInt(0,w-1), randInt(0,h-1),ColorRGB(0,0,0));
    }
}

//Puts an RGB color pixel at position x,y
void pset(int x, int y, const ColorRGB& color)
{
    if(x < 0 || y < 0 || x >= w || y >= h) return;
    Uint32 colorSDL = SDL_MapRGB(scr->format, color.r, color.g, color.b);
    Uint32* bufp;
    bufp = (Uint32*)scr->pixels + y * scr->pitch / 4 + x;
    *bufp = colorSDL;
}

// line from (x1,y1) to (x2,y2) with rgb color
bool drawLine(int x1, int y1, int x2, int y2, const ColorRGB& color)
{
    if(x1 < 0 || x1 > w - 1 || x2 < 0 || x2 > w - 1 || y1 < 0 || y1 > h - 1 || y2 < 0 || y2 > h - 1) return 0;

    int deltax = std::fabs(x2 - x1); //The difference between the x's
    int deltay = std::fabs(y2 - y1); //The difference between the y's
    int x = x1; //Start x off at the first pixel
    int y = y1; //Start y off at the first pixel
    int xinc1, xinc2, yinc1, yinc2, den, num, numadd, numpixels, curpixel;

    if(x2 >= x1) //The x-values are increasing
    {
        xinc1 = 1;
        xinc2 = 1;
    }
    else //The x-values are decreasing
    {
        xinc1 = -1;
        xinc2 = -1;
    }
    if(y2 >= y1) //The y-values are increasing
    {
        yinc1 = 1;
        yinc2 = 1;
    }
    else //The y-values are decreasing
    {
        yinc1 = -1;
        yinc2 = -1;
    }
    if (deltax >= deltay) //There is at least one x-value for every y-value
    {
        xinc1 = 0; //Don't change the x when numerator >= denominator
        yinc2 = 0; //Don't change the y for every iteration
        den = deltax;
        num = deltax / 2;
        numadd = deltay;
        numpixels = deltax; //There are more x-values than y-values
    }
    else //There is at least one y-value for every x-value
    {
        xinc2 = 0; //Don't change the x for every iteration
        yinc1 = 0; //Don't change the y when numerator >= denominator
        den = deltay;
        num = deltay / 2;
        numadd = deltax;
        numpixels = deltay; //There are more y-values than x-values
    }
    for (curpixel = 0; curpixel <= numpixels; curpixel++)
    {
        pset(x % w, y % h, color);  //Draw the current pixel
        num += numadd;  //Increase the numerator by the top of the fraction
        if (num >= den) //Check if numerator >= denominator
        {
            num -= den; //Calculate the new numerator value
            x += xinc1; //Change the x as appropriate
            y += yinc1; //Change the y as appropriate
        }
        x += xinc2; //Change the x as appropriate
        y += yinc2; //Change the y as appropriate
    }

    return 1;
}

//Fast horizontal line from (x1,y) to (x2,y), with rgb color
bool horLine(int y, int x1, int x2, const ColorRGB& color)
{
    if(x2 < x1)
    {
        x1 += x2;    //swap x1 and x2, x1 must be the leftmost endpoint
        x2 = x1 - x2;
        x1 -= x2;
    }
    if(x2 < 0 || x1 >= w || y < 0 || y >= h) return 0; //no single point of the line is on screen
    if(x1 < 0) x1 = 0; //clip
    if(x2 >= w) x2 = w - 1; //clip

    Uint32 colorSDL = SDL_MapRGB(scr->format, color.r, color.g, color.b);
    Uint32* bufp;
    bufp = (Uint32*)scr->pixels + y * scr->pitch / 4 + x1;
    for(int x = x1; x <= x2; x++)
    {
        *bufp = colorSDL;
        bufp++;
    }
    return 1;
}

//Filled  circle with center at (xc,yc) with radius and red green blue color
bool drawDisk(int xc, int yc, int radius, const ColorRGB& color)
{
    if(xc + radius < 0 || xc - radius >= w || yc + radius < 0 || yc - radius >= h) return 0; //every single pixel outside screen, so don't waste time on it
    int x = 0;
    int y = radius;
    int p = 3 - (radius << 1);
    int a, b, c, d, e, f, g, h;
    int pb = yc + radius + 1, pd = yc + radius + 1; //previous values: to avoid drawing horizontal lines multiple times  (ensure initial value is outside the range)
    while (x <= y)
    {
        // write data
        a = xc + x;
        b = yc + y;
        c = xc - x;
        d = yc - y;
        e = xc + y;
        f = yc + x;
        g = xc - y;
        h = yc - x;
        if(b != pb) horLine(b, a, c, color);
        if(d != pd) horLine(d, a, c, color);
        if(f != b)  horLine(f, e, g, color);
        if(h != d && h != f) horLine(h, e, g, color);
        pb = b;
        pd = d;
        if(p < 0) p += (x++ << 2) + 6;
        else p += ((x++ - y--) << 2) + 10;
    }

    return 1;
}

void update()
{
    while (SDL_PollEvent(&event));
    keyState = SDL_GetKeyState(NULL);
    SDL_Flip(scr);
}

void getMouseState(int& mouseX, int& mouseY, bool& LMB, bool& MMB, bool& RMB)
{
    Uint8 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if(mouseState & SDL_BUTTON(1)) LMB = true;
    else LMB = false;
    if(mouseState & SDL_BUTTON(2)) MMB = true;
    else MMB = false;
    if(mouseState & SDL_BUTTON(3)) RMB = true;
    else RMB = false;
}

bool keyDown(int k)
{
    return (keyState[k] != 0);
}

float randFloat(float min,float max)
{
    if (min==max)
        return min;
    return ( (float)(rand()%(int)(max-min+1)+min) +
             ((float)rand() / ((float)RAND_MAX + 1)));
}

int randInt(int min,int max)
{
    return  (rand()%(int)(max-min+1)+min);
}
