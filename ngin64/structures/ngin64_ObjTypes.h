#ifndef NGIN64_OBJTYPES_H
#define NGIN64_OBJTYPES_H



typedef struct {
	int hours;
	int minutes;
	float seconds;

}g64_GameTimer;

typedef struct {
	float r;
	float g;
	float b;
	float a;
}Color;


typedef struct {
	//For use with collision tests

	Vector3 currentPos;
	Vector3 nextPos;

	Vector3 velocity;
	Vector3 centerMass;
	//Vector3 rotation;
	float speed;
	float gravityStrength;
	float rotation;
	//Vector3 max;	
}RigidBody;

typedef struct
{

	Vector3 pos;
	Vector3 rot;
	Vector3 scl;

	//Mtx matrix[3];

}GameObject; //NOTE: GameObjects are defined in objectDefs.h


typedef struct
{
	u8 animID; //NOTE: current animation 
	u8 animFrame; //NOTE: current frame of current animation
	//GFX (*staticModel);
	void(*displayList)();
	GLuint glDisplayList;
	//void* displayList; 
}StaticModel;

typedef struct
{
	GameObject obj; //pointer to game object (pos, rot, scl)
	StaticModel staticModel; //pointer to display List

	StaticModel staticModel_LOD[3]; //pointer to display List     
	TriggerBox trigBox;
	MeshColliderObj* groundCollider;
	MeshColliderObj* wallCollider;

	u8 pointsH;
	u8 pointsB;
	u8 pointsC;
	//short *wallColMeshSize;
	//MeshCollider *wallMeshCol; //vertex positions of collision (float, float, float)
	//MeshColliderTri *wallColTri; //collision mesh triangles (int,int,int)

//	Gfx* DL; //pointer to display list for object	
}g64_EnvObjectPrefab;







typedef struct {

	//Vector2 activeTile;
	int column;
	int row;
	Vector3 pos;
}CursorObject;

typedef struct
{
	GameObject obj; //Note:pointer to game object (pos, rot, scl)
	GameObject* camLook; //Note: GameObject pointer of object camera is currently looking at (ex player character)
	Vector3 camLookPoint;
	Vector3 cameraOffset; //Note: distance to offset from "camLook"
	Vector3 nextPosition; //Note: distance to offset from "camLook"

	float cameraOrbit; //Note:Orbital position around player character (0-360 degrees)
	float audioOrbit; //Note: orbital position of the audio channel 
	float distance; //Note: Current distance 
	float adjDistance;	//Note: adjusted distance when colliding with wall or object
	float nearPosition;	//Note: used for nearClipping 
	u8 againstWall;

}CameraObject;


/*TO DO NOTE - Continue importing object, data and transform types for NGin64 objectDefs.h, transformDefs.h etc*/

typedef struct {
	//For use with collision tests

	Color backgroundColor;
	Color fogColor;
	u16 fogNear;
	u16 fogFar;	
	u16 nearPlane;
	u16 farPlane;

}ViewSettings;

#define INPUT_STICK 0;
#define INPUT_DPAD 1;
#define INPUT_C_UP 2;
#define INPUT_C_DOWN 3;
#define INPUT_C_LEFT 4;
#define INPUT_C_RIGHT 5;
#define INPUT_A 6;
#define INPUT_B 7;
#define INPUT_Z 8;
#define INPUT_L 9;
#define INPUT_R 10;

typedef struct {

	u8 binding;
	Vector3 vector3;
	char name[16];

}InputVector3; //For 3D inputs

typedef struct {

	u8 binding;
	Vector2 vector2;
	char name[16];

}InputVector2; //For 2D inputs

typedef struct {

	u8 binding;
	u8 hold; //Will continue to fire 
	u8 tap; //Will not fire a second time until letting go
	char name[16];

}InputButton;




#endif