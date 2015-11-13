#ifndef __H_HITINFO
#define __H_HITINFO

#include "vec3.h"

struct hitinfo {
   bool intersected;
   vec3 intersectum;
   vec3 normal;
   float t;
   hitinfo(bool intersected, const vec3& intersectum, const vec3& normal, float t) : intersected(intersected), intersectum(intersectum), normal(normal), t(t) {};
   hitinfo(const hitinfo& other) : intersected(other.intersected), intersectum(other.intersectum), normal(other.normal), t(other.t) {};
};

#endif
