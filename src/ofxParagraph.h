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
    
        static string Helvetica;
        enum alignment { ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT };
    
    ofxParagraph(std::string text = "Stumptown street art photo booth try-hard cold-pressed, pour-over raw denim four loko vinyl. Banjo drinking vinegar tousled, Brooklyn Neutra meggings mlkshk freegan whatever. Authentic drinking vinegar next level Portland tattooed, street art mixtape. Butcher High Life Brooklyn bicycle rights. Cardigan iPhone stumptown 90's, Carles Neutra viral Brooklyn ugh disrupt. Truffaut Williamsburg sriracha four dollar toast bicycle rights four loko. Migas Odd Future disrupt DIY polaroid whatever.", int width = 620, alignment align = ALIGN_LEFT);
    
        void draw();
        void setText(std::string text);
        void setFont(std::string file, int ptSize);
        void setColor(int color);
        void setColor(ofColor color);
        void setWidth(int width);
        int getWidth();
        int getHeight();
        void setIndent(int indent);
        void setPosition(ofPoint position);
        void setAlignment(alignment align);
        void setSpacing(int spacing);
        void setLeading(int leading);
        void drawBorder(bool draw);
        void drawBorder(ofColor color);
        void setBorderPadding(int padding);
        void drawWordBoundaries(bool draw = true);
    
    private:
        int mWidth;
        int mHeight;
        int mIndent;
        int mLeading;
        int mSpacing;
        int mLineHeight;
        string mText;
        ofColor mColor;
        ofPoint mPosition;
        ofTrueTypeFont mFont;
        alignment mAlign;
        bool bRender;
        bool bDrawBorder;
        ofColor mBorderColor;
        int mBorderPadding;
        bool bDrawWordBoundaries;
        int mWordBoundaryPadding;
        ofColor mWordBoundaryColor;
        struct word {
            string text;
            ofRectangle rect;
        };
        struct font {
            string file;
            int ptSize;
            ofTrueTypeFont ttf;
        };
        vector< word > mWords;
        vector< vector<word*> > mLines;
        static vector< font > mFonts;
    
        void render();
        inline void drawLeftAligned();
        inline void drawCenterAligned();
        inline void drawRightAligned();
    
        static inline std::string &trim(std::string &s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
            s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
            return s;
        }
    
};




