#ifndef RADIAL_GRADIENT_H
#define RADIAL_GRADIENT_H

#include "Gradient.h"

/**
 * @brief Represents a radial gradient with color stops.
 *
 * This class is derived from the Gradient class and includes additional attributes
 * for defining the center, radius, and focal point of the radial gradient.
 */
class RadialGradient : public Gradient {
protected:
    float cx; /**< X-coordinate of the center of the radial gradient. */
    float cy; /**< Y-coordinate of the center of the radial gradient. */
    float r;  /**< Radius of the radial gradient. */
    float fx; /**< X-coordinate of the focal point of the radial gradient. */
    float fy; /**< Y-coordinate of the focal point of the radial gradient. */
    float fr; /**< Focal radius of the radial gradient. */

public:
    /**
     * @brief Default constructor for RadialGradient.
     */
    RadialGradient();

    /**
     * @brief Copy constructor for RadialGradient.
     * @param other The RadialGradient object to copy.
     */
    RadialGradient(const RadialGradient& other);

    /**
     * @brief Set the x-coordinate of the center.
     * @param cx String representation of the x-coordinate.
     */
    void setCX(string& cx);

    /**
     * @brief Set the y-coordinate of the center.
     * @param cy String representation of the y-coordinate.
     */
    void setCY(string& cy);

    /**
     * @brief Set the radius of the radial gradient.
     * @param r String representation of the radius.
     */
    void setR(string& r);

    /**
     * @brief Set the x-coordinate of the focal point.
     * @param fx String representation of the x-coordinate.
     */
    void setFX(string& fx);

    /**
     * @brief Set the y-coordinate of the focal point.
     * @param fy String representation of the y-coordinate.
     */
    void setFY(string& fy);

    /**
     * @brief Set the focal radius of the radial gradient.
     * @param fr String representation of the focal radius.
     */
    void setFR(string& fr);

    /**
     * @brief Dummy method to set element attributes (not implemented).
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    void setElementAttributes(const string& attribute, string& value) override;

    /**
     * @brief Get the x-coordinate of the center.
     * @return X-coordinate of the center.
     */
    float getCX() const;

    /**
     * @brief Get the y-coordinate of the center.
     * @return Y-coordinate of the center.
     */
    float getCY() const;

    /**
     * @brief Get the radius of the radial gradient.
     * @return Radius of the radial gradient.
     */
    float getR() const;

    /**
     * @brief Get the x-coordinate of the focal point.
     * @return X-coordinate of the focal point.
     */
    float getFX() const;

    /**
     * @brief Get the y-coordinate of the focal point.
     * @return Y-coordinate of the focal point.
     */
    float getFY() const;
};

#endif // !RADIAL_GRADIENT_H
