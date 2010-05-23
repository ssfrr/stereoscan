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
