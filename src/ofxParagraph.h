//
//  ofxParagraph.h
//  ofxParagraphExample
//
//  Created by Stephen Braitsch on 7/29/14.
//
//

#pragma once
#include <vector>
#include <iostream>
#include <ofGraphics.h>
#include <ofTrueTypeFont.h>

class ofxParagraph{
    
    public:
        ofxParagraph(std::string text = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.")
        : mWidth(620)
        , mColor(ofColor::black)
        , mIndent(60)
        , mSpacing(10)
        , mLeading(40)
        , mPosition(100, 100)
        {
            parse(text);
        };
        void draw()
        {
            ofPushStyle();{
                ofSetColor(mColor);
                for(int i=0; i<mLines.size(); i++) {
                    int x = i == 0 ? mIndent : 0;
                    for(int j=0; j<mLines[i].size(); j++) {
                        mFont.drawString(mLines[i][j].text, mPosition.x + x, mPosition.y + (mLeading*i));
                        x += mLines[i][j].width + mSpacing;
                    }
                }
            } ofPopStyle();
            ofNoFill();
            ofRect(mPosition.x, mPosition.y - 30, mWidth, mLines.size() * mLeading);

        }
        void setText(std::string text)
        {
            parse(text);
            layout();
        }
        void setFont(std::string file, int ptSize)
        {
            loadFont(file, ptSize);
            layout();
        }
        void setColor(ofColor color)
        {
            mColor = color;
        }
        void setWidth(int width)
        {
            mWidth = width;
            layout();
        }
        void setIndent(int indent)
        {
            mIndent = indent;
            layout();
        }
        void setSpacing(int spacing)
        {
            mSpacing = spacing;
            layout();
        }
        void setLeading(int leading)
        {
            mLeading = leading;
        }
    
    private:
        int mWidth;
        int mIndent;
        int mLeading;
        int mSpacing;
        ofColor mColor;
        ofPoint mPosition;
        ofTrueTypeFont mFont;
        struct word{
            string text;
            int width;
        };
        vector<word> mWords;
        vector< vector<word> > mLines;
    
        void parse(std::string text)
        {
            std::string mText = trim(text);
            if (mFont.isLoaded() == false) loadFont("/library/Fonts/Arial.ttf", 24);
            
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
    
        void layout()
        {
            mLines.clear();
            vector<word> line;
            int lineWidth = mIndent;
            for (int i=0; i<mWords.size(); i++) {
                if (lineWidth + mWords[i].width < mWidth){
                    lineWidth += mWords[i].width + mSpacing;
                    line.push_back(mWords[i]);
                }   else{
                    mLines.push_back(line);
                    lineWidth = 0;
                    line.clear();
                }
            }
        // last line //
            mLines.push_back(line);
        }
    
        void loadFont(std::string file, int ptSize)
        {
            std::cout << "loading font";
            mFont.loadFont("/library/Fonts/Arial.ttf", 24, true , false, true);
        }
    
        // trim from start
        static inline std::string &ltrim(std::string &s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
            return s;
        }
        
        // trim from end
        static inline std::string &rtrim(std::string &s) {
            s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
            return s;
        }
        
        // trim from both ends
        static inline std::string &trim(std::string &s) {
            return ltrim(rtrim(s));
        }
    
};




