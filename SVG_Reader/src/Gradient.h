#ifndef GRADIENT_H
#define GRADIENT_H

#include "Point.h"
#include "RGB_Color.h"
#include "Transform.h"

/**
 * @brief Represents a color stop in a gradient.
 */
class Stop {
public:
    RGB_Color color; /**< RGB color of the stop. */
    float offset; /**< Offset position of the stop. */

public:
    /**
     * @brief Default constructor for Stop.
     */
    Stop();

    /**
     * @brief Copy constructor for Stop.
     * @param other The Stop object to copy.
     */
    Stop(const Stop& other);
    
/**
	 * @brief Constructor for Stop.
	 * @param color RGB color of the stop.
	 * @param offset Offset position of the stop.
	 */
    Stop(const RGB_Color& color, const float& offset);

    /**
     * @brief Set the color of the stop.
     * @param color String representation of the RGB color.
     */
    void setColor(string& color);

    /**
     * @brief Set the offset position of the stop.
     * @param offset String representation of the offset.
     */
    void setOffset(string& offset);

    /**
     * @brief Set the opacity of the stop.
     * @param opacity String representation of the opacity.
     */
    void setOpacity(string& opacity);

    /**
     * @brief Get the RGB color of the stop.
     * @return RGB_Color object representing the color.
     */
    RGB_Color getColor();

    /**
     * @brief Get the offset position of the stop.
     * @return Offset position as a float.
     */
    float getOffset();
};

/**
 * @brief Represents a gradient with color stops.
 *
 * This class is derived from both the Color and Transform classes.
 */
class Gradient : public Color, public Transform {
protected:
    vector<Stop> ColorOffset; /**< Vector of color stops. */
    bool isPercent; /**< Indicates whether the offset positions are in percentage. */

public:
    /**
     * @brief Default constructor for Gradient.
     */
    Gradient();

    /**
     * @brief Copy constructor for Gradient.
     * @param other The Gradient object to copy.
     */
    Gradient(const Gradient& other);

    /**
     * @brief Add a color stop to the gradient.
     * @param line String representation of the color stop.
     */
    void addStop(string& line);

    /**
     * @brief Set the href attribute for the gradient.
     * @param href String representation of the href attribute.
     */
    void setHref(string& href);

    void setGradientUnits(string& gradientUnits);

    /**
     * @brief Dummy method to set element attributes (not implemented).
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    void setElementAttributes(const string& attribute, string& value) override;

    /**
     * @brief Get the vector of color stops in the gradient.
     * @return Vector of Stop objects.
     */
    vector<Stop> getColorOffset() const;

    /**
     * @brief Get whether the offset positions are in percentage.
     * @return True if offset positions are in percentage, false otherwise.
     */
    bool getIsPercent() const;
};

/**
 * @brief Helper function to get a Gradient object based on a color.
 * @param color String representation of the color.
 * @return Pointer to the Gradient object.
 */
Gradient* getGradient(const string& color);

#endif // !GRADIENT_H
