#ifndef CIRCLE_H
#define CIRCLE_H

#include "Figure.h"

/**
 * @brief The Circle class represents a circle in a 2D space.
 *
 * This class is derived from the Figure class and includes attributes for the center
 * coordinates (cx, cy) and the radius (r) of the circle.
 */
class Circle : public Figure {
protected:
    float cx; /**< X-coordinate of the center. */
    float cy; /**< Y-coordinate of the center. */
    float r;  /**< Radius of the circle. */

public:
    /**
     * @brief Default constructor for Circle.
     */
    Circle();

    /**
     * @brief Set the x-coordinate of the center.
     * @param cx The x-coordinate to set.
     */
    void setCX(string& cx);

    /**
     * @brief Set the y-coordinate of the center.
     * @param cy The y-coordinate to set.
     */
    void setCY(string& cy);

    /**
     * @brief Set the radius of the circle.
     * @param r The radius to set.
     */
    void setR(string& r);

    /**
     * @brief Virtual method to set attributes.
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    void setFigureAttributes(const string& attribute, string& value) override;

    /**
     * @brief Destructor for Circle.
     */
    ~Circle() override = default;
};

#endif // !CIRCLE_H