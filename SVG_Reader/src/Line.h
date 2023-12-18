#ifndef LINE_H
#define LINE_H

#include "Figure.h"

/**
 * @brief The Line class represents a line segment in a 2D space.
 *
 * This class is derived from the Figure class and includes attributes for two points (p1, p2)
 * that define the endpoints of the line segment.
 */
class Line : public Figure {
protected:
    Point p1; /**< The first endpoint of the line. */
    Point p2; /**< The second endpoint of the line. */

public:
    /**
     * @brief Default constructor for Line.
     */
    Line();

    /**
     * @brief Set the x-coordinate of the first endpoint.
     * @param x1 The x-coordinate to set.
     */
    void setX1(string& x1);

    /**
     * @brief Set the y-coordinate of the first endpoint.
     * @param y1 The y-coordinate to set.
     */
    void setY1(string& y1);

    /**
     * @brief Set the x-coordinate of the second endpoint.
     * @param x2 The x-coordinate to set.
     */
    void setX2(string& x2);

    /**
     * @brief Set the y-coordinate of the second endpoint.
     * @param y2 The y-coordinate to set.
     */
    void setY2(string& y2);

    /**
     * @brief Virtual method to set attributes.
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    void setFigureAttributes(const string& attribute, string& value) override;

    /**
     * @brief Destructor for Line.
     */
    ~Line() override = default;
};

#endif // !LINE_H