#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    paragraph = new ofxParagraph();
    paragraph->setPosition(ofPoint(200, 120));
    paragraph->setAlignment(ofxParagraph::center);
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
    paragraph->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}
