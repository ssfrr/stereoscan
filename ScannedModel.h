#ifndef SCANNEDMODEL_H
#define SCANNEDMODEL_H

class ScannedModel {
	public:
	ScannedModel();
	void addPoint(float x, float y, float z);
	void removeLastPoint();
	unsigned int getNumPoints();
	float *getVectData();

	private:
	void growArray();
	float *vectArray;
	unsigned int nextFreeIndex;
	unsigned int arraySize;
};

#endif // SCANNEDMODEL_H
