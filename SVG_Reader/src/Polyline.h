#ifndef POLYLINE_H
#define POLYLINE_H

#include "Figure.h"

/**
 * @brief The Polyline class represents a polyline in a 2D space.
 *
 * This class is derived from the Figure class and includes a vector of points (points)
 * representing the vertices of the polyline.
 */
class Polyline : public Figure {
protected:
    std::vector<Point> points; /**< Vector of points representing the vertices of the polyline. */

public:
    /**s
     * @brief Default constructor for Polyline.
     */
    Polyline() = default;

    /**
     * @brief Set a point for the polyline based on a string representation.
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
     * @brief Destructor for Polyline.
     */
    ~Polyline() override;
};

#endif // !POLYLINE_H