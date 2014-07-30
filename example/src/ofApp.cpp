#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    paragraph = new ofxParagraph();
    paragraph->setWidth(640);
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
