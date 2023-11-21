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

class SVGImage {
private:
	// Attribute
	string nameFile;
	vector<Figure*> figure;
	float width;
	float height;
	Color background;
	ViewBox viewbox;

	// Method
	void standardizeTag(string& line);
	void parse();
public:
	// Constructor
	SVGImage(const string& nameFile = "");

	// Destructor
	~SVGImage();

	// Method
	void setWidth(const string& width);
	void setHeight(const string& height);
	void setStyle(const string& style);
	void setViewBox(const string& viewbox);
	void setAttribute(const string& line);
	void draw(sf::RenderWindow& window, sf::Transform& transform);
};

#endif // !SVG_IMAGE_H
