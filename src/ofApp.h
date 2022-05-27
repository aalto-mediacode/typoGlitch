#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void createFbo();
		void fillFbo();
		void createText();
		void refresh(int &waat);
		void refresh2(string &waat);
		void refresh3(int &waat);
		void refresh4(float &waat);


		
		float windowWidth, windowHeight;
		ofTrueTypeFont myFont;

		bool bHide;
		ofxPanel gui;
		ofxIntSlider squareL;
		ofxIntSlider gridW, gridH;
		ofxIntSlider spaceX, spaceY;
		ofxTextField textInput;
		ofxFloatSlider noiseF;


		ofxIntSlider rL, rW, rH;
		//float squareL;
		int bgC;

		vector<vector<ofFbo>> myFbo;	

		bool setupEnd;
};
