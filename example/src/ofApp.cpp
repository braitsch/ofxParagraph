#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    p1 = new ofxParagraph();
    p1->setWidth(340);
    p1->drawBorder(true);
    p1->setPosition(ofPoint(100, 120));
    p1->setAlignment(ofxParagraph::left);
    
    p2 = new ofxParagraph();
    p2->setWidth(340);
    p2->drawBorder(true);
    p2->setPosition(ofPoint(500, 120));
    p2->setAlignment(ofxParagraph::center);
    
    p3 = new ofxParagraph();
    p3->setWidth(340);
    p3->drawBorder(true);
    p3->setPosition(ofPoint(900, 120));
    p3->setAlignment(ofxParagraph::right);
}

//--------------------------------------------------------------
void ofApp::draw()
{
    p1->draw();
    p2->draw();
    p3->draw();
}
