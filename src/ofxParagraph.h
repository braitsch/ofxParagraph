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
    
        enum alignment { left, center, right };
    
        ofxParagraph(std::string text = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.", int width = 620, alignment align = left);
    
        void draw();
        void setText(std::string text);
        void setFont(std::string file, int ptSize);
        void setColor(int color);
        void setColor(ofColor color);
        void setWidth(int width);
        void setIndent(int indent);
        void setPosition(ofPoint position);
        void setAlignment(alignment align);
        void setSpacing(int spacing);
        void setLeading(int leading);
        void drawBorder(bool draw);
        void drawBorder(ofColor color);
        void setBorderPadding(int padding);
    
    private:
        int mWidth;
        int mIndent;
        int mLeading;
        int mSpacing;
        ofColor mColor;
        ofPoint mPosition;
        ofTrueTypeFont mFont;
        alignment mAlign;
        bool bDrawBorder;
        ofColor mBorderColor;
        int mBorderPadding;
        struct word {
            string text;
            int width;
        };
        struct font {
            string file;
            int ptSize;
            ofTrueTypeFont ttf;
        };
        vector< word > mWords;
        vector< vector<word> > mLines;
        vector< int > mLineWidths;
        static vector< font > mFonts;
    
        void layout();
        void parse(std::string text);
        inline void drawLeftAligned();
        inline void drawCenterAligned();
        inline void drawRightAligned();
    
        void getFont(std::string file, int ptSize);
    
        static inline std::string &trim(std::string &s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
            s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
            return s;
        }
    
};




