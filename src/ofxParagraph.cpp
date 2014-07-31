//
//  ofxParagraph.cpp
//  ofxParagraphExample
//
//  Created by Stephen Braitsch on 7/30/14.
//
//

#include "ofxParagraph.h"

vector< ofxParagraph::font > ofxParagraph::mFonts;

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
    parse(text);
    setAlignment(align);
    setWidth(width);
};

void ofxParagraph::draw()
{
    ofPushStyle();{
        ofSetColor(mColor);
        if (mAlign == left){
            drawLeftAligned();
        }   else if (mAlign == center){
            drawCenterAligned();
        }   else if (mAlign == right){
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
    parse(text);
    layout();
}
void ofxParagraph::setFont(std::string file, int ptSize)
{
    getFont(file, ptSize);
    layout();
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
    layout();
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
    layout();
}
void ofxParagraph::setPosition(ofPoint pos)
{
    mPosition = pos;
}
void ofxParagraph::setAlignment(alignment a)
{
    mAlign = a;
    layout();
}
void ofxParagraph::setSpacing(int spacing)
{
    mSpacing = spacing;
    layout();
}
void ofxParagraph::setLeading(int leading)
{
    mLeading = leading;
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

void ofxParagraph::parse(std::string text)
{
    std::string mText = trim(text);
    // always ensure we have some default font to draw //
    if (mFont.isLoaded() == false) getFont("HelveticaNeueLTStd-Md.otf", 12);
    
    // parse words //
    int position = mText.find(" ");
    while ( position != string::npos )
    {
        string s = mText.substr(0, position);
        word w = {s, mFont.getStringBoundingBox(s, 0, 0).width};
        mWords.push_back(w);
        mText.erase(0, position + 1);
        position = mText.find(" ");
    }
    // last word //
    word w = {mText, mFont.getStringBoundingBox(mText, 0, 0).width};
    mWords.push_back(w);
}

void ofxParagraph::layout()
{
    mLines.clear();
    mLineWidths.clear();
    vector<word> line;
    int lineWidth = mAlign == left ? mIndent : 0;
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
    // last line //
    mLines.push_back(line);
    mLineWidths.push_back(lineWidth);
    mHeight = mLines.size() * mLeading;
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

void ofxParagraph::getFont(std::string file, int ptSize)
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