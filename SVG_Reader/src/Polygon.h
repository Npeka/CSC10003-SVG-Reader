#ifndef POLYGON_H
#define POLYGON_H

#include "Figure.h"

/**
 * @brief The Polygon class represents a polygon in a 2D space.
 *
 * This class is derived from the Figure class and includes a vector of points (points)
 * representing the vertices of the polygon.
 */
class Polygon : public Figure {
protected:
    std::vector<Point> points; /**< Vector of points representing the vertices of the polygon. */

public:
    /**
     * @brief Default constructor for Polygon.
     */
    Polygon() = default;

    /**
     * @brief Set a point for the polygon based on a string representation.
     * @param line The string representation of the point.
     */
    void setPoint(string& line);

    /**
     * @brief Virtual method to set attributes.
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    void setFigureAttributes(const string& attribute, string& value) override;

    /**
     * @brief Destructor for Polygon.
     */
    ~Polygon() override;
};

#endif // !POLYGON_H