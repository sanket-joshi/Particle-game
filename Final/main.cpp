/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "utils.h"
#include "particle.h"
#include <iostream>
using namespace std;

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;
    initSystem();

    //Initialize
    screen();
    cls();
    int x,y;
    bool lft,rgt,mdl;

    //While the user hasn't quit
    while( quit == false )
    {
        //While there's events to handle
        update();

        //Show the dot on the screen
        blur();
        getMouseState(x,y,lft,mdl,rgt);
        setHead(x,y);
        updateSystem();
        if (lft) {
            initSystem();
        }

    }

    return 0;
}

