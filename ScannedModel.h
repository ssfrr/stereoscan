#ifndef SCANNEDMODEL_H
#define SCANNEDMODEL_H

#include "Point3D.h"
#include <fstream>
using namespace std;
class ScannedModel {
	public:
	ScannedModel();
	void addPoint(float x, float y, float z);
	Point3D getCentroid();
	void removeLastPoint();
	unsigned int getNumPoints();
	float *getVectData();
	friend ostream &operator<<(ostream &os, const ScannedModel &model);

	private:
	void growArray();
	float *vectArray;
	unsigned int nextFreeIndex;
	unsigned int arraySize;
};

#endif // SCANNEDMODEL_H
