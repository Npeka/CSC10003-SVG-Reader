#ifndef SVG_IMAGE_H
#define SVG_IMAGE_H

#include "Figure.h"
#include "Render.h"

// class ViewBox
class ViewBox {
public:
	// Attribute
	float min_x;
	float min_y;
	float width;
	float height;

	// Constructor
	ViewBox();

	// Set attribute
	void setAttribute(const string& viewBox);
};
//-------------END-OF-DECLARATION------------//
/*


*/
// class SVGImage
class SVGImage {
protected:
	// Attribute
	string nameFile;
	float width;
	float height;
	Color background;
	ViewBox viewbox;
	vector<Drawable*> figure;

	// Methods
	void standardizeTag(string& line);
	void parse();
public:
	// Constructor
	SVGImage(const string& nameFile = "");
	SVGImage(const SVGImage& svgImage);

	// Destructor
	~SVGImage();

	// Set attribute
	void setNameFile(const string& nameFile);
	void setWidth(const string& width);
	void setHeight(const string& height);
	void setStyle(const string& style);
	void setViewBox(const string& viewbox);
	void setAttribute(const string& line);
	void render();
};
//-------------END-OF-DECLARATION------------//

#endif // !SVG_IMAGE_H
