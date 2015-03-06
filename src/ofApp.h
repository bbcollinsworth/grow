#pragma once

#include "ofMain.h"
#include "Branch.h"
#include "Bloom.h"
#include "Petal.h"
#include "Tree.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void makeBloom(ofVec3f _bloomInit);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        vector <Tree *> trees;
		vector <Branch> branches;
		vector <Bloom *> bloomsMain;

		bool petalMade;
		bool record;

		ofVec3f prevBloom;

		float targetFrame;
		float dragStart;

		int recStart;

		string currentDate;

        ofEasyCam       cam;
        ofLight         light;


};
