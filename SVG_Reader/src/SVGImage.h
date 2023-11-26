#ifndef SVG_IMAGE_H
#define SVG_IMAGE_H
#include "Figure.h"

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
/*


*/
class SVGImage {
public:
	// Attribute
	string nameFile;
	float width;
	float height;
	Color background;
	ViewBox viewbox;
	vector<Figure*> figure;

	// Method
	void standardizeTag(string& line);
	void parse();
public:
	// Constructor
	SVGImage(const string& nameFile = "");
	SVGImage(const SVGImage& svgImage);

	// Destructor
	~SVGImage();

	// Method
	void setWidth(const string& width);
	void setHeight(const string& height);
	void setStyle(const string& style);
	void setViewBox(const string& viewbox);
	void setAttribute(const string& line);

	const vector<Figure*>& getFigure() const;
};

#endif // !SVG_IMAGE_H
