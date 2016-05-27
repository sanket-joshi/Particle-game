#ifndef PARTICLE_H
#define PARTICLE_H

#include "vec2f.h"
#include "utils.h"
class particle
{
public:
    particle();

    void drawParticle();

    vec2f pos;
    vec2f vel;
    ColorRGB col;
};

void initSystem();
void updateSystem();
void setHead(int x, int y);
#endif // PARTICLE_H
