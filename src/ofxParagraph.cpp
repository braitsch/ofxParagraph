//
//  ofxParagraph.cpp
//  ofxParagraphExample
//
//  Created by Stephen Braitsch on 7/30/14.
//
//

#include "ofxParagraph.h"

vector< ofxParagraph::font > ofxParagraph::mFonts;
string ofxParagraph::Helvetica = "HelveticaNeueLTStd-Md.otf";

ofxParagraph::ofxParagraph(std::string text, int width, alignment align)
: mColor(ofColor::black)
, mIndent(40)
, mSpacing(10)
, mLeading(28)
, mPosition(100, 100)
, bDrawBorder(false)
, mBorderColor(ofColor::black)
, mBorderPadding(15)
{
    setText(text);
    setAlignment(align);
    setWidth(width);
    setFont(Helvetica, 14);
    bRender = true;
};

void ofxParagraph::draw()
{
    if (bRender) render();
    ofPushStyle();{
        ofSetColor(mColor);
        if (mAlign == ALIGN_LEFT){
            drawLeftAligned();
        }   else if (mAlign == ALIGN_CENTER){
            drawCenterAligned();
        }   else if (mAlign == ALIGN_RIGHT){
            drawRightAligned();
        }
        if (bDrawBorder == true){
            ofNoFill();
            ofSetColor(mBorderColor);
            ofRect(mPosition.x - mBorderPadding,
                   mPosition.y - mFont.getLineHeight() - mBorderPadding,
                   mWidth + (mBorderPadding * 2),
                   mHeight + (mBorderPadding * 2));
        }
    } ofPopStyle();
}

void ofxParagraph::setText(std::string text)
{
    mText = trim(text);
}

void ofxParagraph::setFont(std::string file, int ptSize)
{
    bool cached = false;
    for (int i=0; i<mFonts.size(); i++) {
        if (mFonts[i].file == file && mFonts[i].ptSize == ptSize){
            cached = true;
            mFont = mFonts[i].ttf;
            std::cout << "retrieving from cache : " + file + " at size " << ptSize << endl;
        }
    }
    if (!cached){
        std::cout << "loading font : " + file + " at size " << ptSize << endl;
        ofTrueTypeFont ttf;
        ttf.loadFont(file, ptSize);
        font nFont = {file, ptSize, ttf};
        mFonts.push_back(nFont);
        mFont = ttf;
    }
}

void ofxParagraph::setColor(ofColor color)
{
    mColor = color;
}

void ofxParagraph::setColor(int color)
{
    mColor = ofColor::fromHex(color);
}

void ofxParagraph::setWidth(int width)
{
    mWidth = width;
    bRender = true;
}

int ofxParagraph::getWidth()
{
    return mWidth;
}

int ofxParagraph::getHeight()
{
    return mHeight;
}

void ofxParagraph::setIndent(int indent)
{
    mIndent = indent;
    bRender = true;
}

void ofxParagraph::setPosition(ofPoint position)
{
    mPosition = position;
}

void ofxParagraph::setAlignment(alignment align)
{
    mAlign = align;
    bRender = true;
}

void ofxParagraph::setSpacing(int spacing)
{
    mSpacing = spacing;
    bRender = true;
}

void ofxParagraph::setLeading(int leading)
{
    mLeading = leading;
    bRender = true;
}

void ofxParagraph::drawBorder(bool draw)
{
    bDrawBorder = draw;
}

void ofxParagraph::drawBorder(ofColor color)
{
    bDrawBorder = true;
    mBorderColor = color;
}

void ofxParagraph::setBorderPadding(int padding)
{
    mBorderPadding = padding;
}

void ofxParagraph::render()
{
    mWords.clear();
// break paragraph into words //
    int position = mText.find(" ");
    while ( position != string::npos )
    {
        string s = mText.substr(0, position);
        word w = {s, mFont.getStringBoundingBox(s, 0, 0).width};
        mWords.push_back(w);
        mText.erase(0, position + 1);
        position = mText.find(" ");
    }
// append the last word //
    word w = {mText, mFont.getStringBoundingBox(mText, 0, 0).width};
    mWords.push_back(w);
    
// calculate number of words per line //
    mLines.clear();
    mLineWidths.clear();
    vector<word> line;
    int lineWidth = mAlign == ALIGN_LEFT ? mIndent : 0;
    for (int i=0; i<mWords.size(); i++) {
        if (lineWidth + mWords[i].width < mWidth){
            lineWidth += mWords[i].width + mSpacing;
            line.push_back(mWords[i]);
        }   else{
            mLines.push_back(line);
            mLineWidths.push_back(lineWidth);
            lineWidth = 0;
            line.clear();
        }
    }
// append the last line //
    mLines.push_back(line);
    mLineWidths.push_back(lineWidth);
    mHeight = mLines.size() * mLeading;
    bRender = false;
}

inline void ofxParagraph::drawLeftAligned()
{
    for(int i=0; i<mLines.size(); i++) {
        int x = i == 0 ? mIndent : 0;
        for(int j=0; j<mLines[i].size(); j++) {
            mFont.drawString(mLines[i][j].text, mPosition.x + x, mPosition.y + (mLeading*i));
            x += mLines[i][j].width + mSpacing;
        }
    }
}

inline void ofxParagraph::drawCenterAligned()
{
    for(int i=0; i<mLines.size(); i++) {
        int x = mSpacing/2 + (mWidth-mLineWidths[i])/2;
        for(int j=0; j<mLines[i].size(); j++) {
            mFont.drawString(mLines[i][j].text, mPosition.x + x, mPosition.y + (mLeading*i));
            x += mLines[i][j].width + mSpacing;
        }
    }
}

inline void ofxParagraph::drawRightAligned()
{
    for(int i=0; i<mLines.size(); i++) {
        int x = mWidth-mLineWidths[i] + mSpacing;
        for(int j=0; j<mLines[i].size(); j++) {
            mFont.drawString(mLines[i][j].text, mPosition.x + x, mPosition.y + (mLeading*i));
            x += mLines[i][j].width + mSpacing;
        }
    }
}