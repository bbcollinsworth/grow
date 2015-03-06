#include "Bloom.h"

Bloom::Bloom()
{
    //ctor
}

void Bloom::setup(ofVec3f *_bloomPoint){

    //THIS CONTROLS THE SIZE OF THE BLOOM
    int bloomSize = int(ofRandom(12,24));

    bloomPoint = *_bloomPoint;
    float bloomGB = float(ofRandom(150,245));
    float bloomR = float(ofRandom(80,255));

    //SETS VARYING BLOOM COLORS (REDDISH, YELLOWISH OR BLUEISH) BASED ON RANDOM PROBABILITY
    ofFloatColor bloomColor;
    if (ofRandomf() < -0.3){
    bloomColor = ofFloatColor(255/255,bloomGB/255,(bloomGB+ofRandomf()*10)/255);
    } else if (ofRandomf() > 0.3) {
    bloomColor = ofFloatColor((bloomGB+ofRandomf()*10)/255,bloomGB/255,255/255);
    } else {
    bloomColor = ofFloatColor(255/255, (200+ofRandomf()*55)/255,(bloomGB+ofRandomf()*10)/255);
    }

    for (int i = 0; i < 6; i++){
        Petal *p = new Petal();
        p->setup(bloomPoint,bloomColor,bloomSize);
        petals.push_back(p);
    }
}

void Bloom::update(){

    for (int i=0; i < petals.size(); i++){
        petals[i]->update();
    }

}

void Bloom::draw(){

    int noiseFactor = bloomPoint.y*0.1;
    ofPushMatrix();
    ofTranslate(bloomPoint);
    float noise = ofNoise( noiseFactor, ofGetFrameNum() * 0.02 );

    ofRotate(noise*10,0,0,1);

    for (int i=0; i < petals.size(); i++){
        float step = 60;
        ofRotate(step);
        petals[i]->draw(noise);
    }
    ofPopMatrix();

}

Bloom::~Bloom()
{
    //dtor
}
