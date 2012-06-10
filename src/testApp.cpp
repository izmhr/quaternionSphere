#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	sphere = QuaternionSphere(100, 4);
	sphere.init();
	ofEnableSmoothing();

	cam.setDrag(0.3);
	cam.setDistance(600);

	glEnable(GL_DEPTH_TEST);

	r = 0.0;
}

//--------------------------------------------------------------
void testApp::update(){
	sphere.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	//ofTranslate(ofGetWidth()/2.0, ofGetHeight()/2.0, 0.0);
	cam.begin();
	ofRotateY(r+=0.1);

	//ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	sphere.draw();
	//ofDisableBlendMode();
	cam.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	cout << key << endl;
	if( 49 <= key && key <= 57 ) {
		sphere.queResetDivision(key-48);
		return;
	}
	if( key == 'r'){
		sphere.toggleRadiusNoise();
	}
	if( key == 'c') {
		sphere.toggleColorize();
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}