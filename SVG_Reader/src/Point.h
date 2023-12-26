#ifndef POINT_H
#define POINT_H

/**
 * @brief The Point class represents a point in a 2D space.
 *
 * This class has attributes for the x-coordinate (x) and y-coordinate (y) of the point.
 */
class Point {
public:
    float x; /**< The x-coordinate of the point. */
    float y; /**< The y-coordinate of the point. */

    /**
     * @brief Default constructor for Point.
     */
    Point();

    /**
     * @brief Parameterized constructor for Point.
     * @param x The x-coordinate of the point.
     * @param y The y-coordinate of the point.
     */
    Point(const float& x, const float& y);

    /**
     * @brief Copy constructor for Point.
     * @param point The Point object to copy.
     */
    Point(const Point& point);

    /**
     * @brief Destructor for Point.
     */
    ~Point() = default;
};

#endif // !POINT_H