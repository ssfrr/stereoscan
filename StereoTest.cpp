#include "StereoToXYZConverter.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

void testIsInitializedDefault() {
	cout << "Initializing Default Converter";
	StereoToXYZConverter convert;
	assert(convert.getSeparation() == 254);
	assert(convert.getCam1Angle() == 45);
	assert(convert.getCam2Angle() == 45);
	assert(convert.getFOV() == 75);
	assert(convert.getXRes() == 640);
	assert(convert.getYRes() == 480);
	cout << "  --PASSED\n";
}

void testIsInitializedArguments() {
	cout << "Initializing Converter with Args";
	StereoToXYZConverter convert(150, 15, 15, 56, 320, 240);
	assert(convert.getSeparation() == 150);
	assert(convert.getCam1Angle() == 15);
	assert(convert.getCam2Angle() == 15);
	assert(convert.getFOV() == 56);
	assert(convert.getXRes() == 320);
	assert(convert.getYRes() == 240);
	cout << "  --PASSED\n";
}

void testReturnsIntersectionPointForZeroInput() {
	cout << "Returns Intersection Point for Zero Input";
	StereoToXYZConverter convert;
	Point3D origin = convert.getPoint(0,0,0,0);
	assert(abs(origin.x) < 0.0001);
	assert(abs(origin.y - 127) < 0.0001);
	assert(abs(origin.z) < 0.0001);
	cout << "  --PASSED\n";
}

void testReturnsElevatedPointForPositiveYInput() {
	cout << "Returns Elevated Point for Positive Y Input";
	StereoToXYZConverter convert;
	Point3D origin = convert.getPoint(0,10,0,10);
	assert(origin.z > 0);
	cout << "  --PASSED\n";
}

void testReturnsDepressedPointForNegativeYInput() {
	cout << "Returns Depressed Point for Negative Y Input";
	StereoToXYZConverter convert;
	Point3D origin = convert.getPoint(0,-10,0,-10);
	assert(origin.z < 0);
	cout << "  --PASSED\n";
}

void testReturnsCorrectPointInPlane() {
	cout << "Returns Correct Point In Plane";
	StereoToXYZConverter convert;
	Point3D origin = convert.getPoint(-21.510656,0,69.152786,0);
	assert(abs(origin.x - 10) < 0.0001);
	assert(abs(origin.y - 147) < 0.0001);
	assert(abs(origin.z) < 0.0001);
	cout << "  --PASSED\n";
}

void testReturnsCorrectPointAbovePlane() {
	cout << "Returns Correct Point Above Plane";
	StereoToXYZConverter convert;
	Point3D origin = convert.getPoint(-21.510656,60.629079,69.152786,64.814613);
	assert(abs(origin.x - 10) < 0.0001);
	assert(abs(origin.y - 147) < 0.0001);
	assert(abs(origin.z - 20) < 0.0001);
	cout << "  --PASSED\n";
}


int main() {
	testIsInitializedDefault();
	testIsInitializedArguments();
	testReturnsIntersectionPointForZeroInput();
	testReturnsElevatedPointForPositiveYInput();
	testReturnsDepressedPointForNegativeYInput();
	testReturnsCorrectPointInPlane();
	testReturnsCorrectPointAbovePlane();
	return 0;
}

