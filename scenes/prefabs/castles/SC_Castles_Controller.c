#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../../../ngin64/nGin64.h"


extern GLuint textures[];
extern u8 textureTotal;

//void SC_Prefabs_Builder(g64_EnvObjectPrefab* prefabName, void (*displayListName));
void SC_Prefabs_Builder(g64_EnvObjectPrefab* prefabName, void(*displayListName), void(*displayListName2), void(*displayListName3), u8 HP, u8 buildPoints, u8 currency);
void gin64_RenderInstanceObj(g64_EnvObjectPrefab* env, int LODStepDist);

extern void SC_SimpleTower_DL_LOD0();
extern void SC_SimpleTower_DL_LOD1();
extern void SC_SimpleTower_DL_LOD2();
g64_EnvObjectPrefab SC_SimpleTower_PF;

extern void SC_WatchTower_DL_LOD0();
extern void SC_WatchTower_DL_LOD1();
extern void SC_WatchTower_DL_LOD2();
g64_EnvObjectPrefab SC_WatchTower_PF;

extern void SC_LargeTower_DL_LOD0();
extern void SC_LargeTower_DL_LOD1();
extern void SC_LargeTower_DL_LOD2();
g64_EnvObjectPrefab SC_LargeTower_PF;

void SC_Prefabs_Init()
{
	SC_Prefabs_Builder(&SC_SimpleTower_PF, &SC_SimpleTower_DL_LOD1, &SC_SimpleTower_DL_LOD1, &SC_SimpleTower_DL_LOD2, 8, 6, 1);
	SC_Prefabs_Builder(&SC_WatchTower_PF, &SC_WatchTower_DL_LOD0, &SC_WatchTower_DL_LOD1, &SC_WatchTower_DL_LOD2, 6, 8, 1);
	SC_Prefabs_Builder(&SC_LargeTower_PF, &SC_LargeTower_DL_LOD0, &SC_LargeTower_DL_LOD1, &SC_LargeTower_DL_LOD2, 22, 14, 3);
}

void SC_Prefabs_Builder(g64_EnvObjectPrefab* prefabName, void (*displayListName), void(*displayListName2), void(*displayListName3), u8 HP, u8 buildPoints, u8 currency) {
	//SC_SimpleTower_DL
	SetVector3(&prefabName->obj.pos, 0, 0, 0); // default position... this should be updated when an instance is made
	SetVector3(&prefabName->obj.rot, 0, 0, 0);
	SetVector3(&prefabName->obj.scl, 1, 1, 1);
	//prefabName->staticModel_LOD[0].displayList = &SC_SimpleTower_DL_LOD1;
	//prefabName->staticModel_LOD[1].displayList = &SC_SimpleTower_DL_LOD2;
	//prefabName->staticModel_LOD[2].displayList = &SC_SimpleTower_DL_LOD2;
	prefabName->staticModel_LOD[0].displayList = displayListName;
	prefabName->staticModel_LOD[1].displayList = displayListName2;
	prefabName->staticModel_LOD[2].displayList = displayListName3;

	prefabName->pointsH = HP; //a building's structural integrity... over time, it will degrade and needs to be revamped
	prefabName->pointsB = buildPoints; //how much sand is needed to build this structure	
	prefabName->pointsC = currency; //how much sand is needed to build this structure

#//ifdef DEBUG_NGIN64_INTERFACE
	//fprintf(stderr, "\nTesting Input | A %i | B %i", g64_Pad[0].hold.A, g64_Pad[0].hold.B);
	fprintf(stderr, "\n > SC_Prefabs_Builder \n");
//#endif



}


extern playfieldState S_PlayfieldState_Pending[16][7];
extern playfieldState S_PlayfieldState_Current[16][7];
extern int editableBlocks[16][7][4];

void SC_Prefabs_DrawCastles() {

	glEnable(GL_CULL_FACE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//glBindTexture(GL_TEXTURE_2D, textures[7]); //>----- UPDATE ----- rebind with the new material settings

	for (int column = 0; column < 16; column++){
		for (int row = 0; row < 7; row++) {

			//----- Note ----- Print basic sand texture only once to save performance

			//if(S_PlayfieldState_Pending[column][row].structure.staticModel_LOD[0].displayList != NULL){
				gin64_RenderEnvironmentObj(&S_PlayfieldState_Pending[column][row].structure, 2);
			//}
			

		}
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

}


