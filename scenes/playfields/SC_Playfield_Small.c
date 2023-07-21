


#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../../ngin64/nGin64.h"







//--------------------------------------- BeachPlayfield ---------------------------------------
   //ACTIVE OBJ MATERIALS: 

   //>------------------------------ 
   //>     > matName: Beach 
   //>          - matTextureName: Sand-Texture-1 
   //>          - matTextureSize(x,y):  (64, 64) 
   //>------------------------------ 
   //>     > matName: rockybeach 
   //>          - matTextureName: Sand-Texture-3-Stones 
   //>          - matTextureSize(x,y):  (64, 64) 
   //>------------------------------ 
   //>     > matName: grass 
   //>          - matTextureName: Grass-Texture-2 
   //>          - matTextureSize(x,y):  (128, 32) 
   //>------------------------------ 
   //>     > matName: water 
   //>          - matTextureName: beach_waves_sequence51 
   //>          - matTextureSize(x,y):  (128, 32) 
   //>------------------------------ 


gl_XP64_Vert vert_BeachPlayfield[] = {
      {.pos = {-18.00, -9.00, 6.00}, .uv = {0.23, -1.81}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-18.00, -7.00, 6.00}, .uv = {0.36, -1.84}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-18.00, -5.00, 6.00}, .uv = {0.48, -1.86}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-18.00, -3.00, 6.00}, .uv = {0.60, -1.89}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-18.00, -1.00, 6.00}, .uv = {0.73, -1.91}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-18.00, 1.00, 6.00}, .uv = {0.85, -1.94}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-18.00, 3.00, 6.00}, .uv = {0.97, -1.97}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-18.00, 5.00, 6.00}, .uv = {1.09, -1.99}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-18.00, 7.00, 6.00}, .uv = {1.22, -2.02}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-18.00, 9.00, 6.00}, .uv = {1.34, -2.05}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-16.00, -9.00, 6.00}, .uv = {0.26, -1.68}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-16.00, -7.00, 6.00}, .uv = {0.38, -1.70}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-16.00, -5.00, 6.00}, .uv = {0.50, -1.73}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-16.00, -3.00, 6.00}, .uv = {0.63, -1.76}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-16.00, -1.00, 6.00}, .uv = {0.75, -1.78}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-16.00, 1.00, 6.00}, .uv = {0.87, -1.81}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-16.00, 3.00, 6.00}, .uv = {1.00, -1.84}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-16.00, 5.00, 6.00}, .uv = {1.12, -1.86}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-16.00, 7.00, 6.00}, .uv = {1.24, -1.89}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-16.00, 9.00, 6.00}, .uv = {1.37, -1.91}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-14.00, -9.00, 6.00}, .uv = {0.28, -1.55}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-14.00, -7.00, 6.00}, .uv = {0.40, -1.57}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-14.00, -5.00, 6.00}, .uv = {0.53, -1.60}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-14.00, -3.00, 6.00}, .uv = {0.65, -1.63}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-14.00, -1.00, 6.00}, .uv = {0.77, -1.65}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-14.00, 1.00, 6.00}, .uv = {0.90, -1.68}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-14.00, 3.00, 6.00}, .uv = {1.02, -1.70}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-14.00, 5.00, 6.00}, .uv = {1.14, -1.73}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-14.00, 7.00, 6.00}, .uv = {1.27, -1.76}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-14.00, 9.00, 6.00}, .uv = {1.39, -1.78}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-12.00, -9.00, 6.00}, .uv = {0.30, -1.42}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-12.00, -7.00, 6.00}, .uv = {0.43, -1.44}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-12.00, -5.00, 6.00}, .uv = {0.55, -1.47}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-12.00, -3.00, 6.00}, .uv = {0.67, -1.49}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-12.00, -1.00, 6.00}, .uv = {0.80, -1.52}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-12.00, 1.00, 6.00}, .uv = {0.92, -1.55}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-12.00, 3.00, 6.00}, .uv = {1.04, -1.57}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-12.00, 5.00, 6.00}, .uv = {1.17, -1.60}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-12.00, 7.00, 6.00}, .uv = {1.29, -1.63}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-12.00, 9.00, 6.00}, .uv = {1.41, -1.65}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-10.00, -9.00, 6.00}, .uv = {0.33, -1.28}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-10.00, -7.00, 6.00}, .uv = {0.45, -1.31}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-10.00, -5.00, 6.00}, .uv = {0.58, -1.34}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-10.00, -3.00, 6.00}, .uv = {0.70, -1.36}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-10.00, -1.00, 6.00}, .uv = {0.82, -1.39}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-10.00, 1.00, 6.00}, .uv = {0.95, -1.42}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-10.00, 3.00, 6.00}, .uv = {1.07, -1.44}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-10.00, 5.00, 6.00}, .uv = {1.19, -1.47}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-10.00, 7.00, 6.00}, .uv = {1.32, -1.49}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-10.00, 9.00, 6.00}, .uv = {1.44, -1.52}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-8.00, -9.00, 6.00}, .uv = {0.35, -1.15}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-8.00, -7.00, 6.00}, .uv = {0.48, -1.18}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-8.00, -5.00, 6.00}, .uv = {0.60, -1.21}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-8.00, -3.00, 6.00}, .uv = {0.72, -1.23}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-8.00, -1.00, 6.00}, .uv = {0.85, -1.26}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-8.00, 1.00, 6.00}, .uv = {0.97, -1.28}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-8.00, 3.00, 6.00}, .uv = {1.09, -1.31}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-8.00, 5.00, 6.00}, .uv = {1.22, -1.34}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-8.00, 7.00, 6.00}, .uv = {1.34, -1.36}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-8.00, 9.00, 6.00}, .uv = {1.46, -1.39}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-6.00, -9.00, 6.00}, .uv = {0.38, -1.02}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-6.00, -7.00, 6.00}, .uv = {0.50, -1.05}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-6.00, -5.00, 6.00}, .uv = {0.62, -1.07}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-6.00, -3.00, 6.00}, .uv = {0.75, -1.10}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-6.00, -1.00, 6.00}, .uv = {0.87, -1.13}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-6.00, 1.00, 6.00}, .uv = {0.99, -1.15}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-6.00, 3.00, 6.00}, .uv = {1.12, -1.18}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-6.00, 5.00, 6.00}, .uv = {1.24, -1.20}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-6.00, 7.00, 6.00}, .uv = {1.36, -1.23}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-6.00, 9.00, 6.00}, .uv = {1.49, -1.26}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-4.00, -9.00, 6.00}, .uv = {0.40, -0.89}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-4.00, -7.00, 6.00}, .uv = {0.52, -0.92}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-4.00, -5.00, 6.00}, .uv = {0.65, -0.94}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-4.00, -3.00, 6.00}, .uv = {0.77, -0.97}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-4.00, -1.00, 6.00}, .uv = {0.89, -0.99}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-4.00, 1.00, 6.00}, .uv = {1.02, -1.02}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-4.00, 3.00, 6.00}, .uv = {1.14, -1.05}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-4.00, 5.00, 6.00}, .uv = {1.26, -1.07}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-4.00, 7.00, 6.00}, .uv = {1.39, -1.10}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-4.00, 9.00, 6.00}, .uv = {1.51, -1.13}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-2.00, -9.00, 6.00}, .uv = {0.42, -0.76}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-2.00, -7.00, 6.00}, .uv = {0.55, -0.79}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-2.00, -5.00, 6.00}, .uv = {0.67, -0.81}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-2.00, -3.00, 6.00}, .uv = {0.80, -0.84}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-2.00, -1.00, 6.00}, .uv = {0.92, -0.86}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-2.00, 1.00, 6.00}, .uv = {1.04, -0.89}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-2.00, 3.00, 6.00}, .uv = {1.17, -0.92}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-2.00, 5.00, 6.00}, .uv = {1.29, -0.94}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-2.00, 7.00, 6.00}, .uv = {1.41, -0.97}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {-2.00, 9.00, 6.00}, .uv = {1.54, -0.99}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {0.00, -9.00, 6.00}, .uv = {0.45, -0.63}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {0.00, -7.00, 6.00}, .uv = {0.57, -0.65}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {0.00, -5.00, 6.00}, .uv = {0.70, -0.68}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {0.00, -3.00, 6.00}, .uv = {0.82, -0.71}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {0.00, -1.00, 6.00}, .uv = {0.94, -0.73}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {0.00, 1.00, 6.00}, .uv = {1.07, -0.76}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {0.00, 3.00, 6.00}, .uv = {1.19, -0.78}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {0.00, 5.00, 6.00}, .uv = {1.31, -0.81}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {0.00, 7.00, 6.00}, .uv = {1.44, -0.84}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {0.00, 9.00, 6.00}, .uv = {1.56, -0.86}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {2.00, -9.00, 6.00}, .uv = {0.47, -0.50}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {2.00, -7.00, 6.00}, .uv = {0.60, -0.52}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {2.00, -5.00, 6.00}, .uv = {0.72, -0.55}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {2.00, -3.00, 6.00}, .uv = {0.84, -0.57}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {2.00, -1.00, 6.00}, .uv = {0.97, -0.60}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {2.00, 1.00, 6.00}, .uv = {1.09, -0.63}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {2.00, 3.00, 6.00}, .uv = {1.21, -0.65}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {2.00, 5.00, 6.00}, .uv = {1.34, -0.68}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {2.00, 7.00, 6.00}, .uv = {1.46, -0.70}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {2.00, 9.00, 6.00}, .uv = {1.58, -0.73}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {4.00, -9.00, 6.00}, .uv = {0.50, -0.37}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {4.00, -7.00, 6.00}, .uv = {0.62, -0.39}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {4.00, -5.00, 6.00}, .uv = {0.74, -0.42}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {4.00, -3.00, 6.00}, .uv = {0.87, -0.44}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {4.00, -1.00, 6.00}, .uv = {0.99, -0.47}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {4.00, 1.00, 6.00}, .uv = {1.11, -0.50}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {4.00, 3.00, 6.00}, .uv = {1.24, -0.52}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {4.00, 5.00, 6.00}, .uv = {1.36, -0.55}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {4.00, 7.00, 6.00}, .uv = {1.48, -0.57}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {4.00, 9.00, 6.00}, .uv = {1.61, -0.60}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {6.00, -9.00, 6.00}, .uv = {0.52, -0.23}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {6.00, -7.00, 6.00}, .uv = {0.64, -0.26}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {6.00, -5.00, 6.00}, .uv = {0.77, -0.29}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {6.00, -3.00, 6.00}, .uv = {0.89, -0.31}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {6.00, -1.00, 6.00}, .uv = {1.01, -0.34}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {6.00, 1.00, 6.00}, .uv = {1.14, -0.36}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {6.00, 3.00, 6.00}, .uv = {1.26, -0.39}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {6.00, 5.00, 6.00}, .uv = {1.39, -0.42}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {6.00, 7.00, 6.00}, .uv = {1.51, -0.44}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {6.00, 9.00, 6.00}, .uv = {1.63, -0.47}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {8.00, -9.00, 6.00}, .uv = {0.54, -0.10}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {8.00, -7.00, 6.00}, .uv = {0.67, -0.13}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {8.00, -5.00, 6.00}, .uv = {0.79, -0.15}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {8.00, -3.00, 6.00}, .uv = {0.92, -0.18}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {8.00, -1.00, 6.00}, .uv = {1.04, -0.21}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {8.00, 1.00, 6.00}, .uv = {1.16, -0.23}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {8.00, 3.00, 6.00}, .uv = {1.29, -0.26}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {8.00, 5.00, 6.00}, .uv = {1.41, -0.28}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {8.00, 7.00, 6.00}, .uv = {1.53, -0.31}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {8.00, 9.00, 6.00}, .uv = {1.66, -0.34}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {10.00, -9.00, 6.00}, .uv = {0.57, 0.03}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {10.00, -7.00, 6.00}, .uv = {0.69, 0.00}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {10.00, -5.00, 6.00}, .uv = {0.82, -0.02}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {10.00, -3.00, 6.00}, .uv = {0.94, -0.05}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {10.00, -1.00, 6.00}, .uv = {1.06, -0.08}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {10.00, 1.00, 6.00}, .uv = {1.19, -0.10}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {10.00, 3.00, 6.00}, .uv = {1.31, -0.13}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {10.00, 5.00, 6.00}, .uv = {1.43, -0.15}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {10.00, 7.00, 6.00}, .uv = {1.56, -0.18}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {10.00, 9.00, 6.00}, .uv = {1.68, -0.21}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {12.00, -9.00, 6.00}, .uv = {0.59, 0.16}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {12.00, -7.00, 6.00}, .uv = {0.72, 0.13}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {12.00, -5.00, 6.00}, .uv = {0.84, 0.11}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {12.00, -3.00, 6.00}, .uv = {0.96, 0.08}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {12.00, -1.00, 6.00}, .uv = {1.09, 0.06}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {12.00, 1.00, 6.00}, .uv = {1.21, 0.03}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {12.00, 3.00, 6.00}, .uv = {1.33, 0.00}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {12.00, 5.00, 6.00}, .uv = {1.46, -0.02}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {12.00, 7.00, 6.00}, .uv = {1.58, -0.05}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {12.00, 9.00, 6.00}, .uv = {1.71, -0.07}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {14.00, -9.00, 6.00}, .uv = {0.62, 0.29}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {14.00, -7.00, 6.00}, .uv = {0.74, 0.27}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {14.00, -5.00, 6.00}, .uv = {0.86, 0.24}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {14.00, -3.00, 6.00}, .uv = {0.99, 0.21}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {14.00, -1.00, 6.00}, .uv = {1.11, 0.19}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {14.00, 1.00, 6.00}, .uv = {1.24, 0.16}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {14.00, 3.00, 6.00}, .uv = {1.36, 0.14}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {14.00, 5.00, 6.00}, .uv = {1.48, 0.11}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {14.00, 7.00, 6.00}, .uv = {1.61, 0.08}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {14.00, 9.00, 6.00}, .uv = {1.73, 0.06}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {16.00, -9.00, 6.00}, .uv = {0.64, 0.42}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {16.00, -7.00, 6.00}, .uv = {0.76, 0.40}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {16.00, -5.00, 6.00}, .uv = {0.89, 0.37}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {16.00, -3.00, 6.00}, .uv = {1.01, 0.34}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {16.00, -1.00, 6.00}, .uv = {1.14, 0.32}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {16.00, 1.00, 6.00}, .uv = {1.26, 0.29}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {16.00, 3.00, 6.00}, .uv = {1.38, 0.27}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {16.00, 5.00, 6.00}, .uv = {1.51, 0.24}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {16.00, 7.00, 6.00}, .uv = {1.63, 0.22}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {16.00, 9.00, 6.00}, .uv = {1.75, 0.19}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {18.00, -9.00, 6.00}, .uv = {0.67, 0.55}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {18.00, -7.00, 6.00}, .uv = {0.79, 0.53}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {18.00, -5.00, 6.00}, .uv = {0.91, 0.50}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {18.00, -3.00, 6.00}, .uv = {1.04, 0.48}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {18.00, -1.00, 6.00}, .uv = {1.16, 0.45}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {18.00, 1.00, 6.00}, .uv = {1.28, 0.42}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {18.00, 3.00, 6.00}, .uv = {1.41, 0.40}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {18.00, 5.00, 6.00}, .uv = {1.53, 0.37}, .vNormal = { 0.00, 0.00, 126.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {18.00, 7.00, 6.00}, .uv = {1.65, 0.35}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },
      {.pos = {18.00, 9.00, 6.00}, .uv = {1.78, 0.32}, .vNormal = { 0.00, 0.00, 127.00}, .vColor = { 238, 238, 236, 255 } },

};

uint16_t poly_BeachPlayfield_Beach[] = {
    //>------------------------------
       //>     + matName: Beach 
       //>          - matTextureName: Sand-Texture-1 
       //>          - matTextureSize(x,y):  (64, 64) 

    //>------------------------------

          18, 9, 8,
          11, 2, 1,
          10, 1, 0,
          12, 3, 2,
          13, 4, 3,
          14, 5, 4,
          15, 6, 5,
          16, 7, 6,
          17, 8, 7,
          23, 14, 13,
          26, 17, 16,
          25, 16, 15,
          22, 13, 12,
          20, 11, 10,
          27, 18, 17,
          21, 12, 11,
          28, 19, 18,
          24, 15, 14,
          30, 21, 20,
          31, 22, 21,
          18, 19, 9,
          11, 12, 2,
          10, 11, 1,
          12, 13, 3,
          13, 14, 4,
          14, 15, 5,
          15, 16, 6,
          16, 17, 7,
          17, 18, 8,
          23, 24, 14,
          26, 27, 17,
          25, 26, 16,
          22, 23, 13,
          20, 21, 11,
          27, 28, 18,
          21, 22, 12,
          28, 29, 19,
          24, 25, 15,
          30, 31, 21,
          34, 25, 24,
          38, 29, 28,
          32, 23, 22,
          37, 28, 27,
          35, 26, 25,
          36, 27, 26,
          33, 24, 23,
          41, 32, 31,
          40, 31, 30,
          34, 35, 25,
          31, 32, 22,
          38, 39, 29,
          32, 33, 23,
          37, 38, 28,
          35, 36, 26,
          36, 37, 27,
          33, 34, 24,
          40, 41, 31,
          45, 36, 35,
          48, 39, 38,
          42, 33, 32,
          44, 35, 34,
          46, 37, 36,
          47, 38, 37,
          43, 34, 33,
          55, 46, 45,
          53, 44, 43,
          56, 47, 46,
          54, 45, 44,
          52, 43, 42,
          50, 41, 40,
          58, 49, 48,
          51, 42, 41,
          57, 48, 47,
          63, 54, 53,
          62, 53, 52,
          60, 51, 50,
          61, 52, 51,
          41, 42, 32,
          45, 46, 36,
          48, 49, 39,
          42, 43, 33,
          44, 45, 35,
          46, 47, 37,
          47, 48, 38,
          43, 44, 34,
          55, 56, 46,
          53, 54, 44,
          56, 57, 47,
          54, 55, 45,
          52, 53, 43,
          50, 51, 41,
          58, 59, 49,
          51, 52, 42,
          57, 58, 48,
          62, 63, 53,
          60, 61, 51,
          61, 62, 52,
          67, 58, 57,
          66, 57, 56,
          64, 55, 54,
          65, 56, 55,
          68, 59, 58,
          72, 63, 62,
          70, 61, 60,
          71, 62, 61,
          73, 64, 63,
          63, 64, 54,
          67, 68, 58,
          66, 67, 57,
          64, 65, 55,
          65, 66, 56,
          68, 69, 59,
          72, 73, 63,
          70, 71, 61,
          71, 72, 62,
          76, 67, 66,
          74, 65, 64,
          78, 69, 68,
          77, 68, 67,
          75, 66, 65,
          82, 73, 72,
          84, 75, 74,
          83, 74, 73,
          80, 71, 70,
          87, 78, 77,
          88, 79, 78,
          81, 72, 71,
          85, 76, 75,
          86, 77, 76,
          93, 84, 83,
          94, 85, 84,
          92, 83, 82,
          90, 81, 80,
          91, 82, 81,
          95, 86, 85,
          76, 77, 67,
          74, 75, 65,
          78, 79, 69,
          73, 74, 64,
          77, 78, 68,
          75, 76, 66,
          82, 83, 73,
          84, 85, 75,
          83, 84, 74,
          80, 81, 71,
          87, 88, 78,
          88, 89, 79,
          81, 82, 72,
          85, 86, 76,
          86, 87, 77,
          93, 94, 84,
          94, 95, 85,
          92, 93, 83,
          90, 91, 81,
          91, 92, 82,
          98, 89, 88,
          97, 88, 87,
          96, 87, 86,
          101, 92, 91,
          100, 91, 90,
          103, 94, 93,
          105, 96, 95,
          104, 95, 94,
          102, 93, 92,
          98, 99, 89,
          97, 98, 88,
          96, 97, 87,
          95, 96, 86,
          101, 102, 92,
          100, 101, 91,
          103, 104, 94,
          104, 105, 95,
          102, 103, 93,
          108, 99, 98,
          106, 97, 96,
          107, 98, 97,
          118, 109, 108,
          113, 104, 103,
          115, 106, 105,
          112, 103, 102,
          114, 105, 104,
          110, 101, 100,
          117, 108, 107,
          116, 107, 106,
          111, 102, 101,
          125, 116, 115,
          121, 112, 111,
          124, 115, 114,
          122, 113, 112,
          120, 111, 110,
          126, 117, 116,
          123, 114, 113,
          127, 118, 117,
          108, 109, 99,
          105, 106, 96,
          106, 107, 97,
          107, 108, 98,
          118, 119, 109,
          113, 114, 104,
          115, 116, 106,
          112, 113, 103,
          114, 115, 105,
          110, 111, 101,
          117, 118, 108,
          116, 117, 107,
          111, 112, 102,
          125, 126, 116,
          121, 122, 112,
          124, 125, 115,
          122, 123, 113,
          120, 121, 111,
          126, 127, 117,
          123, 124, 114,
          128, 119, 118,
          130, 121, 120,
          136, 127, 126,
          137, 128, 127,
          131, 122, 121,
          135, 126, 125,
          134, 125, 124,
          132, 123, 122,
          133, 124, 123,
          128, 129, 119,
          127, 128, 118,
          130, 131, 121,
          136, 137, 127,
          131, 132, 122,
          135, 136, 126,
          134, 135, 125,
          132, 133, 123,
          133, 134, 124,
          138, 129, 128,
          148, 139, 138,
          142, 133, 132,
          140, 131, 130,
          146, 137, 136,
          145, 136, 135,
          141, 132, 131,
          143, 134, 133,
          144, 135, 134,
          147, 138, 137,
          156, 147, 146,
          154, 145, 144,
          152, 143, 142,
          150, 141, 140,
          157, 148, 147,
          155, 146, 145,
          151, 142, 141,
          153, 144, 143,
          158, 149, 148,
          137, 138, 128,
          138, 139, 129,
          148, 149, 139,
          142, 143, 133,
          140, 141, 131,
          146, 147, 137,
          145, 146, 136,
          141, 142, 132,
          143, 144, 134,
          144, 145, 135,
          147, 148, 138,
          156, 157, 147,
          154, 155, 145,
          152, 153, 143,
          150, 151, 141,
          157, 158, 148,
          155, 156, 146,
          151, 152, 142,
          153, 154, 144,
          158, 159, 149,
          168, 159, 158,
          163, 154, 153,
          160, 151, 150,
          162, 153, 152,
          164, 155, 154,
          166, 157, 156,
          161, 152, 151,
          167, 158, 157,
          165, 156, 155,
          168, 169, 159,
          163, 164, 154,
          160, 161, 151,
          162, 163, 153,
          164, 165, 155,
          166, 167, 157,
          161, 162, 152,
          167, 168, 158,
          165, 166, 156,
          173, 164, 163,
          171, 162, 161,
          177, 168, 167,
          178, 169, 168,
          170, 161, 160,
          172, 163, 162,
          174, 165, 164,
          176, 167, 166,
          175, 166, 165,
          183, 174, 173,
          181, 172, 171,
          188, 179, 178,
          186, 177, 176,
          184, 175, 174,
          182, 173, 172,
          180, 171, 170,
          185, 176, 175,
          187, 178, 177,
          173, 174, 164,
          171, 172, 162,
          177, 178, 168,
          178, 179, 169,
          170, 171, 161,
          172, 173, 163,
          174, 175, 165,
          176, 177, 167,
          175, 176, 166,
          183, 184, 174,
          181, 182, 172,
          188, 189, 179,
          186, 187, 177,
          184, 185, 175,
          182, 183, 173,
          180, 181, 171,
          185, 186, 176,
          187, 188, 178,

};


uint16_t get_BeachPlayfield_Size() {

    return sizeof(poly_BeachPlayfield_Beach);
}
