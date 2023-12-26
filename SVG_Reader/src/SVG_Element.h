#ifndef SVG_ELEMENT_H
#define SVG_ELEMENT_H

#include "Header.h"

/**
 * @brief Base class representing an element in an SVG document.
 *
 * This class provides functionality for managing an element's ID, style,
 * and attributes. It also includes a virtual method for setting element attributes.
 */
class SVG_Element {
private:
    static std::unordered_map<string, SVG_Element*> id_map; /**< Static map to store SVG elements by ID. */

protected:
    string id; /**< ID of the SVG element. */

public:
    /**
     * @brief Default constructor for SVG_Element.
     */
    SVG_Element();

    /**
     * @brief Copy constructor for SVG_Element.
     * @param other The SVG_Element object to copy.
     */
    SVG_Element(const SVG_Element& other);

    /**
     * @brief Virtual destructor for SVG_Element.
     */
    virtual ~SVG_Element() = default;

    /**
     * @brief Set the ID of the SVG element.
     * @param id The ID to set.
     */
    void setID(const string& id);

    /**
     * @brief Set the style of the SVG element.
     * @param style The style to set.
     */
    void setStyle(string& style);

    /**
     * @brief Get the ID of the SVG element.
     * @return The ID of the SVG element.
     */
    string getID() const;

    /**
     * @brief Find a global SVG element by ID.
     * @param id The ID to search for.
     * @return Pointer to the found SVG element, or nullptr if not found.
     */
    SVG_Element* findGlobalElement(const string& id);

    /**
     * @brief Parse the attributes of the SVG element from the given line.
     * @param line The line containing the attributes to parse.
     */
    void parseElementAttributes(string& line);

    /**
     * @brief Virtual method to set attributes for the SVG element.
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    virtual void setElementAttributes(const string& attribute, string& value) = 0;
};

#endif // !SVG_ELEMENT_H
