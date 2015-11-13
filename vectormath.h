#ifndef __H_VECMATH
#define __H_VECMATH

#include "vec2.h"
#include "vec3.h"
#include "hitinfo.h"
#include "sphere.h"

float lerp(float, float, float);
float screen (float a, float b);
hitinfo raySphereIntersect(vec3 rayOrigin, vec3 rayDir, sphere s);
float zCompOfCrossProd(const vec2& a, const vec2& b);
float isPointOnFrontOfTriangle(vec2 p, vec2 a, vec2 b, vec2 c);

vec3 multMatrix3ByVec3(float mtx[3][3], vec3 v);

#endif
