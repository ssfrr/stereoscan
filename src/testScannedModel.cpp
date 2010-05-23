#include <iostream>
#include "ScannedModel.h"
#include <cassert>
using namespace std;

void testInitializesToZeroPoints() {
	cout << "Initializes to Zero Points";
	ScannedModel model;
	assert(model.getNumPoints() == 0);
	cout << "  --PASSED\n";
}

void testAddingPointIncrementsNumPoints() {
	cout << "Adding Point Increments NumPoints";
	ScannedModel model;
	model.addPoint(0,0,0);
	assert(model.getNumPoints() == 1);
	model.addPoint(0,0,0);
	assert(model.getNumPoints() == 2);
	model.addPoint(0,0,0);
	assert(model.getNumPoints() == 3);
	cout << "  --PASSED\n";
}

void testPointCanBeRetreived() {
	cout << "Points can be retrieved";
	ScannedModel model;
	model.addPoint(0,0,0);
	model.addPoint(1,1,1);
	model.addPoint(2,2,2);
	float *vectArray = model.getVectData();
	for(unsigned int i = 0; i < 3; i++) {
		float x = vectArray[i*3];
		float y = vectArray[i*3+1];
		float z = vectArray[i*3+2];
		assert(x == i);
		assert(y == i);
		assert(z == i);
	}
	cout << "  --PASSED\n";
}

void testGrowDoesntCrash() {
	cout << "Grow Doesn't Crash";
	ScannedModel model;
	for(unsigned int i = 0; i < 4000; i++)
		model.addPoint(0,0,0);
	cout << "  --PASSED\n";
}


int main() {
	testInitializesToZeroPoints();
	testAddingPointIncrementsNumPoints();
	testPointCanBeRetreived();
	testGrowDoesntCrash();
	return 0;
}
