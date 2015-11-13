#ifndef __H_SPHERE
#define __H_SPHERE

#include "vec3.h"

struct sphere {
   vec3 center;
   float radius;
   vec3 color;
   sphere(vec3 center, float radius, vec3 color);
   sphere();
};
// : center(vec3::zero), radius(0.0f), color(vec3::zero)
#endif
