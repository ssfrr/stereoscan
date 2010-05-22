
#ifndef STEREOTOXYZCONVERTER_H
#define STEREOTOXYZCONVERTER_H

#include "Point3D.h"

class StereoToXYZConverter {
	// camSeparation is in cm
	float camSeparation;
	// camera angles are in degrees off of the line connecting the cameras
	float cam1Angle;
	float cam2Angle;
	// diagonal field-of-view for cameras in degrees
	float FOV;
	unsigned int xRes;
	unsigned int yRes;

	public:
	StereoToXYZConverter();
	StereoToXYZConverter(float camSeparation, float cam1Angle, float cam2Angle,
			float FOV, unsigned int xRes, unsigned int yRes);
	void setGeometry(float camSeparation, float cam1Angle, float cam2Angle);
	void setSeparation(float camSeparation);
	void setcam1Angle(float angle);
	void setcam2Angle(float angle);
	void setCamera(float FOV, unsigned int xRes, unsigned int yRes);
	Point3D getPoint(float x1, float y1, float x2, float y2);
}
#endif // STEREOTOXYZCONVERTER_H
