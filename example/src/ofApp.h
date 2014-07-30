#pragma once

#include "ofMain.h"
#include "ofxParagraph.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
        ofxParagraph* paragraph;
    
};
