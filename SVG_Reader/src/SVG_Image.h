#ifndef SVG_IMAGE_H
#define SVG_IMAGE_H

#include "Gradient.h"
#include "Group.h"

/**
 * @brief Represents a 2D view box defining the user coordinate system.
 */
class ViewBox {
public:
	float min_x; /**< Minimum x-coordinate of the view box. */
	float min_y; /**< Minimum y-coordinate of the view box. */
	float width; /**< Width of the view box. */
	float height; /**< Height of the view box. */

	/**
	 * @brief Default constructor for ViewBox.
	 */
	ViewBox();

	/**
	 * @brief Set the view box attributes.
	 * @param viewBox String representation of the view box: "min_x min_y width height".
	 */
	void setViewBox(string& viewBox);
};
/*


*/
// class SVGImage
class SVG_Image {
private:
	// Attribute
	float width;
	float height;
	ViewBox viewbox;
	Group* root;
	Color* background;
	string namefile;

	// Methods
	void standardizeTag(string& line);

public:
	// Constructor
	SVG_Image();
	SVG_Image(const string& nameFile);

	// Destructor
	~SVG_Image();

	// Getter
	const Group* getRoot() const;

	// Set attribute
	void setWidth(string& width);
	void setHeight(string& height);
	void setStyle(string& style);
	void setImageAttributes(string& line);
	void renewImage();
	void parse(const string& nameFile);
	
};

void SVG_Render(const SVG_Image& svgImage, Render_Window);

//-------------END-OF-DECLARATION------------//

#endif // !SVG_IMAGE_H