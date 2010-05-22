#ifndef VIDCAM_H
#define VIDCAM_H

class VidCam {
	unsigned int Xres;
	unsigned int Yres;
	float FOV;

	public:
	Vidcam(Xres,Yres,FOV);
	void setResolution(unsigned int Xres, unsigned int Yres);
	void setFOV(float FOV);
	unsigned int getXres();
	unsigned int getYres();
	unsigned int getFOV();
}

#endif // VIDCAM_H
