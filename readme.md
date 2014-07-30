ofxParagraph
-----------------
A simple text layout engine for [openFrameworks](http://openframeworks.cc/)


####API
-----------------

	ofxParagraph paragraph = ofxParagraph(string text, int width)

------------------------------------------------------------------------------
*draw the paragraph*
 
	void draw()
------------------------------------------------------------------------------
*set the text* 

	void setText(string text)
------------------------------------------------------------------------------
*set the width* 

	void setWidth(int width)	
------------------------------------------------------------------------------
*set the position* 

	void setPosition(ofPoint position)	
------------------------------------------------------------------------------
*set the text color*
 
	void setColor(ofColor color)
------------------------------------------------------------------------------
*set the alignment: left, right, center*
 
	void setAlignment(ofxParagraph::Alignment alignment)
------------------------------------------------------------------------------
*set the indentation of the first line*
 
	void setIndent(int indent)
------------------------------------------------------------------------------
*set the leading between lines*
 
	void setLeading(int leading)
------------------------------------------------------------------------------
*set the pixel spacing between words*
 
	void setSpacing(int spacing)

