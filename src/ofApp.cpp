#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	setupEnd = false;
	bgC = 10;
	//squareL = 300;
	ofSetBackgroundColor(0);

	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();

	//GUI SETTINGS
	bHide = false;
	ofxGuiSetDefaultHeight(32);
	ofxGuiSetDefaultWidth(256);
	ofxGuiSetBorderColor(32);
	ofxGuiSetFillColor(ofColor(24));
	ofxGuiSetTextColor(ofColor::white);
	ofxGuiSetHeaderColor(ofColor(12));
	ofxGuiSetBackgroundColor(ofColor::black);

	//GUI SETUP
	gui.setup();
	gui.add(squareL.setup("size", 450, 50, 600));
	gui.add(gridW.setup("grid W", 5, 1, 25));
	gui.add(gridH.setup("grid H", 5, 1, 25));

	gui.add(spaceX.setup("space X", 10, 0, 30));
	gui.add(spaceY.setup("space Y", 10, 0, 30));
	gui.add(noiseF.setup("noise factor", 3.0, 0.0, 10.0));


	//gui.add(rL.setup("lato", 300, 25, 500));
	//gui.add(rW.setup("X", 38, 0, 100));
	//gui.add(rH.setup("Y", 50, 0, 100));
	gui.add(textInput.setup("Your word", "W"));
	//myFont.load("SourceCodePro-Medium.ttf", squareL);

	//w = 0 --> load the font ttf file
	int w = 0;
	//GUI CALLBACKS
	squareL.addListener(this, &ofApp::refresh3);
	gridW.addListener(this, &ofApp::refresh);
	gridH.addListener(this, &ofApp::refresh);
	spaceX.addListener(this, &ofApp::refresh);
	spaceY.addListener(this, &ofApp::refresh);
	textInput.addListener(this, &ofApp::refresh2);
	noiseF.addListener(this, &ofApp::refresh4);

	   
	//FBO
	refresh(w);
}

void ofApp::refresh4(float &waat) {
	int temp = 1;
	refresh(temp);
}

void ofApp::refresh3(int &waat) {
	int temp = 0;
	refresh(temp);
}

void ofApp::refresh2(string &waat) {
	int temp = 1;
	refresh(temp);
}

void ofApp::refresh(int &waat) {
	myFbo.clear();
	ofSetColor(0);
	int n = 3;
	float squareLn = squareL * n;
	//cout << "refresh - " << "square L = " << squareL << endl;
	ofDrawRectangle(windowWidth / 2 - squareLn / 2, windowHeight / 2 - squareLn / 2, squareLn, squareLn);
	//cout << "elements should be 0 = " << myFbo.size() << endl;
	if (waat == 0) { myFont.load("SourceCodePro-Medium.ttf", squareL); };
	createText();
	createFbo();
	fillFbo();
	//cout << "test" << endl;
	setupEnd = true;
}

void ofApp::createText() {
	//cout << "create text - " << "square L = " << squareL << endl;

	ofSetColor(225);
	//myFont.drawString(textInput, windowWidth / 2 - squareL * rW / 100, windowHeight / 2 + squareL * rH / 100);
	myFont.drawString(textInput, windowWidth / 2 - squareL * 38 / 100, windowHeight / 2 + squareL * 50 / 100);
}

void ofApp::createFbo() {
	//cout << "FBO allocation" << endl;
	//cout << "FBO allocation - " << "square L = " << squareL << endl;


	for (int x = 0; x < gridW; x++) {
		vector<ofFbo> tempFboVec;
		for (int y = 0; y < gridH; y++) {
			ofFbo tempFbo;
			tempFbo.allocate(squareL / gridW, squareL / gridH, GL_RGBA);
			tempFboVec.push_back(tempFbo);

			//cout << "x " << x << " - " << "y " << y << endl;
		}
		myFbo.push_back(tempFboVec);
	}
}

void ofApp::fillFbo() {
	//cout << "FBO fill with image" << endl;
	//cout << "FBO fill - " << "square L = " << squareL << endl;

	ofImage img;
	img.grabScreen(windowWidth / 2 - squareL / 2, windowHeight / 2 - squareL / 2, squareL, squareL);
	//for no reason the image needs to be rotated if taken in the setup()
	if (!setupEnd) { img.rotate90(2); };

	for (int x = 0; x < gridW; x++) {
		for (int y = 0; y < gridH; y++) {
			//float x1 = windowWidth / 2 - squareL / 2 + x * squareL / gridW;
			//float y1 = windowHeight / 2 - squareL / 2 + y * squareL / gridH;
			//img.rotate90(2);
			//img.save("screenshot.png");

			//cout << "x " << x << " - " << "y " << y << endl;

			float x2 = -x * squareL / gridW;
			float y2 = -y * squareL / gridH;


			myFbo[x][y].begin();
			//img.draw(0, 0);
			img.draw(x2, y2);
			myFbo[x][y].end();
		}
	}

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------

void ofApp::draw(){

	if (!bHide) {
		gui.draw();
	}

	//FBO DRAW
	if (setupEnd == true) {
		//cout << "gridW " << gridW << endl;
		//cout << "gridH " << gridH << endl;
		//cout << "number of FBO items = " << myFbo.size() << endl;
		//cout << "draw - " << "square L = " << squareL << endl;

		for (int x = 0; x < gridW; x++) {
			for (int y = 0; y < gridH; y++) {

				float fboW = squareL / gridW;
				float fboH = squareL / gridH;

				float center = windowHeight / 2 - squareL / 2;

				float xInc1 = x * spaceX; //+ x * sin(ofGetElapsedTimef() * 3);
				float yInc1 = y * spaceY; //+ y * sin(ofGetElapsedTimef() * 3);

				float xInc2 = ofMap(ofNoise(ofGetElapsedTimef() + noiseF * x + noiseF * y), 0, 1, -10 , 10);
				float yInc2 = ofMap(ofNoise(ofGetElapsedTimef() + noiseF * x + noiseF * y), 0, 1, -10, 10);


				float x1 = center + x * fboW + xInc1 + xInc2;
				float y1 = center + y * fboH + yInc1;

				myFbo[x][y].draw(x1 , y1);
				//cout << "x " << x << " - " << "y " << y << endl;

			}
		}

		//display also fbo in different position
		//float pos = 0;
		//for (int x = 0; x < gridW; x++) {
		//	for (int y = 0; y < gridH; y++) {
		//		pos += squareL / gridW; 
		//		myFbo[x][y].draw(pos, 0);
		//	}
		//}

	}



	//for (int x = 0; x < gridW; x++) {
	//	for (int y = 0; y < gridH; y++) {
	//		float x1 = windowWidth / 2 - squareL / 2 + x * squareL / gridW;
	//		float y1 = windowHeight / 2 - squareL / 2 + y * squareL / gridH;
	//
	//		ofNoFill();
	//		ofSetColor(127);
	//		ofDrawRectangle(x1, y1, squareL / gridW, squareL / gridH);
	//	}
	//}



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'h') {
		bHide = !bHide;
	}

	if (key == 'x') {
		ofImage myScreenshot;
		myScreenshot.grabScreen(windowWidth / 2 - squareL / 2, windowHeight / 2 - squareL / 2,  squareL, squareL);
		myScreenshot.save("scr.png");
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){}
//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	cout << windowWidth << " x " << windowHeight << endl;
}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){}
