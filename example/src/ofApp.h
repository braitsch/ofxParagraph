#pragma once

#include "ofMain.h"
#include "ofxParagraph.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();

        ofxParagraph* p1;
        ofxParagraph* p2;
        ofxParagraph* p3;
    
        ofTrueTypeFont label;
};
