#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    p1 = new ofxParagraph();
    p1->setWidth(340);
    p1->setColor(ofColor::darkGrey);
    p1->drawBorder(ofColor::darkGrey);
    p1->setPosition(ofPoint(100, 120));
    p1->setAlignment(ofxParagraph::ALIGN_LEFT);
    p1->drawWordBoundaries();
    
    p2 = new ofxParagraph();
    p2->setWidth(340);
    p2->setColor(ofColor::darkGrey);
    p2->drawBorder(ofColor::darkGrey);
    p2->setPosition(ofPoint(500, 120));
    p2->setAlignment(ofxParagraph::ALIGN_CENTER);
    
    p3 = new ofxParagraph();
    p3->setWidth(340);
    p3->setColor(ofColor::darkGrey);
    p3->drawBorder(ofColor::darkGrey);
    p3->setPosition(ofPoint(900, 120));
    p3->setAlignment(ofxParagraph::ALIGN_RIGHT);

// draw a label above each paragraph //
    ofSetHexColor(0x666666);
    ofBackground(ofColor::white);
    label.loadFont(ofxParagraph::Helvetica, 14);
}

//--------------------------------------------------------------
void ofApp::draw()
{
    p1->draw();
    p2->draw();
    p3->draw();
    label.drawString("LEFT ALIGNED", 100 + (340 - label.getStringBoundingBox("LEFT ALIGNED", 0, 0).width)/2, 60);
    label.drawString("CENTER ALIGNED", 500 + (340 - label.getStringBoundingBox("CENTER ALIGNED", 0, 0).width)/2, 60);
    label.drawString("RIGHT ALIGNED", 900 + (340 - label.getStringBoundingBox("RIGHT ALIGNED", 0, 0).width)/2, 60);
}
