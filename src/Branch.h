#ifndef BRANCH_H
#define BRANCH_H

#include "ofMain.h"
#include "Petal.h"
#include "Bloom.h"

class Branch
{
    public:
        Branch();

        void setup(ofVec3f *_drawPoint, float *_startThickness, int *_angle, int *_parentAngle, ofVec3f *_parentStart, int _branchCount);
        void update();
        void draw(ofColor _treeColor);
        ofVec3f getDrawPoint();
        ofVec3f getBranchPoint(int _index);
        int getSize();

        void bloom(ofVec3f bloomPoint);

        ofVec3f startPoint;
        ofVec3f drawPoint;
        ofVec3f vel;
        float startThickness;
        int angle;
        int parentAngle;
        ofVec3f parentStart;

        int branchCount;
        bool bloomset;
        float thickness;
        int bloomSpacing;

        vector <ofVec3f> points;
        vector <int> bloomNums;
        vector <Bloom *> blooms;
        vector <Petal> petals;

        virtual ~Branch();
    protected:
    private:
};

#endif // BRANCH_H
