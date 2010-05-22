#include "StereoToXYZConverter.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
	cout << "Initializing Default Converter\n";
	StereoToXYZConverter convert;
	assert(convert.getSeparation() == 254);
	assert(convert.getCam1Angle() == 45);
	assert(convert.getCam2Angle() == 45);
	assert(convert.getFOV() == 75);
	assert(convert.getXRes() == 640);
	assert(convert.getYRes() == 480);
	cout << "Default Converter Initialized Properly\n";
	
	return 0;
}
