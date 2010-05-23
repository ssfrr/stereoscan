#include "StereoScanApp.h"
#include <GL/gl.h>


//--------------------------------------------------------------
void StereoScanApp::setup(){

    ofSetWindowShape(1200,800);
	xRes = 320;
	yRes = 240;
	vidGrabber1.setDeviceID(0);
	vidGrabber2.setDeviceID(1);
	vidGrabber1.initGrabber(xRes,yRes);
	vidGrabber2.initGrabber(xRes,yRes);
	//TODO: check that we actually got the right resolution
	currentColorFrame1.allocate(xRes,yRes);
	currentColorFrame2.allocate(xRes,yRes);

	currentGrayFrame1.allocate(xRes,yRes);
	currentGrayFrame2.allocate(xRes,yRes);

	background1.allocate(xRes,yRes);
	background2.allocate(xRes,yRes);

	diff1.allocate(xRes,yRes);
	diff2.allocate(xRes,yRes);

	bLearnBakground = true;
	threshold = 80;
	ofBackground(100,100,100);

	frame1Fresh = false;
	frame2Fresh = false;

	// add a bunch of random vertices for testing
	/*ofSeedRandom();
	for(int i = 0; i < 4000; i++) {
		vertices.addPoint(ofRandom(-200,200),ofRandom(-200,200),ofRandom(-200,200));
	}*/
	converter.setGeometry(8.12, 84.289, 84.289);
	ofSetFrameRate(24);
	ofSetVerticalSync(true);
	glPointSize(4);
}

//--------------------------------------------------------------
void StereoScanApp::update(){

	vidGrabber1.grabFrame();
	vidGrabber2.grabFrame();

	if(!frame1Fresh)
		frame1Fresh = vidGrabber1.isFrameNew();
	if(!frame2Fresh)
		frame2Fresh = vidGrabber2.isFrameNew();

	if (frame1Fresh && frame2Fresh){
		frame1Fresh = false;
		frame2Fresh = false;

		currentColorFrame1.setFromPixels(vidGrabber1.getPixels(), xRes, yRes);
		currentColorFrame2.setFromPixels(vidGrabber2.getPixels(), xRes, yRes);

		currentGrayFrame1 = currentColorFrame1;
		currentGrayFrame2 = currentColorFrame2;

		if (bLearnBakground == true){
			// the = sign copys the pixels from grayImage into
			// grayBg (operator overloading)
			background1 = currentGrayFrame1;
			background2 = currentGrayFrame2;
			bLearnBakground = false;
		}

		// take the abs value of the difference between background
		// and incoming and then threshold:
		diff1.absDiff(background1, currentGrayFrame1);
		diff1.threshold(threshold);
		diff2.absDiff(background2, currentGrayFrame2);
		diff2.threshold(threshold);

		contourFinder1.findContours(diff1, 1, 200, 10, false);
		contourFinder2.findContours(diff2, 1, 200, 10, false);

		// if there's a blob in both images
		if(contourFinder1.blobs.size() && contourFinder2.blobs.size()) {
			float x1,x2,y1,y2;
			x1 = contourFinder1.blobs[0].centroid.x;
			y1 = contourFinder1.blobs[0].centroid.y;
			x2 = contourFinder2.blobs[0].centroid.x;
			y2 = contourFinder2.blobs[0].centroid.y;
			Point3D vect = converter.getPoint(x1,y1,x2,y2);
			vertices.addPoint(vect.x,vect.y,vect.z);
		}
	}

}

//--------------------------------------------------------------
void StereoScanApp::draw(){

	unsigned int border = 10;
	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetColor(0xffffff);
	currentColorFrame1.draw(border, border);
//	currentGrayFrame1.draw(20, yRes + 20);
//	background1.draw(20, 2 * (yRes + 20));
//	diff1.draw(20,3 * (yRes + 20));

	currentColorFrame2.draw(2*border + xRes, border);
//	currentGrayFrame2.draw(20 + xRes, yRes + 20);
//	background2.draw(20 + xRes, 2 * (yRes + 20));
//	diff2.draw(20 + xRes,3 * (yRes + 20));

	// then draw the contours:

	ofFill();
	ofSetColor(0x333333);
	ofRect(border,(yRes + border) + border,xRes,yRes);
	ofSetColor(0xffffff);

	ofFill();
	ofSetColor(0x333333);
	ofRect(2*border+xRes,(yRes + border)+ border,xRes,yRes);
	ofSetColor(0xffffff);

	// draw each blob individually,
	for (int i = 0; i < contourFinder1.blobs.size(); i++){
		contourFinder1.blobs[i].draw(border,(yRes + border) + border);
	}

	// draw each blob individually,
	for (int i = 0; i < contourFinder2.blobs.size(); i++){
		contourFinder2.blobs[i].draw(2*border + xRes,(yRes + border) + border);
	}

    ofSetColor(20, 20, 20);
	glPushMatrix();
	glTranslatef(1100,200,-400);
	glRotatef(-mouseY,1,0,0);
	glRotatef(mouseX,0,1,0);
	float *pointArray = vertices.getVectData();
    glBegin(GL_POINTS);
		for(int i = 0; i < vertices.getNumPoints(); i++) {
        	glVertex3f((pointArray[i*3] - modelCentroid.x) *100,
					(pointArray[i*3+1] - modelCentroid.y) *100,
					(pointArray[i*3+2] - modelCentroid.z) *100);
		}
    glEnd();
	glPopMatrix();
	// finally, a report:

	ofSetColor(0xffffff);
	char reportStr[1024];
	sprintf(reportStr, "press ' ' to capture bg\nthreshold %i (press: +/-)\nnum points: %i, fps: %f", threshold, vertices.getNumPoints(), ofGetFrameRate());
	ofDrawBitmapString(reportStr, 20, 600);

}


//--------------------------------------------------------------
void StereoScanApp::keyPressed  (int key){

	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
		case 'c':
			modelCentroid = vertices.getCentroid();
			break;
	}
}

//--------------------------------------------------------------
void StereoScanApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void StereoScanApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void StereoScanApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void StereoScanApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void StereoScanApp::windowResized(int w, int h){

}

