#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../nGin64.h"

extern void SC_SimpleTower_DL();


void gin64_RenderInstanceObj(g64_EnvObjectPrefab* instance, int LODStepDist) {

    if (instance->staticModel_LOD[2].displayList) {

        if (!instance->staticModel_LOD[2].glDisplayList) {

            instance->staticModel_LOD[2].glDisplayList = glGenLists(1);
            glNewList(instance->staticModel_LOD[2].glDisplayList, GL_COMPILE);
            instance->staticModel_LOD[2].displayList();
            glEndList();
        }

        glPushMatrix();
        glTranslatef(instance->obj.pos.x, instance->obj.pos.y, instance->obj.pos.z);

        /*----- Note ----- Add this functionality */
       // glRotatef(instance->obj.rot.x, instance->obj.rot.y, instance->obj.rot.z, 1.0f);
       // glScalef(instance->obj.scl.x, instance->obj.scl.y, instance->obj.scl.z);

        glCallList(instance->staticModel_LOD[2].glDisplayList);
        glPopMatrix();

        gin64_UpdateTriCounter(12);

    }
}

void gin64_RenderEnvironmentObj(g64_EnvObjectPrefab* instance, int LODStepDist) {

    if (instance->staticModel_LOD[LODStepDist].displayList) {

        if (!instance->staticModel_LOD[LODStepDist].glDisplayList) {

            instance->staticModel_LOD[LODStepDist].glDisplayList = glGenLists(1);
            glNewList(instance->staticModel_LOD[LODStepDist].glDisplayList, GL_COMPILE);
            instance->staticModel_LOD[LODStepDist].displayList();
            glEndList();
        }

        glPushMatrix();
        glTranslatef(instance->obj.pos.x, instance->obj.pos.y, instance->obj.pos.z);
       // glRotatef(instance->obj.rot.x, instance->obj.rot.y, instance->obj.rot.z, 1.0f);
      //  glScalef(instance->obj.scl.x, instance->obj.scl.y, instance->obj.scl.z);

        //instance->staticModel_LOD[2].displayList();

        glCallList(instance->staticModel_LOD[LODStepDist].glDisplayList);
        glPopMatrix();

        gin64_UpdateTriCounter(12);
    }
}





void gin64_UpdatedNestedEnvObjList(g64_EnvObjectPrefab* instance, int LODStepDist) {


    //bool testbool = false;
    //testbool = SC_OfficeTower_DL_LOD2_ALL(instance, LODStepDist);

    if (instance->staticModel_LOD[LODStepDist].displayList) {

        if (!instance->staticModel_LOD[LODStepDist].glDisplayList) {

            instance->staticModel_LOD[LODStepDist].glDisplayList = glGenLists(1);
            glNewList(instance->staticModel_LOD[LODStepDist].glDisplayList, GL_COMPILE);
            instance->staticModel_LOD[LODStepDist].displayList();
            glEndList();
        }

        /*
        glPushMatrix();
        glTranslatef(instance->obj.pos.x, instance->obj.pos.y, instance->obj.pos.z);
        // glRotatef(instance->obj.rot.x, instance->obj.rot.y, instance->obj.rot.z, 1.0f);
       //  glScalef(instance->obj.scl.x, instance->obj.scl.y, instance->obj.scl.z);

         //instance->staticModel_LOD[2].displayList();

        glCallList(instance->staticModel_LOD[LODStepDist].glDisplayList);
        glPopMatrix();
        */
        gin64_UpdateTriCounter(12);
    }


}


//GLuint glSandDisplayList;
//GLuint glGlassDisplayList;

/*

extern bool SC_OfficeTower_DL_LOD2_ALL(g64_EnvObjectPrefab* instance, int LODStepDist);


void gin64_NestedEnvObjList(g64_EnvObjectPrefab* instance, GLuint currentList, int LODStepDist) {


}


void gin64_BuildEnvObjList(g64_EnvObjectPrefab* instance, GLuint* currentList, int LODStepDist) {









}





void gin64_RenderAllObj(g64_EnvObjectPrefab* instance, int LODStepDist) {






}

*/