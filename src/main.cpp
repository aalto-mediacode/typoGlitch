#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	float scaleF = 2;
	ofSetupOpenGL(1024*scaleF,768*scaleF,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
