
//
//  ofxParagraphExample
//
//  Created by Stephen Braitsch on 9/17/15
//  https://github.com/braitsch/ofxParagraph
//

#include "ofApp.h"

void ofApp::setup()
{
    ofBackground(ofColor::white);
    ofSetFullscreen(true);

// create three paragraphs with different alignments //
    for (int i=0; i<3; i++) {
        ofxParagraph* p = new ofxParagraph();
        p->setColor(ofColor::darkGrey);
        p->drawBorder(ofColor::darkGrey);
        if (i==0){
// let's draw the boundaries in the first paragraph //
            p->drawWordBoundaries();
            p->setAlignment(ofxParagraph::ALIGN_LEFT);
        }   else if (i==1){
            p->setAlignment(ofxParagraph::ALIGN_CENTER);
        }   else if (i==2){
            p->setAlignment(ofxParagraph::ALIGN_RIGHT);
        }
        paragraphs.push_back(p);
    }

// change these to whatever you want //
    int pWidth = 340;
    int pFontSize = 14;
    float pPadding = pWidth*.30;

// check for high resolution display //
    if (ofGetScreenWidth()>=2560 && ofGetScreenHeight()>=1600)
    {
        pWidth*=2;
        pFontSize*=2;
    }
    
// load our font and layout our paragraphs //
    font = ofxSmartFont::add("ofxbraitsch/fonts/HelveticaNeueLTStd-Md.otf", pFontSize);
    
    int pLeading = pFontSize*.65;
    int tWidth = paragraphs.size()*pWidth + (paragraphs.size()-1)*pPadding;
    
    int x = (ofGetWidth() - tWidth)/2;
    for (int i=0; i<paragraphs.size(); i++){
        paragraphs[i]->setWidth(pWidth);
        paragraphs[i]->setFont(font);
        paragraphs[i]->setLeading(pLeading);
        paragraphs[i]->setPosition(x+((pWidth+pPadding)*i), ofGetHeight()/2 - paragraphs[i]->getHeight()/2);
    }
    
}

void ofApp::draw()
{
//  draw the paragraphs //
    for (int i=0; i<paragraphs.size(); i++){
        paragraphs[i]->draw();
    // and a label above each one //
        string s;
        switch (i) {
            case 0: s = "LEFT ALIGNED"; break;
            case 1: s = "CENTER ALIGNED"; break;
            case 2: s = "RIGHT ALIGNED"; break;
        }
        ofPushStyle();
            ofSetHexColor(0x666666);
            font->draw(s, paragraphs[i]->x + (paragraphs[i]->getWidth()/2 - font->width(s)/2), paragraphs[i]->y-100);
        ofPopStyle();
    }
}




