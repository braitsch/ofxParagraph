
//
//  ofxParagraphExample
//
//  Created by Stephen Braitsch on 9/17/15
//  https://github.com/braitsch/ofxParagraph
//

#pragma once
#include "ofMain.h"
#include "ofxParagraph.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();
    
        shared_ptr<ofxSmartFont> label;
        vector<ofxParagraph*> paragraphs;

};
