#include "ofMain.h"
#include "ofApp.h"
#include "Branch.h"
#include "Bloom.h"
#include "Petal.h"
#include "Tree.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1280,720,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
