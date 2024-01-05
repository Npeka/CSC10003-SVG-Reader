#ifndef SVG_ELEMENT_H
#define SVG_ELEMENT_H

#include "Header.h"
class SVG_Element;
typedef std::unordered_map<string, SVG_Element*> Defs_Type; /**< Type definition for the map of IDs to SVG elements. */

/**
 * @brief Base class representing an element in an SVG document.
 *
 * This class provides functionality for managing an element's ID, style,
 * and attributes. It also includes a virtual method for setting element attributes.
 */
class SVG_Element {
protected:
    string id; /**< ID of the SVG element. */
    Defs_Type* id_map; /**< Map of IDs to SVG elements. */

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
    void setID(const string& id, Defs_Type* image = nullptr);

    /**
    * @brief Set the map of IDs to SVG elements.
    * @param id_map The map of IDs to SVG elements.
    */
    void setID_Map(Defs_Type* id_map);

    /**
     * @brief Get the ID of the SVG element.
     * @return The ID of the SVG element.
     */
    string getID() const;

    /**
     * @brief Virtual method to set attributes for the SVG element.
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    virtual void setElementAttributes(const string& attribute, string& value) = 0;
};

/**
 * @brief Find a global SVG element by its ID.
 *
 * @param id The ID of the SVG element to find.
 * @param id_map Pointer to the map of global IDs to SVG elements.
 * @return Pointer to the found SVG element, or nullptr if not found.
 */
SVG_Element* findGlobalElement(const string& id, const Defs_Type* id_map);

#endif // !SVG_ELEMENT_H
