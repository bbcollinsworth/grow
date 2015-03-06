#ifndef BLOOM_H
#define BLOOM_H

#include "ofMain.h"
#include "Petal.h"

class Bloom
{
    public:
        Bloom();

        void setup(ofVec3f *_bloomPoint);
        void update();
        void draw();

        ofVec3f bloomPoint;


        vector <Petal *> petals;

        virtual ~Bloom();
    protected:
    private:
};

#endif // BLOOM_H
