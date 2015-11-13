#ifndef __H_VEC2
#define __H_VEC2

struct vec2 {
   float x;
   float y;
   vec2(float x, float y);
   float getMagnitude() const;
   vec2 getNormalized() const;
   vec2 operator+(const vec2& other);
   vec2 operator-(const vec2& other);
   vec2 operator*(float scalar) const;
};

#endif
