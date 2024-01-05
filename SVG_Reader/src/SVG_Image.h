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
/**
 * @brief Represents an SVG image.
 *
 * This class encapsulates the properties of an SVG image, including
 * width, height, viewBox, root group, background color, and the file name.
 */
class SVG_Image {
private:
    float width; /**< Width of the SVG image. */
    float height; /**< Height of the SVG image. */
    ViewBox viewbox; /**< ViewBox representing the coordinate system of the SVG image. */
    Group* root; /**< Root group containing drawable figures. */
    Color* background; /**< Background color of the SVG image. */
    string namefile; /**< File name of the SVG image. */
    Defs_Type id_map; /**< Map of IDs to SVG elements. */

    /**
     * @brief Standardize an SVG tag in the given line.
     * @param line The line containing the SVG tag to standardize.
     */
    void standardizeTag(string& line);

public:
    /**
     * @brief Default constructor for SVG_Image.
     */
    SVG_Image();

    /**
     * @brief Constructor for SVG_Image with a specified file name.
     * @param nameFile The file name of the SVG image.
     */
    SVG_Image(const string& nameFile);

    /**
     * @brief Destructor for SVG_Image.
     */
    ~SVG_Image();

    /**
     * @brief Renew the SVG image by clearing and recreating it.
     */
    void renewImage();

    /**
     * @brief Set the width of the SVG image.
     * @param width The width to set.
     */
    void setWidth(string& width);

    /**
     * @brief Set the height of the SVG image.
     * @param height The height to set.
     */
    void setHeight(string& height);

    /**
     * @brief Set the style of the SVG image.
     * @param style The style to set.
     */
    void setStyleImage(string& style);

    /**
     * @brief Set the style of an SVG element.
     *
     * @param element Pointer to the SVG element.
     * @param style CSS styles to apply.
     */
    void setStyleElement(SVG_Element* element, string& style);

    /**
     * @brief Set the attributes of the SVG image.
     * @param line The line containing the attributes to parse.
     */
    void setImageAttributes(string& line);

    /**
     * @brief Parse SVG element attributes from a string and apply them.
     *
     * @param element Pointer to the SVG element.
     * @param line String containing the attributes to parse.
     */
    void parseElementAttributes(SVG_Element* element, string& line);

    /**
     * @brief Parse the SVG file with the given name.
     * @param nameFile The file name of the SVG image to parse.
     */
    void parseImage(const string& nameFile);

    /**
     * @brief Get the root group of the SVG image.
     * @return Pointer to the root group.
     */
    const Group* getRoot() const;

    /**
    * @brief Get the width of the SVG image.
    * @return The width of the SVG image.
    */
    float getWidth() const;

    /**
     * @brief Get the height of the SVG image.
     * @return The height of the SVG image.
     */
    float getHeight() const;

    /**
     * @brief Get the ViewBox representing the coordinate system of the SVG image.
     * @return The ViewBox of the SVG image.
     */
    ViewBox getViewBox() const;

    /**
     * @brief Get the map of IDs to SVG elements (Defs_Type).
     * @return The map of IDs to SVG elements.
     */
    Defs_Type getDefs() const;
};

/**
 * @brief Render the given SVG image to the specified graphics window.
 * @param svgImage The SVG image to render.
 * @param graphics The GDI+ Graphics object representing the graphics window.
 */
void SVG_Render(const SVG_Image& svgImage, Render_Window);

#endif // !SVG_IMAGE_H