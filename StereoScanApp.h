#ifndef STEREOSCANAPP_H
#define STEREOSCANAPP_H

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "GL/gl.h"
#include "ScannedModel.h"
#include "StereoToXYZConverter.h"

class StereoScanApp : public ofBaseApp{

		ofVideoGrabber vidGrabber1;
		ofVideoGrabber vidGrabber2;

        ofxCvContourFinder 	contourFinder1;
        ofxCvContourFinder 	contourFinder2;

        ofxCvColorImage currentColorFrame1;
        ofxCvColorImage currentColorFrame2;

		ofxCvGrayscaleImage currentGrayFrame1;
		ofxCvGrayscaleImage currentGrayFrame2;

		ofxCvGrayscaleImage background1;
		ofxCvGrayscaleImage background2;

		ofxCvGrayscaleImage diff1;
		ofxCvGrayscaleImage diff2;

		ScannedModel vertices;
		StereoToXYZConverter converter;

		int threshold;
		bool bLearnBakground;
		unsigned int xRes, yRes;
		bool frame1Fresh;
		bool frame2Fresh;

		float xrot,yrot;
		float scale;

		Point3D modelCentroid;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

};

#endif // STEREOSCANAPP_H
