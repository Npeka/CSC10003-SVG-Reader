#ifndef SVG_IMAGE_H
#define SVG_IMAGE_H

#include "Group.h"

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
	void setAttribute(const std::string& viewBox);
};
//-------------END-OF-DECLARATION------------//
/*


*/
// class SVGImage
class SVGImage {
private:
	// Attribute
	float width;
	float height;
	Color background;
	ViewBox viewbox;
	Group* root;

	// Methods
	void standardizeTag(std::string& line);
	
public:
	// Constructor
	SVGImage();
	SVGImage(const std::string& nameFile);
	SVGImage(const SVGImage& svgImage);

	// Destructor
	~SVGImage();
	
	// Getter
	const Group* getRoot() const;

	// Set attribute
	void setWidth(const std::string& width);
	void setHeight(const std::string& height);
	void setStyle(const std::string& style);
	void setViewBox(const std::string& viewbox);
	void setSVGAttributes(const std::string& line);
	void parse(const std::string& nameFile);
};

void SVG_Render(const SVGImage& svgImage, Render_Window);

//-------------END-OF-DECLARATION------------//

#endif // !SVG_IMAGE_H
