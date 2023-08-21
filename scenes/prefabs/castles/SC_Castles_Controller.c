#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../../../ngin64/nGin64.h"
#include "../../../interface/SC_Interface.h"


extern GLuint textures[];
extern u8 textureTotal;

//void SC_Prefabs_Builder(g64_EnvObjectPrefab* prefabName, void (*displayListName));
//void SC_Prefabs_Builder(g64_EnvObjectPrefab* prefabName, void(*displayListName), void(*displayListName2), void(*displayListName3), u8 HP, u8 buildPoints, u8 currency);
void SC_Prefabs_Builder(g64_EnvObjectPrefab* prefabName, void(*displayListName), void(*displayListName2), void(*displayListName3), u8 maxJobs, u8 maxResidents, u8 HP, u8 buildMaterials, u8 buildCurrency);
void gin64_RenderInstanceObj(g64_EnvObjectPrefab* env, int LODStepDist);


g64_EnvObjectPrefab SC_Empty_PF; //Used for demolishing an existing property

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

extern void SC_LightHouse_DL_LOD0();
extern void SC_LightHouse_DL_LOD1();
extern void SC_LightHouse_DL_LOD2();
g64_EnvObjectPrefab SC_LightHouse_PF;

extern void SC_OfficeTower_DL_LOD0();
extern void SC_OfficeTower_DL_LOD1();
extern void SC_OfficeTower_DL_LOD2();
g64_EnvObjectPrefab SC_OfficeTower_PF;

extern void SC_ResidentialTower_DL_LOD0();
extern void SC_ResidentialTower_DL_LOD1();
extern void SC_ResidentialTower_DL_LOD2();
g64_EnvObjectPrefab SC_ResidentialTower_PF;

extern void SC_Powerplant_DL_LOD0();
extern void SC_Powerplant_DL_LOD1();
extern void SC_Powerplant_DL_LOD2();
g64_EnvObjectPrefab SC_Powerplant_PF;


void SC_Prefabs_BuildEvent();


void SC_Prefabs_Init()
{
	SC_Prefabs_Builder(&SC_SimpleTower_PF, &SC_SimpleTower_DL_LOD1, &SC_SimpleTower_DL_LOD1, &SC_SimpleTower_DL_LOD2, 0, 2, 12, 6, 1);
	SC_Prefabs_Builder(&SC_WatchTower_PF, &SC_WatchTower_DL_LOD0, &SC_WatchTower_DL_LOD1, &SC_WatchTower_DL_LOD2, 5, 1, 40, 8, 1);
	SC_Prefabs_Builder(&SC_LargeTower_PF, &SC_LargeTower_DL_LOD0, &SC_LargeTower_DL_LOD1, &SC_LargeTower_DL_LOD2, 3, 6, 20, 14, 3);
	SC_Prefabs_Builder(&SC_OfficeTower_PF, &SC_OfficeTower_DL_LOD0, &SC_OfficeTower_DL_LOD1, &SC_OfficeTower_DL_LOD2, 20, 0, 30, 30, 8); //office
	SC_Prefabs_Builder(&SC_ResidentialTower_PF, &SC_ResidentialTower_DL_LOD0, &SC_ResidentialTower_DL_LOD1, &SC_ResidentialTower_DL_LOD2, 6, 12, 40, 25, 6); //condo
	//powerplant


	gin64_Event_Subscribe(&BuildObjectEvent.OnTrigger, &SC_Prefabs_BuildEvent);
}

void SC_Prefabs_Builder(g64_EnvObjectPrefab* prefabName, void (*displayListName), void(*displayListName2), void(*displayListName3), u8 maxJobs, u8 maxResidents, u8 HP, u8 buildMaterials, u8 buildCurrency) {
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


	if(maxJobs >= 1){
		prefabName->jobs[0] = 1; //Initial job 
		prefabName->jobs[1] = maxJobs; //Initial job 
	}


	if (maxResidents >= 1) {
		prefabName->residents[0] = 1;
		prefabName->residents[1] = maxResidents;
	}
	prefabName->mood[0] = 10;
	//prefabName->alert = 0;

	prefabName->pointsH = HP; //a building's structural integrity... over time, it will degrade and needs to be revamped
	prefabName->pointsB = buildMaterials; //how much sand is needed to build this structure	
	prefabName->pointsC = buildCurrency; //how much money is needed to build this structure

#//ifdef DEBUG_NGIN64_INTERFACE
	//fprintf(stderr, "\nTesting Input | A %i | B %i", g64_Pad[0].hold.A, g64_Pad[0].hold.B);
	//fprintf(stderr, "\n > SC_Prefabs_Builder \n");
//#endif



}


extern playfieldState S_PlayfieldState_Pending[16][7];
extern playfieldState S_PlayfieldState_Current[16][7];
extern int editableBlocks[16][7][4];









/*
void SC_Prefabs_DrawCastles() {

	glEnable(GL_CULL_FACE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//
	//glBindTexture(GL_TEXTURE_2D, textures[7]); //>----- UPDATE ----- rebind with the new material settings
	//for( int materials = 0; materials < 2; materials ++){

		//Note - switch material settings

		glSandDisplayList = glGenLists(1);
		glNewList(glSandDisplayList, GL_COMPILE);


		glEndList();
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

}

*/



GLuint glSandDisplayList;
GLuint glGlassDisplayList;

bool updateCastleMesh = true;

void SC_Prefabs_BuildEvent() {

	updateCastleMesh = true;
}


extern void gin64_UpdatedNestedEnvObjList(g64_EnvObjectPrefab* instance, int LODStepDist);
void SC_Prefabs_BuildCastleDLs() {




	glEnable(GL_CULL_FACE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBindTexture(GL_TEXTURE_2D, textures[7]); //>----- UPDATE ----- rebind with the new material settings
	//glBindTexture(GL_TEXTURE_2D, textures[7]); //>----- UPDATE ----- rebind with the new material settings

	for (int column = 0; column < 16; column++) {
		for (int row = 0; row < 7; row++) {

			//----- Note ----- Print basic sand texture only once to save performance

			//if(S_PlayfieldState_Pending[column][row].structure.staticModel_LOD[0].displayList != NULL){
				//gin64_RenderEnvironmentObj(&S_PlayfieldState_Pending[column][row].structure, 2);
			gin64_RenderEnvironmentObj(&S_PlayfieldState_Current[column][row].structure, 2);

		}
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);



	/*
	glEnable(GL_CULL_FACE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);




	if (updateCastleMesh == true) {


		for (int column = 0; column < 16; column++) {
			for (int row = 0; row < 7; row++) {

				//----- Note ----- Print basic sand texture only once to save performance

				//if(S_PlayfieldState_Pending[column][row].structure.staticModel_LOD[0].displayList != NULL){
					//gin64_RenderEnvironmentObj(&S_PlayfieldState_Pending[column][row].structure, 2);
				gin64_UpdatedNestedEnvObjList(&S_PlayfieldState_Current[column][row].structure, 2);


				//}


			}
		}

		glSandDisplayList = glGenLists(1);
		glNewList(glSandDisplayList, GL_COMPILE);

		glBindTexture(GL_TEXTURE_2D, textures[7]); //>----- UPDATE ----- rebind with the new material settings

		for (int column = 0; column < 16; column++) {
			for (int row = 0; row < 7; row++) {

				//----- Note ----- Print basic sand texture only once to save performance

				//if(S_PlayfieldState_Pending[column][row].structure.staticModel_LOD[0].displayList != NULL){
					//gin64_RenderEnvironmentObj(&S_PlayfieldState_Pending[column][row].structure, 2);
				glPushMatrix();
				glTranslatef(S_PlayfieldState_Current[column][row].structure.obj.pos.x, S_PlayfieldState_Current[column][row].structure.obj.pos.y, S_PlayfieldState_Current[column][row].structure.obj.pos.z);
				// glRotatef(instance->obj.rot.x, instance->obj.rot.y, instance->obj.rot.z, 1.0f);
			   //  glScalef(instance->obj.scl.x, instance->obj.scl.y, instance->obj.scl.z);

				// instance->staticModel_LOD[2].displayList();

				glCallList(S_PlayfieldState_Current[column][row].structure.staticModel_LOD[2].glDisplayList);
				glPopMatrix();


				//}


			}
		}

		glEndList();

		updateCastleMesh = false;
		
	}

	glCallList(glSandDisplayList);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	*/
	

}




void SC_Prefabs_DrawCastles() {



	//SC_Prefabs_BuildCastleDLs();
	//return;


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
				//gin64_RenderEnvironmentObj(&S_PlayfieldState_Pending[column][row].structure, 2);
				gin64_RenderEnvironmentObj(&S_PlayfieldState_Current[column][row].structure, 2);

				
			//}
			

		}
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

}








