#ifndef COLOR_H
#define COLOR_H

#include "SVG_Element.h"

/**
 * @brief Represents a color in an SVG element.
 *
 * This class is derived from the SVG_Element class and includes an opacity attribute.
 */
class Color : public SVG_Element {
public:
    float opacity; /**< Opacity of the color. */

    /**
     * @brief Default constructor for Color.
     */
    Color();

    /**
     * @brief Copy constructor for Color.
     * @param other The Color object to copy.
     */
    Color(const Color& other);

    /**
     * @brief Set the opacity of the color.
     * @param opacity The opacity value to set.
     */
    void setOpacity(const float& opacity);

    /**
     * @brief Set the opacity of the color.
     * @param opacity String representation of the opacity.
     */
    void setOpacity(string& opacity);

    /**
     * @brief Virtual method to set RGB color (to be overridden by derived classes).
     * @param color String representation of the RGB color.
     */
    virtual void setRGB(string& color) {};

    /**
     * @brief Dummy method to set element attributes (not implemented).
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    void setElementAttributes(const string& attribute, string& value) override {};
};

/**
 * @brief Helper function to create a Color object.
 * @param color Pointer to the Color object.
 * @param name Optional name for the color (default is an empty string).
 */
void createColor(Color*& color, string name = "");

/**
 * @brief Helper function to copy a Color object.
 * @param color Pointer to the Color object to be copied.
 * @param copy Pointer to the copy of the Color object.
 */
void copyColor(Color*& color, Color* copy);

#endif // !COLOR_H
