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
, mSpacing(6)
, mLeading(6)
, mPosition(100, 100)
, bDrawBorder(false)
, mBorderColor(ofColor::black)
, mBorderPadding(15)
, bDrawWordBoundaries(false)
, mWordBoundaryPadding(2)
, mWordBoundaryColor(ofColor::red)
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
        for (int i=0; i<mWords.size(); i++) {
            mFont.drawString(mWords[i].text, mPosition.x + mWords[i].rect.x, mPosition.y + mWords[i].rect.y);
            if (bDrawWordBoundaries == true){
                ofPushStyle();
                ofNoFill();
                ofSetColor(mWordBoundaryColor);
                ofRect(mPosition.x + mWords[i].rect.x - mWordBoundaryPadding,
                       mPosition.y + mWords[i].rect.y-mLineHeight - mWordBoundaryPadding,
                       mWords[i].rect.width + (mWordBoundaryPadding * 2),
                       mLineHeight + (mWordBoundaryPadding * 2));
                ofPopStyle();
            }
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

void ofxParagraph::drawWordBoundaries(bool draw)
{
    bDrawWordBoundaries = draw;
}

void ofxParagraph::render()
{
    mWords.clear();
    mLineHeight = 0;
// break paragraph into words //
    int position = mText.find(" ");
    while ( position != string::npos )
    {
        string s = mText.substr(0, position);
        word w = {s, mFont.getStringBoundingBox(s, 0, 0)};
        mWords.push_back(w);
        mText.erase(0, position + 1);
        position = mText.find(" ");
        if (w.rect.height > mLineHeight) mLineHeight = w.rect.height;
    }
// append the last word //
    word w = {mText, mFont.getStringBoundingBox(mText, 0, 0)};
    mWords.push_back(w);
    if (w.rect.height > mLineHeight) mLineHeight = w.rect.height;
    
// assign words to lines //
    int y = 0;
    int x = mAlign == ALIGN_LEFT ? mIndent : 0;
    mLines.clear();
    vector<word*> line;
    for (int i=0; i<mWords.size(); i++) {
        if (x + mWords[i].rect.width < mWidth){
            mWords[i].rect.x = x;
            mWords[i].rect.y = y;
            x += mWords[i].rect.width + mSpacing;
            line.push_back(&mWords[i]);
        }   else{
            y+= mLineHeight + mLeading;
            mWords[i].rect.x = 0;
            mWords[i].rect.y = y;
            x = mWords[i].rect.width + mSpacing;
            mLines.push_back(line);
            line.clear();
            line.push_back(&mWords[i]);
        }
    }
// append the last line //
    mLines.push_back(line);
    mHeight = mLines.size() * (mLineHeight + mLeading);
    
// reposition words for right & center aligned paragraphs //
    if (mAlign == ALIGN_CENTER){
        for(int i=0; i<mLines.size(); i++) {
            int lineWidth = 0;
            for(int j=0; j<mLines[i].size(); j++) {
                lineWidth+= mLines[i][j]->rect.width;
            }
            lineWidth+= mSpacing * (mLines[i].size()-1);
        // calculate the amount each word should move over //
            int offset = (mWidth - lineWidth) / 2;
            for(int j=0; j<mLines[i].size(); j++) mLines[i][j]->rect.x += offset;
        }
    }   else if (mAlign == ALIGN_RIGHT){
        for(int i=0; i<mLines.size(); i++) {
            word* lword = mLines[i].back();
        // calculate the distance the last word in each line is from the right boundary //
            int offset = mWidth - (lword->rect.x + lword->rect.width);
            for(int j=0; j<mLines[i].size(); j++) mLines[i][j]->rect.x += offset;
        }
    }
    bRender = false;
}
