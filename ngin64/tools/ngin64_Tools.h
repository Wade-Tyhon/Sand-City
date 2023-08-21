#ifndef NGIN64_TOOLS_H
#define NGIN64_TOOLS_H

	/*-------------------------------NGin64 System Functions---------------------------*/


	extern float lerp(float val_1, float val_2, float time);
	extern float lerpInt(int val_1, int val_2, float time);

	extern void gin64_InitTimers(); //should only be called once per boot
	extern void gin64_SetDeltaTime();
	extern float gin64_GetDeltaTime();

	extern bool gin64_EventKeyCheck(char* keyA, char* keyB);


	/*-------------------------------NGin64 Transform Functions---------------------------*/

	extern Vector3 RotateCameraAround(Vector3 basePosition, Vector3 centerPoint, double angleInDegrees);


	/*-------------------------------NGin64 Vector Functions---------------------------*/

	extern void SetVector3(Vector3* setVector, float x, float y, float z);
	extern void SetVector2(Vector2* setVector, float x, float y);
	extern float vectorDot(Vector3 vectorA, Vector3 vectorB);
	extern Vector3 vectorCross(Vector3 vectorA, Vector3 vectorB);
	extern float vectorScalarTriple(Vector3 vectorA, Vector3 vectorB, Vector3 vectorC);
	extern u8 vectorCompare(Vector3 vectorA, Vector3 vectorB, float precision);
	extern u8 positionCompare(Vector3 vectorA, Vector3 vectorB, float precision);

	//Note: functions ending in _R return a variable
	extern Vector3 vectorAdd_R(Vector3 vectorA, Vector3 vectorB);
	extern Vector3 vectorSubtract_R(Vector3 vectorA, Vector3 vectorB);
	extern Vector3 vectorScale_R(Vector3 vectorA, float scaler);

	//Note: functions ending in _P require a pointer to store the resulting calculation
	extern void VectorNormalize_P(Vector3* vector);
	extern void VectorAdd_P(Vector3* vectorSum, Vector3 vectorA, Vector3 vectorB);
	extern void VectorScale_P(Vector3* vectorToScale, float scaler);

#endif