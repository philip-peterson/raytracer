#include "vec2.h"
#include <cmath>

float vec2::getMagnitude() const {
   return sqrt(x*x + y*y);
}
vec2 vec2::getNormalized() const {
   return (*this) * (1.0/getMagnitude());
}

vec2 vec2::operator+(const vec2& other) {
   return vec2(this->x + other.x, this->y + other.y);
}
vec2 vec2::operator-(const vec2& other) {
   return vec2(this->x - other.x, this->y - other.y);
}
vec2 vec2::operator*(float scalar) const {
   return vec2(x*scalar, y*scalar);
}

vec2::vec2(float x, float y) : x(x), y(y) {}
