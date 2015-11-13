#include <iostream>
#include "vec2.h"
#include "vec3.h"
#include "vectormath.h"
#include "sphere.h"
#include "hitinfo.h"
#include <GL/freeglut.h>
#include <cmath>

#define LOOKAT_X 0.0f
#define LOOKAT_Y 0.0f
#define LOOKAT_Z 1.0f

#define ORTHO_SIZE .01f

#define LIGHTDIR_X -.4f
#define LIGHTDIR_Y .6f
#define LIGHTDIR_Z .2f


#define SPEC_FACTOR 0.9f
#define SPEC_AMOUNT 0.8f
#define DIFF_AMOUNT 0.4f

#define TWOPI 6.2831853071795864769
#define PI 3.1415926535897932385
#define PIOVER2 1.5707963267948966192

using namespace std;

static unsigned int viewport_width = 1024;
static unsigned int viewport_height = 768;

static float* colorData;
static vec3 ambientColor ( 1.f/255.f, 5.f/255.f, 28.f/255.f );

static void displayBuffer() {
   glClear(GL_COLOR_BUFFER_BIT);
   glDrawPixels(viewport_width, viewport_height, GL_RGB, GL_FLOAT, colorData);
   glutSwapBuffers();
}

static void allocBuffer() {
   colorData = new float[viewport_width * viewport_height * 3];
}

static void initializeSpheres(int& numSpheres, sphere*& spheres) {
   numSpheres = 2;

   spheres = (sphere*)malloc(numSpheres*sizeof(sphere));

   // green
   spheres[0].center = vec3(1.0f, 0.0f, 2.0f);
   spheres[0].radius = .4f;
   spheres[0].color = vec3(0.0f, 1.0f, 0.0f);

   // red
   spheres[1].center = vec3(-1.0f, 0.0f, 8.0f);
   spheres[1].radius = 1.0f;
   spheres[1].color = vec3(1.0f, 0.0f, 0.0f);

}

static void raytraceScene(vec3 camPos, vec3 lookAt, vec3 lookRight, int numSpheres, sphere *spheres, vec3 lightDir) {
   for (int row = 0; row < viewport_height; row++) {
      for (int col = 0; col < viewport_width; col++) {
         int base = (row*viewport_width + col)*3;
         vec2 screenPosFromCenter = vec2(col - .5f * viewport_width, .5f * viewport_height - row);

         vec3 lookUp = lookRight.cross(lookAt);

         vec3 rayOrigin (camPos);
         rayOrigin = rayOrigin + lookRight*screenPosFromCenter.x*ORTHO_SIZE;
         rayOrigin = rayOrigin + lookUp*screenPosFromCenter.y*ORTHO_SIZE;

         colorData[base+0] = ambientColor.x;
         colorData[base+1] = ambientColor.y;
         colorData[base+2] = ambientColor.z;

         int winner = -1;
         float recordT = -1;
         hitinfo winnerInfo (false, vec3::zero, vec3::zero, -1);
         for (int i = 0; i < numSpheres; i++) {
            hitinfo rsi = raySphereIntersect(rayOrigin, lookAt, spheres[i]); 
            if (rsi.intersected) {
               if (recordT < 0 || rsi.t < recordT) {
                  recordT = rsi.t;
                  winnerInfo = rsi;
                  winner = i;
               }
            }
         }
         if (winner != -1) {
            float diffuseIntensity = max(-lightDir.dot(winnerInfo.normal), 0.0f) * DIFF_AMOUNT;
            vec3 reflection = (lightDir - winnerInfo.normal*2*(lightDir.dot(winnerInfo.normal)));
            vec3 view = (winnerInfo.intersectum - camPos).getNormalized();
            float specIntensity = SPEC_FACTOR*max(0.0f, -reflection.dot(view));
            specIntensity = specIntensity * specIntensity;
            specIntensity *= SPEC_AMOUNT;

            colorData[base+0] = spheres[winner].color.x * (ambientColor.x + diffuseIntensity*2);
            colorData[base+1] = spheres[winner].color.y * (ambientColor.y + diffuseIntensity*2);
            colorData[base+2] = spheres[winner].color.z * (ambientColor.z + diffuseIntensity*2);
            
            colorData[base+0] = screen(colorData[base+0], specIntensity);
            colorData[base+1] = screen(colorData[base+1], specIntensity);
            colorData[base+2] = screen(colorData[base+2], specIntensity);
         }

      }
   }
}

int main(int argc, char** argv) {
   allocBuffer();

   sphere* spheres;
   vec3 camPos = vec3::zero;

   vec3 lookAt (LOOKAT_X, LOOKAT_Y, LOOKAT_Z);
   vec3 lightDir (LIGHTDIR_X, LIGHTDIR_Y, LIGHTDIR_Z);

   lookAt = lookAt.getNormalized();
   lightDir = lightDir.getNormalized();
   
   float phi = PIOVER2 - acos(lookAt.y);

   float udotz = lookAt.dot(vec3(0.0f, 0.0f, 1.0f));
   float udotx = lookAt.dot(vec3(1.0f, 0.0f, 0.0f));

   float theta = acos(udotz);
   if (udotx <= 0.0f) {
      theta = TWOPI - theta;
   }

   float roty[3][3] = {
        { cos(theta)   , 0.0f ,  sin(theta)   }
      , { 0.0f         , 1.0f ,  0.0f         }
      , { -sin(theta)  , 0.0f ,  cos(theta)   }
   };

   float rotx[3][3] = {
        { 1.0f,  0.0f,     0.0f      }
      , { 0.0f,  cos(phi), -sin(phi) }
      , { 0.0f,  sin(phi), cos(phi)  }
   };

   vec3 lookRight = multMatrix3ByVec3(roty, vec3(-1.0f, 0.0f, 0.0f));
   lookRight = multMatrix3ByVec3(rotx, lookRight);

   int numSpheres;
   initializeSpheres(numSpheres, spheres);
   raytraceScene(camPos, lookAt, lookRight, numSpheres, spheres, lightDir);

   glutInit(&argc, argv);
   glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
   glutInitWindowSize( viewport_width, viewport_height ); 
   glutInitWindowPosition( 100, 100 );
   glutCreateWindow( "Raytracer" );

   glutDisplayFunc(displayBuffer);
   glClearColor(ambientColor.x, ambientColor.y, ambientColor.z, 1.0f);
   glutMainLoop();

   return 0;
}
