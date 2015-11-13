#include "vec3.h"
#include <cmath>

vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) { }

float vec3::getMagnitude() const {
   return sqrt(x*x + y*y + z*z);
}

vec3 vec3::getNormalized() const {
   return (*this) * (1.0/getMagnitude());
}

vec3 vec3::operator*(float scalar) const {
   return vec3(x*scalar, y*scalar, z*scalar);
}

vec3 vec3::operator+(const vec3& other) const {
   return vec3(this->x+other.x, this->y+other.y, this->z+other.z);
}

vec3 vec3::operator-(const vec3& other) const {
   return vec3(this->x-other.x, this->y-other.y, this->z-other.z);
}

vec3 vec3::projOnto(const vec3& other) const {
   return other * (this->dot(other) / (other.dot(other)));
}

float vec3::dot(const vec3& other) const {
   return this->x*other.x + this->y*other.y + this->z*other.z;
}

vec3 vec3::cross(const vec3& other) const {
   return vec3(this->y*other.z - this->z*other.y, this->z*other.x - this->x*other.z, this->x*other.y - this->y*other.x);
}

vec3 vec3::zero(0,0,0);
