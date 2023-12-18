#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Figure.h"

/**
 * @brief The Ellipse class represents an ellipse in a 2D space.
 *
 * This class is derived from the Figure class and includes attributes for the center
 * coordinates (cx, cy) and radii along the x-axis (rx) and y-axis (ry).
 */
class Ellipse : public Figure {
protected:
    float cx; /**< The x-coordinate of the center. */
    float cy; /**< The y-coordinate of the center. */
    float rx; /**< The radius along the x-axis. */
    float ry; /**< The radius along the y-axis. */

public:
    /**
     * @brief Default constructor for Ellipse.
     */
    Ellipse();

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
     * @brief Set the radius along the x-axis.
     * @param rx The radius along the x-axis to set.
     */
    void setRX(string& rx);

    /**
     * @brief Set the radius along the y-axis.
     * @param ry The radius along the y-axis to set.
     */
    void setRY(string& ry);

    /**
     * @brief Virtual method to set attributes.
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    void setFigureAttributes(const string& attribute, string& value) override;

    /**
     * @brief Destructor for Ellipse.
     */
    ~Ellipse() override = default;
};

#endif // !ELLIPSE_H
