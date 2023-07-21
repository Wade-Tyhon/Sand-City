#ifndef NGIN64_COLTYPES_H
#define NGIN64_COLTYPES_H



/*--------------------------------------------------------------------------*/
/*------------------------------Collision Objects---------------------------*/
/*--------------------------------------------------------------------------*/


typedef struct {
	//For use with simple collision tests that are axis aligned like hit boxes, triggers, etc
	Vector3 min;
	Vector3 max;
}BoundBox;

typedef struct
{	//For use with collision tests on complex objects that are not axis aligned.
	Vector3 minA;
	Vector3 maxA;
	Vector3 minB;
	Vector3 maxB;
}PolyBox;

typedef struct {
	//best for use for moving object collision tests 
	u8 enabled;
	Vector3 center;
	float radius;
}Sphere;


/*--------------------------------------------------------------------------*/
/*------------------------------Collision Mesh---------------------------*/
/*--------------------------------------------------------------------------*/

typedef struct {
	//Use the mesh collider to build a simple collision mesh to represent level geometry
	Vector3 vertex;
	u8 normal[3];
}MeshCollider;

typedef struct {
	//Use the mesh collider to build a simple collision mesh to represent level geometry
	short tri[3];
}MeshColliderTri;

typedef struct {
	MeshCollider* meshVtx; //the vtx points that make up each collision tri
	MeshColliderTri* meshTri; //the tris to check collision on
	u8	meshLength; //number of tris to check collision on
}MeshColliderObj;

typedef struct {
	u8 collision;
	u8 triNum;
	float vDot;
	Vector3 vecSubtract;
	Vector3 lastCollisionPoint;
	Vector3 currentCollisionPoint;
	Vector3 nearestCollisionPoint;
}CollisionPoint;

typedef struct {
	u8 collision;
	u8 triNum;
	float vDot;
	Vector3 triNormal;
	Vector3 lastCollisionPoint;
	Vector3 currentCollisionPoint;
}Debug_Collision;



/*--------------------------------------------------------------------------*/
/*-----------------------------Trigger GameObjects--------------------------*/
/*--------------------------------------------------------------------------*/

typedef struct
{
	BoundBox collider;
	//u8 boolean;
	u8 isActive;
}TriggerBox;

typedef struct
{
	TriggerBox trigger;
	//void (*function)();
}EnvLighting;

typedef struct
{
	TriggerBox trigger;
	//void (*function)();
}TriggerGeometry;

typedef struct
{
	TriggerBox trigger;
	void (*function)();
}EventTrigger;



//-----------------------------Collision Hierarchy--------------------------
//NOTE ON USE: This is a series of structs for the specific use of a collision hierarchy 
//LevelCol



typedef struct
{
	u8 isActive;
	TriggerBox* trigBox; //holds pointers to trigger boxes
}SectorTrigger;

typedef struct
{
	u8 isActive;
	TriggerBox* trigBox; //check this trigger box to see if player is located in this area		
	u8 LOD;
	//--------Sector Setup--------
	u8 sectorCount; //number of scenes in this level
	// SectorTrigger* sectorTrig; //points to sector trig box that holds 
	// TriggerBox* sectorTrigBox; //holds pointers to trigger boxes
	TriggerBox* sectorTrig; //holds pointers to trigger boxes
}SceneTrigger;

typedef struct
{
	u8 isActive; //set active "isActive = 1;" when player is in this area
	TriggerBox* trigBox; //check this trigger box to see if player is located in this area				
	//--------Scene Setup--------
	u8 sceneCount; //number of scenes in this level
	SceneTrigger* scenetrig; //holds pointers to trigger boxes
}LevelTrigger;


typedef struct
{
	u8 levelCount; //number of levels/regions in the game. Each level will have an instance of the LevelTrigger class
	LevelTrigger* levelTrig; //holds pointers to trigger boxes
}WorldTrigger;







#endif