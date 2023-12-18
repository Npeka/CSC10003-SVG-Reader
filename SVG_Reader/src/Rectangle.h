#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"

/**
 * @brief The Rectangle class represents a rectangle in a 2D space.
 *
 * This class is derived from the Figure class and includes attributes for the position
 * (x, y), radii (rx, ry), width, and height of the rectangle.
 */
class Rectangle : public Figure {
protected:
    float x; /**< X-coordinate of the rectangle's position. */
    float y; /**< Y-coordinate of the rectangle's position. */
    float rx; /**< X-radius of the rectangle. */
    float ry; /**< Y-radius of the rectangle. */
    float width; /**< Width of the rectangle. */
    float height; /**< Height of the rectangle. */

public:
    /**
     * @brief Default constructor for Rectangle.
     */
    Rectangle();

    /**
     * @brief Set the x-coordinate of the rectangle's position.
     * @param x The x-coordinate to set.
     */
    void setX(string& x);

    /**
     * @brief Set the y-coordinate of the rectangle's position.
     * @param y The y-coordinate to set.
     */
    void setY(string& y);

    /**
     * @brief Set the x-radius of the rectangle.
     * @param rx The x-radius to set.
     */
    void setRX(string& rx);

    /**
     * @brief Set the y-radius of the rectangle.
     * @param ry The y-radius to set.
     */
    void setRY(string& ry);

    /**
     * @brief Set the width of the rectangle.
     * @param width The width to set.
     */
    void setWidth(string& width);

    /**
     * @brief Set the height of the rectangle.
     * @param height The height to set.
     */
    void setHeight(string& height);

    /**
     * @brief Virtual method to set attributes.
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    void setFigureAttributes(const string& attribute, string& value) override;

    /**
     * @brief Destructor for Rectangle.
     */
    ~Rectangle() override = default;
};

#endif // !RECTANGLE_H