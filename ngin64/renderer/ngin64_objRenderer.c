#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../nGin64.h"

extern void SC_SimpleTower_DL();

void gin64_RenderInstanceObj(g64_EnvObjectPrefab* instance, int LODStepDist) {

    if(instance->staticModel_LOD[0].displayList){

        glPushMatrix();
            glTranslatef(instance->obj.pos.x, instance->obj.pos.y, instance->obj.pos.z);
            glRotatef(instance->obj.rot.x, instance->obj.rot.y, instance->obj.rot.z, 1.0f);
            glScalef(instance->obj.scl.x, instance->obj.scl.y, instance->obj.scl.z);

            instance->staticModel_LOD[0].displayList();

        glPopMatrix();

    }
}

void gin64_RenderEnvironmentObj(g64_EnvObjectPrefab* instance, int LODStepDist) {

    if (instance->staticModel_LOD[0].displayList) {

        glPushMatrix();
        glTranslatef(instance->obj.pos.x, instance->obj.pos.y, instance->obj.pos.z);
        glRotatef(instance->obj.rot.x, instance->obj.rot.y, instance->obj.rot.z, 1.0f);
        glScalef(instance->obj.scl.x, instance->obj.scl.y, instance->obj.scl.z);

        instance->staticModel_LOD[0].displayList();

        glPopMatrix();

    }
}