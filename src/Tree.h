#ifndef TREE_H
#define TREE_H

#include "ofMain.h"
#include "Branch.h"

class Tree
{
    public:
        Tree();

        void setup(ofVec3f *_treeStart, int *_startAngle, int _treeCount);
        void update();
        void draw();

        ofVec3f treeStart, parentStart;
        int startAngle, parentAngle;
        float startThickness;
        int treeSize;

        vector <Branch *> branches;

        ofColor treeColor;

        virtual ~Tree();
    protected:
    private:
};

#endif // TREE_H
