#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../nGin64.h"


/*-------------------------------NGin64 Vector Functions---------------------------*/



void SetVector3(Vector3* setVector, float x, float y, float z)
{
	setVector->x = x;
	setVector->y = y;
	setVector->z = z;
}

void SetVector2(Vector2* setVector, float x, float y)
{
	setVector->x = x;
	setVector->y = y;
}

float vectorDot(Vector3 vectorA, Vector3 vectorB)
{
	float sum = 0.0f;

	sum += vectorA.x * vectorB.x;
	sum += vectorA.y * vectorB.y;
	sum += vectorA.z * vectorB.z;

	return sum;
}

Vector3 vectorCross(Vector3 vectorA, Vector3 vectorB)
{
	Vector3 sum;

	sum.x = (vectorA.y * vectorB.z) - (vectorA.z * vectorB.y);
	sum.y = (vectorA.z * vectorB.x) - (vectorA.x * vectorB.z);
	sum.z = (vectorA.x * vectorB.y) - (vectorA.y * vectorB.x);

	return sum;
}

float vectorScalarTriple(Vector3 vectorA, Vector3 vectorB, Vector3 vectorC)
{
	float sum;

	sum = vectorDot(vectorA, vectorCross(vectorB, vectorC));

	return sum;
}

u8 vectorCompare(Vector3 vectorA, Vector3 vectorB, float precision)
{
	if (((vectorA.x - vectorB.x) + (vectorA.y - vectorB.y) + (vectorA.z - vectorB.z)) <= precision)
		return 1;

	else
		return 0;
}

u8 positionCompare(Vector3 vectorA, Vector3 vectorB, float precision)
{

	if ((vectorA.x - vectorB.x) <= fabsf(precision) && (vectorB.x - vectorA.x) <= fabsf(precision))
		if ((vectorA.y - vectorB.y) <= fabsf(precision) && (vectorB.y - vectorA.y) <= fabsf(precision))
			if ((vectorA.z - vectorB.z) <= fabsf(precision) && (vectorB.z - vectorA.z) <= fabsf(precision))
				return 1;
				

	return 0;
}

Vector3 vectorAdd_R(Vector3 vectorA, Vector3 vectorB)
{
	Vector3 newVector = { (vectorA.x + vectorB.x),(vectorA.y + vectorB.y),(vectorA.z + vectorB.z) };
	return newVector;
}

Vector3 vectorSubtract_R(Vector3 vectorA, Vector3 vectorB)
{
	Vector3 newVector = { (vectorA.x - vectorB.x),(vectorA.y - vectorB.y),(vectorA.z - vectorB.z) };
	return newVector;
}

Vector3 vectorScale_R(Vector3 vectorA, float scaler)
{

	Vector3 newVector = { (vectorA.x * scaler),(vectorA.y * scaler),(vectorA.z * scaler) };

	return newVector;
}

float tempFloat = 0;
void VectorNormalize(Vector3* vector)
{
	float length = sqrtf(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);

	if (length > 0.0f)
	{
		//vector->x /= length;
		//vector->y /= length;
		//vector->z /= length;
		tempFloat = 1.0f / length;
		vector->x *= tempFloat;
		vector->y *= tempFloat;
		vector->z *= tempFloat;
	}
}


void VectorAdd(Vector3* vectorSum, Vector3 vectorA, Vector3 vectorB)
{
	vectorSum->x = vectorA.x + vectorB.x;
	vectorSum->y = vectorA.y + vectorB.y;
	vectorSum->z = vectorA.z + vectorB.z;

}

void VectorScale(Vector3* vectorToScale, float scaler)
{
	vectorToScale->x = vectorToScale->x * scaler;
	vectorToScale->y = vectorToScale->y * scaler;
	vectorToScale->z = vectorToScale->z * scaler;
}