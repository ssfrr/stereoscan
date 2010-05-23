#include "ScannedModel.h"

ScannedModel::ScannedModel() {
	// ARRAY_SIZE_INIT should be a multiple of 3
	const int ARRAY_SIZE_INIT = 3000;
	nextFreeIndex = 0;
	vectArray = new float[ARRAY_SIZE_INIT];
	arraySize = ARRAY_SIZE_INIT;
}

void ScannedModel::addPoint(float x, float y, float z) {
	if(nextFreeIndex + 2 >= arraySize)
		growArray();
	vectArray[nextFreeIndex++] = x;
	vectArray[nextFreeIndex++] = y;
	vectArray[nextFreeIndex++] = z;
}

Point3D ScannedModel::getCentroid() {
	Point3D centroid;
	double xsum = 0;
	double ysum = 0;
	double zsum = 0;
	for(unsigned int i = 0; i < nextFreeIndex / 3; i++) {
		xsum += vectArray[i*3];
		ysum += vectArray[i*3+1];
		zsum += vectArray[i*3+2];
	}
	centroid.x = xsum / (nextFreeIndex / 3);
	centroid.y = ysum / (nextFreeIndex / 3);
	centroid.z = zsum / (nextFreeIndex / 3);

	return centroid;
}

void ScannedModel::removeLastPoint() {
	if(nextFreeIndex >= 3)
		nextFreeIndex -= 3;
}

void ScannedModel::growArray() {
 	float *newArray = new float[arraySize * 2];
	for(unsigned int i = 0; i < arraySize; i++)
		newArray[i] = vectArray[i];
	delete[] vectArray;
	vectArray = newArray;
	arraySize *= 2;
}

unsigned int ScannedModel::getNumPoints() {
	return nextFreeIndex / 3;
}

float *ScannedModel::getVectData() {
	return vectArray;
}
