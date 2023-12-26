#ifndef PATH_H
#define PATH_H

#include "Figure.h"

/**
 * @brief The Path class represents a path consisting of multiple line segments in a 2D space.
 *
 * This class is derived from the Figure class and includes a vector (path) of pairs, where each
 * pair contains a character and a vector of points. The character might represent a specific
 * operation (e.g., move to, line to), and the vector of points represents the coordinates of the path.
 */
class Path : public Figure {
protected:
    vector<pair<char, vector<Point>>> path; /**< Vector of pairs representing the path. */

public:
    /**
     * @brief Default constructor for Path.
     */
    Path() = default;

    /**
     * @brief Set the path based on a string representation.
     * @param line The string representation of the path.
     */
    void setPath(string& line);

    /**
     * @brief Virtual method to set attributes.
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    void setFigureAttributes(const string& attribute, string& value) override;

    /**
     * @brief Destructor for Path.
     */
    ~Path() override = default;
};

#endif // !PATH_H
