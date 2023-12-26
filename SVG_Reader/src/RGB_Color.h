#ifndef RGB_H
#define RGB_H

#include "Color.h"

/**
 * @brief Represents an RGB color with optional opacity.
 *
 * This class is derived from the Color class and includes attributes for red, green, blue,
 * and opacity values. It also provides methods to set the color from a string representation
 * or individual RGB values.
 */
class RGB_Color : public Color {
private:
    static std::unordered_map<string, RGB_Color> rgb_map; /**< Static map for caching RGB colors. */

public:
    float r; /**< Red component of the RGB color. */
    float g; /**< Green component of the RGB color. */
    float b; /**< Blue component of the RGB color. */

    /**
     * @brief Default constructor for RGB_Color.
     * Initializes red, green, and blue components to 0.
     * Sets default opacity to 1.0.
     */
    RGB_Color();

    /**
     * @brief Constructor for RGB_Color with string color representation.
     * @param color String representation of the RGB color.
     */
    RGB_Color(string& color);

    /**
     * @brief Copy constructor for RGB_Color.
     * @param color The RGB_Color object to copy.
     */
    RGB_Color(const RGB_Color& color);

    /**
     * @brief Constructor for RGB_Color with individual RGB values.
     * @param r Red component.
     * @param g Green component.
     * @param b Blue component.
     * @param a Opacity (default is 255).
     */
    RGB_Color(const float& r, const float& g, const float& b, const float& a = 255);

    /**
     * @brief Set RGB values from string representation.
     * Assumes the format "r g b" or "r g b a".
     * @param color String representation of the RGB color.
     */
    void setRGB(string& color);

    /**
     * @brief Set RGB values from individual components.
     * @param r Red component.
     * @param g Green component.
     * @param b Blue component.
     * @param a Opacity.
     */
    void setRGB(const float& r, const float& g, const float& b, const float& a = 255);

    /**
     * @brief Ensure RGB values are within the valid range [0, 255].
     */
    void balance();

    /**
     * @brief Overloaded assignment operator for RGB_Color.
     * @param color The RGB_Color object to copy.
     * @return Reference to the assigned RGB_Color object.
     */
    RGB_Color& operator=(const RGB_Color& color);
};

#endif // !RGB_H
