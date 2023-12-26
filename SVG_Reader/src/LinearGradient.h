#ifndef LINEAR_GRADIENT_H
#define LINEAR_GRADIENT_H

#include "Gradient.h"

/**
 * @brief Represents a linear gradient with color stops.
 *
 * This class is derived from the Gradient class and includes additional attributes
 * for defining the start and end points of the gradient.
 */
class LinearGradient : public Gradient {
private:
    Point p1; /**< Start point of the linear gradient. */
    Point p2; /**< End point of the linear gradient. */

public:
    /**
     * @brief Default constructor for LinearGradient.
     */
    LinearGradient();

    /**
     * @brief Copy constructor for LinearGradient.
     * @param other The LinearGradient object to copy.
     */
    LinearGradient(const LinearGradient& other);

    /**
     * @brief Set the x-coordinate of the start point.
     * @param x1 String representation of the x-coordinate.
     */
    void setX1(string& x1);

    /**
     * @brief Set the y-coordinate of the start point.
     * @param y1 String representation of the y-coordinate.
     */
    void setY1(string& y1);

    /**
     * @brief Set the x-coordinate of the end point.
     * @param x2 String representation of the x-coordinate.
     */
    void setX2(string& x2);

    /**
     * @brief Set the y-coordinate of the end point.
     * @param y2 String representation of the y-coordinate.
     */
    void setY2(string& y2);

    /**
     * @brief Dummy method to set element attributes (not implemented).
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    void setElementAttributes(const string& attribute, string& value) override;

    /**
     * @brief Get the start point of the linear gradient.
     * @return Point object representing the start point.
     */
    Point getP1() const;

    /**
     * @brief Get the end point of the linear gradient.
     * @return Point object representing the end point.
     */
    Point getP2() const;
};

#endif // !LINEAR_GRADIENT_H
