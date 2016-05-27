#include "particle.h"
#include <math.h>
#include <iostream>

using namespace std;
static const double DEG_TO_RAD=57.29578;

particle::particle()
{
    this->pos = vec2f(randInt(0,640), randInt(0,400));//position of the particle
    this->vel = vec2f(0,0);//current velocity of the particle
    this->col = ColorRGB(randInt(0,255),randInt(0,255),randInt(0,255));//the colour of the particle
}

//draw the particle
void particle::drawParticle()
{
    drawDisk((int)pos[0], (int)pos[1], 10, col);
}
#define PP 75//there are 75 particles
particle mySystem[PP];

void initSystem()
{
    for(int i = 0; i<PP; i++)
    {
        mySystem[i] = particle();//the number of particles in the array is equal to the parameters set in the
    }
}

//update the screen and information
void updateSystem()
{
    for(int i = 1; i<PP; i++)
    {
        float dist = (mySystem[i-1].pos - mySystem[i].pos).magnitude() - 5;
		float force = 0.1*dist;
		float ang = 180 - getAngle(mySystem[i-1].pos,mySystem[i].pos);
		mySystem[i].vel[0] = force*cos(ang/DEG_TO_RAD);
		mySystem[i].vel[1] = force*sin(ang/DEG_TO_RAD);

		mySystem[i].pos += mySystem[i].vel;
		mySystem[i].drawParticle();
    }
}

void setHead(int x, int y)
{
    mySystem[0].pos = vec2f(x,y);
    mySystem[0].drawParticle();
}
