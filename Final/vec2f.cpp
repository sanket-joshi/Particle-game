#include "vec2f.h"
#include <math.h>
#include <iostream>

using namespace std;

vec2f::vec2f()
{

}

vec2f::vec2f(float x, float y)
{
    v[0] = x;
    v[1] = y;
}

float &vec2f::operator[](int index)
{
    return v[index];
}

float vec2f::operator[](int index) const
{
    return v[index];
}

vec2f vec2f::operator*(float scale) const
{
    return vec2f(v[0] * scale, v[1] * scale);
}

vec2f vec2f::operator/(float scale) const
{
    return vec2f(v[0] / scale, v[1] / scale);
}

vec2f vec2f::operator+(const vec2f &other) const
{
    return vec2f(v[0] + other.v[0], v[1] + other.v[1]);
}

vec2f vec2f::operator-(const vec2f &other) const
{
    return vec2f(v[0] - other.v[0], v[1] - other.v[1]);
}

vec2f vec2f::operator-() const
{
    return vec2f(-v[0], -v[1]);
}

const vec2f &vec2f::operator*=(float scale)
{
    v[0] *= scale;
    v[1] *= scale;
    return *this;
}

const vec2f &vec2f::operator/=(float scale)
{
    v[0] /= scale;
    v[1] /= scale;
    return *this;
}

const vec2f &vec2f::operator+=(const vec2f &other)
{
    v[0] += other.v[0];
    v[1] += other.v[1];
    return *this;
}

const vec2f &vec2f::operator-=(const vec2f &other)
{
    v[0] -= other.v[0];
    v[1] -= other.v[1];
    return *this;
}

float vec2f::magnitude() const
{
    return sqrt(v[0] * v[0] + v[1] * v[1]);
}

float vec2f::magnitudeSquared() const
{
    return v[0] * v[0] + v[1] * v[1];
}

vec2f vec2f::normalize() const
{
    float m = sqrt(v[0] * v[0] + v[1] * v[1]);
    return vec2f(v[0] / m, v[1] / m);
}

float vec2f::dot(const vec2f &other) const
{
    return v[0] * other.v[0] + v[1] * other.v[1];
}

vec2f vec2f::perp() const
{
    return vec2f(v[1], -v[0]);
}

vec2f operator*(float scale, const vec2f &v)
{
    return v * scale;
}

ostream &operator<<(ostream &output, const vec2f &v)
{
    cout << '(' << v[0] << ", " << v[1] << ')';
    return output;
}
static const double DEG_TO_RAD=57.29578;
double getAngle(vec2f v1, vec2f v2)
   {
    double x1=v1[0], y1=v1[1];
    double x2=v2[0], y2=v2[1];
    double opp = y2 - y1;
    double adj = x2 - x1;
    if (adj == 0)
        if (y2 > y1)
            return 270;
        else
            return 90;
    else if (opp >= 0 && adj > 0)
        return 360 - atan  (opp / adj)*DEG_TO_RAD;
    else if (adj < 0)
        return 180-atan  (opp / adj)*DEG_TO_RAD;
    else if (opp < 0 && adj > 0)
        return 360-atan  (opp / adj)*DEG_TO_RAD;
    return 0;
}
