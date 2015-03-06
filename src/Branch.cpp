#include "Branch.h"

Branch::Branch()
{
    //ctor
    	//mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
}

//--------------------------------------------------------------
void Branch::setup(ofVec3f *_drawPoint, float *_startThickness, int *_angle, int *_parentAngle, ofVec3f *_parentStart, int _branchCount){
    startPoint = *_drawPoint;
    drawPoint = ofVec3f(0,0,0);
    startThickness = *_startThickness;
    branchCount = _branchCount;
    parentAngle = *_parentAngle;
    parentStart = *_parentStart;
    if ( abs(parentAngle + *_angle) > 90 && parentAngle != 0) {
        angle = *_angle*-1;
    } else {
        angle = *_angle;
    }

    bloomset = false;
    bloomSpacing = int(ofRandom(32,60));
    int bloomNum = 2;

    for (int i = 0; i < bloomNum; i++){

        int b = int(ofRandom(32,60));
        bloomNums.push_back(b);
    }

}

//--------------------------------------------------------------
void Branch::update(){
    vel = ofVec3f(ofRandomf(),ofRandomuf()*8*-1,0);
    vel.x+=sin(drawPoint.y*0.07)*2;

    if (thickness > 0){
    points.push_back(drawPoint);
    drawPoint += vel;

    }

    for (int i = 0; i < bloomNums.size(); i++){
        int locIndex = bloomNums[i];
        if (locIndex==points.size()){
            Bloom *b = new Bloom();
            b->setup(&points[locIndex]);
            blooms.push_back(b);
        }

    }

    for (int i = 0; i< blooms.size(); i++){
        blooms[i]->update();

    }

}

//--------------------------------------------------------------
void Branch::draw(ofColor _treeColor){

    float branchNoise = ofNoise( branchCount, ofGetFrameNum() * 0.01 );
    float parentNoise = ofNoise( branchCount - 1, ofGetFrameNum() * 0.01 );

    branchNoise *= 0.65;
    parentNoise *= 0.65;

    ofTranslate(parentStart);

    ofRotate(parentAngle+parentNoise);
    ofPushMatrix();
    ofTranslate(startPoint);

    ofRotate(angle + branchNoise);
        ofSetColor(_treeColor);

    ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	for(int i = 1; i < points.size(); i++){

		ofVec3f thisPoint = points[i-1];
		ofVec3f nextPoint = points[i];

		ofVec3f direction = (nextPoint - thisPoint);
		float distance = direction.length();

		ofVec3f dirNormal = direction.normalized();

		ofVec3f toTheLeft = dirNormal.getRotated(-90, ofVec3f(0,0,1));
		ofVec3f toTheRight = dirNormal.getRotated(90, ofVec3f(0,0,1));

		thickness = startThickness+abs(sin(i*0.1)*2)-i*0.06;

        if (thickness > 0){
		ofVec3f leftPoint = thisPoint+toTheLeft*(thickness);
		ofVec3f rightPoint = thisPoint+toTheRight*(thickness);

		mesh.addVertex(leftPoint);
		mesh.addVertex(rightPoint);
        }
	}

	mesh.draw();

    for (int i = 0; i< blooms.size(); i++){
        blooms[i]->draw();
    }

	ofPopMatrix();

}



//--------------------------------------------------------------

int Branch::getSize(){
    int branchSize = points.size();
    return branchSize;
}

//--------------------------------------------------------------

ofVec3f Branch::getDrawPoint(){
    return drawPoint;
}


//--------------------------------------------------------------

ofVec3f Branch::getBranchPoint(int _index){
    return points[_index];
}

//--------------------------------------------------------------
Branch::~Branch()
{
    //dtor
}
