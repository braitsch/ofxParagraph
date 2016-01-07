
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
        p->setColor(ofColor::fromHex(0x555555));
        p->drawBorder(ofColor::fromHex(0x777777));
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
    
// load our fonts and layout our paragraphs //
    label = ofxSmartFont::add("raleway/Raleway-Thin.ttf", pFontSize*2, "raleway-thin");
    paragraphs[0]->setFont(ofxSmartFont::add("raleway/Raleway-Medium.ttf", pFontSize, "raleway-medium"));
    paragraphs[1]->setFont(ofxSmartFont::add("raleway/Raleway-Italic.ttf", pFontSize, "raleway-italic"));
    paragraphs[2]->setFont(ofxSmartFont::add("raleway/Raleway-SemiBoldItalic.ttf", pFontSize, "raleway-semi-bi"));
    ofxSmartFont::list();
    
    int pLeading = pFontSize*.65;
    int tWidth = paragraphs.size()*pWidth + (paragraphs.size()-1)*pPadding;
    
    int x = (ofGetWidth() - tWidth)/2;
    for (int i=0; i<paragraphs.size(); i++){
        paragraphs[i]->setWidth(pWidth);
        paragraphs[i]->setLeading(pLeading);
        paragraphs[i]->setSpacing(pFontSize*.7);
        paragraphs[i]->setBorderPadding(30);
        paragraphs[i]->setPosition(x+((pWidth+pPadding)*i), ofGetHeight()/2 - paragraphs[0]->getHeight()/2);
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
            label->draw(s, paragraphs[i]->x + (paragraphs[i]->getWidth()/2 - label->width(s)/2), paragraphs[i]->y-100);
        ofPopStyle();
    }
}




