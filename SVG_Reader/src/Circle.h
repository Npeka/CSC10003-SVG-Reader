#ifndef CIRCLE_H
#define CIRCLE_H

#include "Figure.h"

/**
 * @brief The Circle class represents a circle in a 2D space.
 *
 * This class is derived from the Figure class and includes attributes
 * such as center coordinates (cx, cy) and radius (r).
 */
class Circle : public Figure {
protected:
    float cx; /**< X-coordinate of the center. */
    float cy; /**< Y-coordinate of the center. */
    float r;  /**< Radius of the circle. */

public:
    /**
     * @brief Default constructor for the Circle class.
     *
     * Initializes the circle with default values.
     */
    Circle();

    /**
     * @brief Copy constructor for the Circle class.
     *
     * Creates a copy of the given Circle object.
     *
     * @param circle The Circle object to be copied.
     */
    Circle(const Circle& circle);

    /**
     * @brief Set the X-coordinate of the center.
     *
     * @param cx The new value for the X-coordinate.
     */
    void setCX(const string& cx);

    /**
     * @brief Set the Y-coordinate of the center.
     *
     * @param cy The new value for the Y-coordinate.
     */
    void setCY(const string& cy);

    /**
     * @brief Set the radius of the circle.
     *
     * @param r The new value for the radius.
     */
    void setR(const string& r);

    /**
     * @brief Set an attribute of the circle based on the attribute name and value.
     *
     * This method is overridden from the base class Figure.
     *
     * @param attribute The name of the attribute to set.
     * @param value The new value for the attribute.
     */
    void setAttribute(const string& attribute, const string& value) override;

    /**
     * @brief Destructor for the Circle class.
     *
     * The destructor is set to the default implementation.
     */
    ~Circle() override = default;
};

#endif // !CIRCLE_H
