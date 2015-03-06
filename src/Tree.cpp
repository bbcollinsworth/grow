#include "Tree.h"

Tree::Tree()
{
    //ctor
}

void Tree::setup(ofVec3f *_treeStart, int *_startAngle, int _treeCount){

   treeStart = *_treeStart;
   startAngle = *_startAngle;
   //float startY = ofRandomHeight()*0.5+ofGetHeight()*0.5;
    Branch * trunk = new Branch();
    startThickness = 5;
    parentAngle = 0;
    parentStart = ofVec3f(0,0,0);
    trunk->setup(&treeStart,&startThickness,&startAngle,&parentAngle,&parentStart,branches.size());
    //trunk.setup(ofVec3f(ofRandomWidth()*0.75,ofGetHeight(),0),5,20,0,ofVec3f(0,0,0));
    branches.push_back(trunk);

    int branchB = int(ofRandom(50,150));
    int branchH = 100+ofRandomf()*20;
    //treeColor = ofColor(branchG+40,branchG,int(ofRandom(0,60)));
    //MAKE HSB COLOR!!!!!
    //treeColor = ofColor(60+branchG,20+branchG,0+branchG);

    int treeAlpha;
    if (_treeCount %3 <1){
        treeAlpha = int(ofRandom(240,255));
    } else {
        treeAlpha = int(ofRandom(130,230));
    }

    treeColor.setHsb(branchH,255-branchB,branchB);//,treeAlpha);

    treeSize = int(ofRandom(3,6));

}

//-------------------------------------------------------------------

void Tree::update(){

    for (int i=0; i < branches.size(); i++){
        branches[i]->update();
    }

    if (branches.size()<treeSize){
    for (int i=0; i < branches.size(); i++){
        if (branches[i]->getSize() == 30){
            ofVec3f branchPoint = branches[i]->drawPoint;
            parentAngle = branches[i]->angle;
            parentStart = branches[i]->startPoint;
            startAngle = ofRandomf()*45;
            Branch * b = new Branch();
            b->setup(&branchPoint,&startThickness,&startAngle,&parentAngle,&parentStart,branches.size());
            branches.push_back(b);

            cout << branches.size() << endl;
            cout << branchPoint << endl;
            }
        }
    }



}

//-------------------------------------------------------------------

void Tree::draw(){

    ofPushMatrix();
    for (int i=0; i < branches.size(); i++){
        branches[i]->draw(treeColor);
    }
    ofPopMatrix();

}

//-------------------------------------------------------------------

Tree::~Tree()
{
    //dtor
}
