#ifndef PETAL_H
#define PETAL_H

#include "ofMain.h"

class Petal
{
    public:
        Petal();

        void setup(ofVec3f _drawPoint, ofFloatColor _petalColor, int _bloomSize);
        void update();
        void draw(float _noise);

        int petalLength;

        float step;
        ofVec3f startPoint;
        ofVec3f drawPoint;
        ofVec3f vel;

        ofFloatColor petalColor;

        vector <ofVec3f > points;

        virtual ~Petal();
    protected:
    private:
};

#endif // PETAL_H
