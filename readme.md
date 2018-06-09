ofxParagraph
-----------------
A simple paragraph renderer for [openFrameworks](http://openframeworks.cc/) that allows you to set the alignment, width, indentation, leading and pixel based word spacing of paragraphs.


![image](./readme-img/layout-example.png)

### Installation

**ofxParagraph** uses [ofxSmartFont](https://github.com/braitsch/ofxSmartFont) for font management which allows you to safely share ofxParagraph fonts with the rest of your application. 

This requires you to clone the repository recursively if you don't already have it installed.

	git clone --recursive git@github.com:braitsch/ofxParagraph.git

### Usage

Creating a paragraph is as simple as passing in a string and setting a width.

	ofxParagraph paragraph = ofxParagraph(text, width);

And then assigning a font you'd like to use:

 	paragraph.setFont("fonts/helvetica_neue.ttf", 12)

Alternately you can pass in an [ofxSmartFont](https://github.com/braitsch/ofxSmartFont) instance:

	shared_ptr<ofxSmartFont> helvetica_12;
	paragraph.setFont(helvetica_12);

Once you've got some text, a width and a font you're ready to draw:

	paragraph.draw();
	// or specify a position //
	paragraph.draw(int x, int y);

### Customization

The following methods are available to customize any ofxParagraph instance.
 
	void setText(string text)
	
	void setWidth(int width)
	
	void setFont(string file, int pointSize)
	
	void setFont(std::shared_ptr<ofxSmartFont> font)
 
	void setColor(ofColor color)
	
	void setColor(int color) // e.g. 0x333333

	void setPosition(int x, int y)
 
	void setAlignment(ofxParagraph::Alignment align)
 
	void setIndent(int indent)
 
	void setLeading(int leading) // vertical spacing between lines //
 
	void setSpacing(int spacing) // horizontal spacing between words //
	
You can also draw a border around paragraphs and boundaries around words.
	
	void drawBorder(bool draw)
	
	void drawBorder(ofColor color)
	
	void setBorderPadding(int padding)

	void drawWordBoundaries(bool draw)
	
And there are also a couple of handy getter functions just in case.

	int getWidth()
	
	int getHeight()
	
	int getStringHeight(string s = "")
