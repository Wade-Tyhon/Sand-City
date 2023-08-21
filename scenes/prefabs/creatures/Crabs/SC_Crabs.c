
#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../../../../ngin64/nGin64.h"

//--------------------------------------- SimpleTower ---------------------------------------
   //ACTIVE OBJ MATERIALS: 

   //>------------------------------ 
   //>     > matName: Beach 
   //>          - matTextureName: Sand-Texture-1 
   //>          - matTextureSize(x,y):  (64, 64) 
   //>------------------------------ 


extern GLuint textures[];
extern u8 textureTotal;


static const gl_XP64_Vert vert_Crab_LOD1[] = {
      {.pos = {0.49, -0.00, 0.52}, .uv = {0.97, -0.49}, .vNormal = { 2.00, 0.00, 126.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {0.28, 0.42, 0.35}, .uv = {0.76, -0.91}, .vNormal = { -9.00, 56.00, 113.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {-0.11, -0.00, 0.53}, .uv = {0.38, -0.49}, .vNormal = { -31.00, 0.00, 123.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {-0.47, 0.23, 0.27}, .uv = {0.03, -0.72}, .vNormal = { -57.00, 33.00, 108.00}, .vColor = { 127, 105, 103, 255 } },
      {.pos = {-0.47, -0.24, 0.27}, .uv = {0.03, -0.26}, .vNormal = { -57.00, -33.00, 108.00}, .vColor = { 127, 105, 103, 255 } },
      {.pos = {0.28, -0.43, 0.35}, .uv = {0.76, -0.08}, .vNormal = { -9.00, -56.00, 113.00}, .vColor = { 181, 172, 171, 255 } },
      {.pos = {0.48, 0.01, 0.48}, .uv = {0.36, -0.33}, .vNormal = { 92.00, -1.00, 87.00}, .vColor = { 163, 151, 150, 255 } },
      {.pos = {0.30, -0.25, 0.34}, .uv = {0.38, -0.64}, .vNormal = { 10.00, -78.00, 99.00}, .vColor = { 90, 42, 36, 255 } },
      {.pos = {0.67, 0.01, 0.28}, .uv = {0.05, -0.33}, .vNormal = { 92.00, 0.00, 87.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {0.30, 0.28, 0.34}, .uv = {0.38, -0.01}, .vNormal = { 11.00, 77.00, 99.00}, .vColor = { 90, 42, 36, 255 } },
      {.pos = {0.53, 0.33, 0.37}, .uv = {0.69, -0.67}, .vNormal = { -26.00, 34.00, 119.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {0.49, 0.48, 0.30}, .uv = {0.66, -0.77}, .vNormal = { -29.00, 45.00, 114.00}, .vColor = { 181, 172, 171, 255 } },
      {.pos = {0.30, 0.28, 0.34}, .uv = {0.50, -0.64}, .vNormal = { 11.00, 77.00, 99.00}, .vColor = { 90, 42, 36, 255 } },
      {.pos = {0.97, 0.71, 0.35}, .uv = {0.98, -0.92}, .vNormal = { -25.00, 36.00, 119.00}, .vColor = { 181, 172, 171, 255 } },
      {.pos = {0.08, -0.29, 0.30}, .uv = {0.40, -0.67}, .vNormal = { -9.00, -76.00, 100.00}, .vColor = { 91, 44, 38, 255 } },
      {.pos = {0.24, -0.70, -0.05}, .uv = {0.50, -0.94}, .vNormal = { -2.00, -83.00, 96.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {0.30, -0.25, 0.34}, .uv = {0.50, -0.65}, .vNormal = { 10.00, -78.00, 99.00}, .vColor = { 90, 42, 36, 255 } },
      {.pos = {-0.10, -0.26, 0.29}, .uv = {0.28, -0.65}, .vNormal = { -18.00, -74.00, 100.00}, .vColor = { 90, 42, 36, 255 } },
      {.pos = {-0.16, -0.77, -0.05}, .uv = {0.24, -0.98}, .vNormal = { -17.00, -68.00, 105.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {-0.26, -0.24, 0.28}, .uv = {0.18, -0.63}, .vNormal = { -21.00, -84.00, 92.00}, .vColor = { 90, 42, 36, 255 } },
      {.pos = {-0.48, -0.54, -0.05}, .uv = {0.04, -0.83}, .vNormal = { -21.00, -84.00, 92.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {-0.26, 0.26, 0.28}, .uv = {0.18, -0.63}, .vNormal = { -21.00, 84.00, 92.00}, .vColor = { 90, 42, 36, 255 } },
      {.pos = {-0.10, 0.28, 0.29}, .uv = {0.28, -0.65}, .vNormal = { -18.00, 74.00, 100.00}, .vColor = { 90, 42, 36, 255 } },
      {.pos = {-0.48, 0.56, -0.05}, .uv = {0.04, -0.83}, .vNormal = { -21.00, 84.00, 92.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {0.08, 0.31, 0.30}, .uv = {0.40, -0.67}, .vNormal = { -9.00, 76.00, 100.00}, .vColor = { 90, 42, 36, 255 } },
      {.pos = {-0.16, 0.79, -0.05}, .uv = {0.24, -0.97}, .vNormal = { -17.00, 68.00, 105.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {0.24, 0.73, -0.05}, .uv = {0.50, -0.93}, .vNormal = { -2.00, 83.00, 96.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {0.85, 0.34, 0.43}, .uv = {0.80, -0.40}, .vNormal = { -17.00, -45.00, 117.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {0.97, 0.71, 0.35}, .uv = {0.40, -0.58}, .vNormal = { -25.00, 36.00, 119.00}, .vColor = { 181, 172, 171, 255 } },
      {.pos = {0.53, 0.33, 0.37}, .uv = {0.76, -0.04}, .vNormal = { -26.00, 34.00, 119.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {1.06, 0.25, 0.35}, .uv = {0.99, -0.58}, .vNormal = { -9.00, -93.00, 85.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {0.85, -0.32, 0.43}, .uv = {0.80, -0.40}, .vNormal = { -17.00, 45.00, 117.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {0.53, -0.30, 0.37}, .uv = {0.75, -0.04}, .vNormal = { -26.00, -34.00, 119.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {0.97, -0.69, 0.35}, .uv = {0.40, -0.58}, .vNormal = { -25.00, -36.00, 119.00}, .vColor = { 181, 172, 171, 255 } },
      {.pos = {1.06, -0.23, 0.35}, .uv = {0.98, -0.58}, .vNormal = { -9.00, 93.00, 85.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {0.53, -0.30, 0.37}, .uv = {0.69, -0.68}, .vNormal = { -26.00, -34.00, 119.00}, .vColor = { 255, 255, 255, 255 } },
      {.pos = {0.49, -0.46, 0.30}, .uv = {0.66, -0.78}, .vNormal = { -29.00, -45.00, 114.00}, .vColor = { 181, 172, 171, 255 } },
      {.pos = {0.97, -0.69, 0.35}, .uv = {0.98, -0.93}, .vNormal = { -25.00, -36.00, 119.00}, .vColor = { 181, 172, 171, 255 } },

};

static const uint16_t poly_Crab_LOD1_Crab_Legs[] = {
    //>------------------------------
       //>     + matName: Crab_Legs 
       //>          - matTextureName: Crab_Legs 
       //>          - matTextureSize(x,y):  (64, 64) 

    //>------------------------------

          6, 7, 8,
          9, 6, 8,
          10, 11, 12,
          10, 13, 11,
          14, 15, 16,
          17, 18, 14,
          19, 20, 17,
          21, 22, 23,
          22, 24, 25,
          24, 12, 26,
          27, 28, 29,
          30, 27, 29,
          31, 32, 33,
          34, 32, 31,
          35, 16, 36,
          35, 36, 37,

};


static const uint16_t poly_Crab_LOD1_Crab_Shell[] = {
    //>------------------------------
       //>     + matName: Crab_Shell 
       //>          - matTextureName: Crab_Shell 
       //>          - matTextureSize(x,y):  (64, 64) 

    //>------------------------------

          0, 1, 2,
          1, 3, 2,
          3, 4, 2,
          4, 5, 2,
          5, 0, 2,

};



void SC_Crab_DL_LOD0() {

    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(gl_XP64_Vert), (void*)(0 * sizeof(float) + (void*)vert_Crab_LOD1));
    glTexCoordPointer(2, GL_FLOAT, sizeof(gl_XP64_Vert), (void*)(3 * sizeof(float) + (void*)vert_Crab_LOD1));
    glNormalPointer(GL_FLOAT, sizeof(gl_XP64_Vert), (void*)(5 * sizeof(float) + (void*)vert_Crab_LOD1));
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(gl_XP64_Vert), (void*)(8 * sizeof(float) + (void*)vert_Crab_LOD1));

    //glBindTexture(GL_TEXTURE_2D, textures[17]); //>----- UPDATE ----- rebind with the new material settings
    //glDrawElements(GL_TRIANGLES, sizeof(poly_Crab_LOD1_Crab_Legs) / sizeof(uint16_t), GL_UNSIGNED_SHORT, poly_Crab_LOD1_Crab_Legs);

    glBindTexture(GL_TEXTURE_2D, textures[16]); //>----- UPDATE ----- rebind with the new material settings
    glDrawElements(GL_TRIANGLES, sizeof(poly_Crab_LOD1_Crab_Shell) / sizeof(uint16_t), GL_UNSIGNED_SHORT, poly_Crab_LOD1_Crab_Shell);
    glBindTexture(GL_TEXTURE_2D, textures[17]); //>----- UPDATE ----- rebind with the new material settings
    glDrawElements(GL_TRIANGLES, sizeof(poly_Crab_LOD1_Crab_Legs) / sizeof(uint16_t), GL_UNSIGNED_SHORT, poly_Crab_LOD1_Crab_Legs);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    gin64_UpdateTriCounter(21);
}
