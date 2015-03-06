#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(255);

    ofToggleFullscreen();
    ofEnableDepthTest();

    record = false;

    dragStart = false;

    recStart = 0;

    float posFactor = ofGetWidth()/2*ofRandomf();
            posFactor *= posFactor*posFactor*0.1;
            float distanceFactor = ofGetHeight()*ofRandomf();
            float bXPos = sin(posFactor)*distanceFactor;
            float bYPos = cos(posFactor)*distanceFactor;
            prevBloom = ofVec3f(bXPos,bYPos,ofRandomf()*30*-1);
            prevBloom = ofVec3f(0,0,0);



    light.setDiffuseColor(ofFloatColor(1.0,1.0,1.0));
    light.setPosition(ofPoint(0.0,0.0,400.0));


}

//--------------------------------------------------------------
void ofApp::update(){

    for (int i = 0; i < trees.size(); i++){
        trees[i]->update();
    }

        for (int i = 0; i< bloomsMain.size(); i++){
        bloomsMain[i]->update();

    }

}


//--------------------------------------------------------------
void ofApp::draw(){

    //ofTranslate(ofGetWidth()*0.5,ofGetHeight()*0.5);

    int bgR = ofMap(bloomsMain.size(),0,20,0,50);
    int bgG = ofMap(bloomsMain.size(),0,20,20,100);
    int bgB = ofMap(bloomsMain.size(),0,20,0,30);

    ofBackgroundGradient(ofColor (bgR, bgG, bgB), ofColor (bgR*0.5F, bgG*0.5F, bgB*0.5F));

    //UNCOMMENT FOR 3D:

    //cam.begin();
    //light.enable();
   // ofEnableLighting();

    //ofTranslate(ofGetWidth()*0.5,ofGetHeight()*0.5);

    //DISTANCE FADE EFFECT (STILL TESTING):
    //for (int i = -40; i>-200; i-=40 ){
       // ofSetColor(50,50,100,5);
       // ofRect(ofVec3f(0,0,i),ofGetWidth(),ofGetHeight());
    //}

    for (int i = 0; i < trees.size(); i++){
        trees[i]->draw();
    }

    //DRAW MAIN BLOOMS CREATED BY FINGER PRESS / DRAG
    for (int i = 0; i< bloomsMain.size(); i++){
        bloomsMain[i]->draw();
    }

    //TO SAVE EVERY FRAME
    if (record == true){
        string frameCount = ofToString(20000+ofGetFrameNum());
        string fileName = "filmImages/" + currentDate + "/" + frameCount + ".png";
        ofSaveScreen(fileName);

        int recFrames = ofGetFrameNum()-recStart;
        float recTime = recFrames / 60;

        cout << "Frames: " << recFrames << endl;
        cout << "Time: " << recTime << endl;
    }

   // ofDisableLighting();
   // light.disable();
    //cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f'){
        ofToggleFullscreen();
    }
    if (key == 's'){
        string frameCount = ofToString(20000+ofGetFrameNum());
        string fileName = "Images/" + frameCount + ".jpg";
        ofSaveScreen(fileName);
    }

    //THIS CREATES A NEW TREE... MAINLY FOR TESTING
    if(key == 't'){
        ofVec3f treeInit = ofVec3f(0,ofGetHeight()*ofRandom(0.1,0.9),0);
        int angleInit = int(ofRandom(70,130));

        Tree *t = new Tree();
        t->setup(&treeInit,&angleInit,trees.size());
        trees.push_back(t);
    }

    //CREATES A NEW BLOOM -- ALSO FOR TESTING
    if(key == 'b'){
            float posFactor = ofGetWidth()/2*ofRandomf();
            //posFactor *= posFactor*posFactor*0.1;
            float distanceFactor = ofGetHeight()*ofRandomf();
            float bXPos = sin(posFactor)*distanceFactor;
            float bYPos = cos(posFactor)*distanceFactor;
            ofVec3f bloomInit = ofVec3f(bXPos,bYPos,ofRandomf()*30*-1);

            ofVec3f dist = prevBloom - bloomInit;
            float distanceFromPrev = dist.length();

            float chance = ofGetHeight()*ofRandomf()*0.5;
            float minDist = 20;

        if (prevBloom != ofVec3f(0,0,0)){
            while (distanceFromPrev > chance || distanceFromPrev < minDist){
                distanceFactor = ofGetHeight()*ofRandomf();
                bXPos = sin(posFactor)*distanceFactor;
                bYPos = cos(posFactor)*distanceFactor;
                bloomInit = ofVec3f(bXPos,bYPos,ofRandomf()*30*-1);
                dist = prevBloom - bloomInit;
                distanceFromPrev = dist.length();
                chance = ofGetHeight()*ofRandomf()*2;
            }
        }

        makeBloom(bloomInit);

        prevBloom = bloomInit;

    }

    //THIS SAVES EVERY FRAME
    if(key == 'r'){
            record = true;
            recStart = ofGetFrameNum();
            currentDate = ofGetTimestampString();
        }

    if(key == 'e'){
            record = false;
    }

    //THIS CLEARS SCREEN OF MAIN BLOOMS -- NEED UPDATE TO CLEAR ALL / CLEAR POINTER VECTORS
    //if(key == 'c'){
    //        bloomsMain.clear();
    //}

}

//--------------------------------------------------------------
void ofApp::makeBloom(ofVec3f _bloomInit){

            Bloom * b = new Bloom();
            b->setup(&_bloomInit);
            bloomsMain.push_back(b);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
            //targetFrame = ofGetFrameNum();
            int *bXPos = &x;
            int *bYPos = &y;
            ofVec3f bloomInit = ofVec3f(*bXPos,*bYPos,ofRandomf()*30*-1);

            ofVec3f dist = prevBloom - bloomInit;
            float distanceFromPrev = dist.length();

        if (distanceFromPrev > ofRandom(25,50)){
            makeBloom(bloomInit);
            prevBloom = bloomInit;
        }
        //targetFrame = ofGetFrameNum()+int(ofRandom(50));

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

            //targetFrame = ofGetFrameNum();
        int *bXPos = &x;
        int *bYPos = &y;
        float bZPos = ofRandomf()*200*-1;

        ofVec3f bloomInit = ofVec3f(*bXPos,*bYPos,bZPos);

        ofVec3f treeInit = ofVec3f(*bXPos,*bYPos,bZPos-10);

        for (int i=0; i<ofRandom(1,4); i++){
            Tree *t = new Tree();
            int angleInit = int(ofRandomuf()*360);
            t->setup(&treeInit,&angleInit,trees.size());
            trees.push_back(t);
        }

        makeBloom(bloomInit);
        prevBloom = bloomInit;


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    //dragStart = false;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
