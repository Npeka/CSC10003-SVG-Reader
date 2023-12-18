#ifndef TEXT_H
#define TEXT_H

#include "Figure.h"

/**
 * @brief The Text class represents text in a 2D space.
 *
 * This class is derived from the Figure class and includes attributes for the position
 * (x, y), displacement (dx, dy), font size, text anchor, font family, font style, and data (text content).
 */
class Text : public Figure {
protected:
    float x; /**< X-coordinate of the text's position. */
    float y; /**< Y-coordinate of the text's position. */
    float dx; /**< X-displacement of the text. */
    float dy; /**< Y-displacement of the text. */
    float font_size; /**< Font size of the text. */
    string text_anchor; /**< Text anchor property. */
    string font_family; /**< Font family of the text. */
    string font_style; /**< Font style of the text. */
    string data; /**< Text content. */

public:
    /**
     * @brief Default constructor for Text.
     */
    Text();

    /**
     * @brief Set the x-coordinate of the text's position.
     * @param x The x-coordinate to set.
     */
    void setX(string& x);

    /**
     * @brief Set the y-coordinate of the text's position.
     * @param y The y-coordinate to set.
     */
    void setY(string& y);

    /**
     * @brief Set the x-displacement of the text.
     * @param dx The x-displacement to set.
     */
    void setDx(string& dx);

    /**
     * @brief Set the y-displacement of the text.
     * @param dy The y-displacement to set.
     */
    void setDy(string& dy);

    /**
     * @brief Set the font size of the text.
     * @param font_size The font size to set.
     */
    void setFontSize(string& font_size);

    /**
     * @brief Set the text anchor property.
     * @param text_anchor The text anchor to set.
     */
    void setTextAnchor(string& text_anchor);

    /**
     * @brief Set the font family of the text.
     * @param font_family The font family to set.
     */
    void setFontFamily(string& font_family);

    /**
     * @brief Set the font style of the text.
     * @param font_style The font style to set.
     */
    void setFontStyle(string& font_style);

    /**
     * @brief Set the data (text content) of the text.
     * @param data The text content to set.
     */
    void setData(string& data);

    /**
     * @brief Virtual method to set attributes.
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    void setFigureAttributes(const string& attribute, string& value) override;

    /**
     * @brief Destructor for Text.
     */
    ~Text() override = default;
};

#endif // !TEXT_H