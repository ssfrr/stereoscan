#include <cmath>
#include "StereoToXYZConverter.h"

StereoToXYZConverter::StereoToXYZConverter() {
	camSeparation = 254;
	cam1Angle = 45;
	cam2Angle = 45;
	FOV = 75;
	xRes = 640;
	yRes = 480;
}

StereoToXYZConverter::StereoToXYZConverter(float camSeparation, float cam1Angle,
		float cam2Angle, float FOV, unsigned int xRes, unsigned int yRes) {
	this->camSeparation = camSeparation;
	this->cam1Angle = cam1Angle;
	this->cam2Angle = cam2Angle;
	this->FOV = FOV;
	this->xRes = xRes;
	this->yRes = yRes; 
}

void StereoToXYZConverter::setGeometry(float camSeparation, float cam1Angle, float cam2Angle) {
	this->camSeparation = camSeparation;
	this->cam1Angle = cam1Angle;
	this->cam2Angle = cam2Angle;
}

void StereoToXYZConverter::setSeparation(float camSeparation) {
	this->camSeparation = camSeparation;
}

void StereoToXYZConverter::setcam1Angle(float angle) {
	this->cam1Angle = angle;
}

void StereoToXYZConverter::setcam2Angle(float angle) {
	this->cam2Angle = angle;
}

void StereoToXYZConverter::setCamera(float FOV, 
		unsigned int xRes, unsigned int yRes) {
	this->FOV = FOV;
	this->xRes = xRes;
	this->yRes = yRes; 
}

Point3D StereoToXYZConverter::getPoint(float x1, float y1, float x2, float y2) {
	// calculate the location in the plane parallel to the floor
	Point3D outPoint;
	float horizToDiagRatio = xRes / sqrt(xRes * xRes + yRes * yRes);
	float xFOV = horizToDiagRatio * FOV;
	float deflection1 = x1 * xFOV / xRes;
	float deflection2 = x2 * xFOV / xRes;
	float A = cos(cam1Angle - deflection1);
	float B = cos(cam2Angle + deflection2);
	float C = sin(cam1Angle - deflection1);
	float D = -sin(cam1Angle + deflection1);
	float r1 = camSeparation * D / ((A * D) - (B * C));
	float r2 = -camSeparation * C / ((A * D) - (B * C));

	outPoint.x = r1 * A - camSeparation / 2;
	outPoint.y = r1 * C;

	// Calculate the vertical component
	float vertToDiagRatio = yRes / sqrt(xRes * xRes + yRes * yRes);
	float yFOV = vertToDiagRatio * FOV;
	float elevation1 = y1 * yFOV / yRes;
	float elevation2 = y2 * yFOV / yRes;

	// average the altitude calculated from the 2 cameras
	outPoint.z = (r1 * tan(elevation1) + r2 * tan(elevation2)) / 2;
	return outPoint;
}

float StereoToXYZConverter::getSeparation() {
	return camSeparation;
}

float StereoToXYZConverter::getCam1Angle() {
	return cam1Angle;
}

float StereoToXYZConverter::getCam2Angle() {
	return cam2Angle;
}

float StereoToXYZConverter::getFOV() {
	return FOV;
}

unsigned int StereoToXYZConverter::getXRes() {
	return xRes;
}

unsigned int StereoToXYZConverter::getYRes() {
	return yRes;
}
