#ifndef SC_CREATURETYPES_H
#define SC_CREATURETYPES_H

#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../../../ngin64/nGin64.h"

extern g64_NPCObjectPrefab SC_KingCrab_PF;

extern void SC_KingCrab_DL();
extern void SC_CrabPrefabs_Init();
extern void SC_CrabPrefabs_Draw(g64_NPCObjectPrefab* prefabInstance);

#endif