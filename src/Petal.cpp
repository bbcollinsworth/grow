#include "Petal.h"

Petal::Petal()
{
    //ctor
}


//--------------------------------------------------------------
void Petal::setup(ofVec3f _drawPoint, ofFloatColor _petalColor, int _bloomSize){
    startPoint = _drawPoint;
    drawPoint = ofVec3f(0,-5,0);

    petalColor = _petalColor;
    petalLength = _bloomSize;


}

//--------------------------------------------------------------
void Petal::update(){

    float zFactor = ofRandomuf()*2;
    if (points.size() < petalLength){
    vel = ofVec3f(ofRandomf()-ofRandomf(),ofRandomuf()*4*-1,(zFactor/zFactor*0.7+0.1));
    points.push_back(drawPoint);
    drawPoint += vel;
    }

}

//--------------------------------------------------------------
void Petal::draw(float _noise){

    ofPushMatrix();
    ofRotate(_noise,1,1,1);

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

		float thickness = (points.size()-i)*i*0.09;

        float colorChange = (points.size()-i)*0.015;

        if (thickness > 0){
		ofVec3f leftPoint = thisPoint+toTheLeft*(thickness);
		ofVec3f rightPoint = thisPoint+toTheRight*(thickness);

		mesh.addVertex(leftPoint);
		mesh.addColor(ofFloatColor(petalColor.r,petalColor.g-colorChange,petalColor.b-colorChange));
		mesh.addVertex(rightPoint);
		mesh.addColor(ofFloatColor(petalColor.r,petalColor.g-colorChange,petalColor.b-colorChange));
        }
	}


	mesh.draw();

    ofPopMatrix();

}

Petal::~Petal()
{
    //dtor
}
