#ifndef VEC2F_H
#define VEC2F_H

#include <ostream>
class vec2f
{
private:
    float v[2];
public:
    vec2f();
    vec2f(float x, float y);

    float &operator[](int index);
    float operator[](int index) const;

    vec2f operator*(float scale) const;
    vec2f operator/(float scale) const;
    vec2f operator+(const vec2f &other) const;
    vec2f operator-(const vec2f &other) const;
    vec2f operator-() const;

    const vec2f &operator*=(float scale);
    const vec2f &operator/=(float scale);
    const vec2f &operator+=(const vec2f &other);
    const vec2f &operator-=(const vec2f &other);
    float dot(const vec2f &other) const;
    vec2f perp() const;

    float magnitude() const;
    float magnitudeSquared() const;
    vec2f normalize() const;
};

vec2f operator*(float scale, const vec2f &v);
std::ostream &operator<<(std::ostream &output, const vec2f &v);
double getAngle(vec2f v1, vec2f v2);

#endif // VEC2F_H
