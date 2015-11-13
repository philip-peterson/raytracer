#include "vec2.h"
#include "vec3.h"
#include "sphere.h"
#include "hitinfo.h"
#include <cmath>

float lerp (float a, float b, float t) {
   return (1.0f-t)*a + t*b;
}

float screen (float a, float b) {
   return 1.0f - (1.0f - a)*(1.0f - b);
}

hitinfo raySphereIntersect(vec3 rayOrigin, vec3 rayDir, sphere s) {
   vec3 r_so = s.center - rayOrigin;
   vec3 u = rayDir.getNormalized();
   
   float b = -2.0f * u.dot(r_so);
   float c = r_so.getMagnitude();
   c *= c;
   c = c - s.radius * s.radius;

   float radicand = b*b - 4*c;
   if (radicand < 0.0f) {
      return hitinfo(false, vec3::zero, vec3::zero, 0);
   }

   float sqrtrad = sqrt(radicand);
   float t = 0.5f * (-b - sqrtrad);

   if (t <= 0) {
      t = 0.5f * (-b + sqrtrad);
      if (t <= 0) {
         return hitinfo(false, vec3::zero, vec3::zero, 0);
      }
   }

   vec3 intersectum = rayOrigin + u*t;
   vec3 normal = (intersectum - s.center).getNormalized();
   return hitinfo(true, intersectum, normal, t);

   // partially completed more complicated but more efficient version:
   //
   // --later-- //   // Solve quadratic formula for sphere intersection
   // --later-- //   // a = 1
   // --later-- //   // b = -2 __u__ . __r_so__
   // --later-- //   // c = r_so^2 - R^2
   // --later-- //   //
   // --later-- //   // Where
   // --later-- //   //    __r_so__ := position of sphere relative to ray origin
   // --later-- //   //    R := sphere radius
   // --later-- //   //    __u__ := unit ray direction
   // --later-- //   //
   // --later-- //   // let z := __u__ . __r_so__
   // --later-- //   // b = -2 * z
   // --later-- //   //
   // --later-- //   // if t = (-b +-   sqrt(  b^2 - 4 a c)) / (2a)
   // --later-- //   //    t = (-b +-   sqrt(4 z^2 - 4 a c)) / (2a)
   // --later-- //   //    t = (-b +- 2*sqrt(  z^2 -   a c)) / (2a)
   // --later-- //   //    t = (-b/2 +- sqrt(  z^2 -   a c)) / (a)
   // --later-- //   //    t = (-z +- sqrt(  z^2 -   a c)) / (a)
   // --later-- //   // and since a = 1
   // --later-- //   //    t = -z +- sqrt( z^2 - c)
   // --later-- //   //
   // --later-- //   // We will consider first the lower of the two possible t's
   // --later-- //   //    t = -z - sqrt( z^2 - c)
   // --later-- //   //
   // --later-- //   //    -z - sqrt( z^2 - c) >= 0
   // --later-- //   //    -z >= sqrt( z^2 - c)          (*)
   // --later-- //   //
   // --later-- //   // Thus the lower t is only a candidate when (*) holds true.
   // --later-- //   // Otherwise we must consider the upper t.

   // --later-- //   float oppz = -u.dot(r_so);
   // --later-- //   float mag_r_so = r_so.getMagnitude();
   // --later-- //   float c = mag_r_so * mag_r_so - s.radius * s.radius;

   // --later-- //   float radicand = oppz*oppz - c;
   // --later-- //   if (radicand < 0.0) {
   // --later-- //      return hitinfo(false);
   // --later-- //   }

   // --later-- //   float sqrtradic = sqrt(radicand);
   // --later-- //   if (sqrtradic <= oppz) {
   // --later-- //      
   // --later-- //   }
   // --later-- //   // compute larger t

}

vec3 multMatrix3ByVec3(float mtx[3][3], vec3 v) {
   vec3 newvec (0.0f, 0.0f, 0.0f);
   for (int i = 0; i < 3; i++) {
      vec3 row = vec3(mtx[i][0], mtx[i][1], mtx[i][2]);

      float component = row.dot(v);

      // ugh. sorry
      switch(i) {
         case 0:
            newvec.x = component;
         break;
         case 1:
            newvec.y = component;
         break;
         case 2:
            newvec.z = component;
         break;
      }
   }
   return newvec;
}

// The below functions were not used, however they may come in handy in the future...

float zCompOfCrossProd(const vec2& a, const vec2& b) {
   return a.x*b.y - a.y*b.x;
}

float isPointOnFrontOfTriangle(vec2 p, vec2 a, vec2 b, vec2 c) {
   // Notation:
   // r_uv := position of u relative to v

   vec2 r_pa = p - a; 
   vec2 r_pb = p - b; 
   vec2 r_pc = p - c; 

   vec2 r_ba = b - a;
   vec2 r_cb = c - b;
   vec2 r_ac = a - c;

   return 
         zCompOfCrossProd(r_ba, r_pa) >= 0
      && zCompOfCrossProd(r_cb, r_pb) >= 0
      && zCompOfCrossProd(r_ac, r_pc) >= 0
   ;
}
