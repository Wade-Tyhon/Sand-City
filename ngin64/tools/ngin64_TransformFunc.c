#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../nGin64.h"





Vector3 RotateCameraAround(Vector3 basePosition, Vector3 centerPoint, double angleInDegrees)
{

	//double angleInRadians = ((angleInDegrees) * 3.14f/180.0f);
	double angleInRadians = ((angleInDegrees) * 0.01744f);
	double cosTheta = cosf(angleInRadians);
	double sinTheta = sinf(angleInRadians);

	Vector3 calculatePosition;

	calculatePosition.x = (cosTheta * (basePosition.x - centerPoint.x) - sinTheta * (basePosition.y - centerPoint.y) + centerPoint.x);
	calculatePosition.y = (sinTheta * (basePosition.x - centerPoint.x) + cosTheta * (basePosition.y - centerPoint.y) + centerPoint.y);
	calculatePosition.z = basePosition.z;




	return calculatePosition;

}