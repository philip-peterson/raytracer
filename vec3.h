#ifndef __H_VEC3
#define __H_VEC3


struct vec3 {
   float x;
   float y;
   float z;
   vec3(float x, float y, float z);
   float getMagnitude() const;
   vec3 getNormalized() const;
   vec3 operator*(float scalar) const;
   vec3 operator-(const vec3& other) const;
   vec3 operator+(const vec3& other) const;
   vec3 projOnto(const vec3& other) const;
   float dot(const vec3& other) const;
   vec3 cross(const vec3& other) const;
   static vec3 zero;
};


#endif
