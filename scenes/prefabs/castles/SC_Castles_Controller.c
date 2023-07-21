#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../../../ngin64/nGin64.h"


void SC_Prefabs_Builder(g64_EnvObjectPrefab* prefabName, void (*displayListName));
void gin64_RenderInstanceObj(g64_EnvObjectPrefab* env, int LODStepDist);

extern void SC_SimpleTower_DL();
g64_EnvObjectPrefab SC_SimpleTower_PF;

extern void SC_TallTower_DL();
g64_EnvObjectPrefab SC_TallTower_PF;

void SC_Prefabs_Init()
{
	SC_Prefabs_Builder(&SC_SimpleTower_PF, &SC_SimpleTower_DL);
	SC_Prefabs_Builder(&SC_TallTower_PF, &SC_TallTower_DL);

}

void SC_Prefabs_Builder(g64_EnvObjectPrefab* prefabName, void (*displayListName)) {
	//SC_SimpleTower_DL
	SetVector3(&prefabName->obj.pos, 0, 0, 0); // default position... this should be updated when an instance is made
	SetVector3(&prefabName->obj.rot, 0, 0, 0);
	SetVector3(&prefabName->obj.scl, 1, 1, 1);
	prefabName->staticModel_LOD[0].displayList = &SC_SimpleTower_DL;
	prefabName->staticModel_LOD[1].displayList = &SC_SimpleTower_DL;
	prefabName->staticModel_LOD[2].displayList = &SC_SimpleTower_DL;

#//ifdef DEBUG_NGIN64_INTERFACE
	//fprintf(stderr, "\nTesting Input | A %i | B %i", g64_Pad[0].hold.A, g64_Pad[0].hold.B);
	fprintf(stderr, "\n > SC_Prefabs_Builder \n");
//#endif



}


extern playfieldState S_PlayfieldState_Pending[16][7];
extern playfieldState S_PlayfieldState_Current[16][7];
extern int editableBlocks[16][7][4];

void SC_Prefabs_DrawCastles() {


	for (int column = 0; column < 16; column++){
		for (int row = 0; row < 7; row++) {


			if(S_PlayfieldState_Pending[column][row].structure.staticModel_LOD[0].displayList != NULL){
				gin64_RenderInstanceObj(&S_PlayfieldState_Pending[column][row].structure, 0);
			}
			

		}
	}

	//gin64_RenderInstanceObj(&S_PlayfieldState_Pending[8][4].structure, 0);
	//gin64_RenderInstanceObj(&S_PlayfieldState_Pending[6][4].structure, 0);
	//S_PlayfieldState_Pending[8][4].structure->staticModel_LOD[0].displayList;
	//S_PlayfieldState_Pending[6][4].structure->staticModel_LOD[0].displayList();


}


