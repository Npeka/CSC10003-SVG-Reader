#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"
#include "RGB_Color.h"
#include "Transform.h"

/**
 * @brief Base class for SVG figures with transformation capabilities.
 */
class Figure : public SVG_Element, public Transform {
protected:
    Color* fill; ///< Fill color of the figure.
    Color* stroke; ///< Stroke color of the figure.
    float stroke_width; ///< Width of the stroke.

public:
    /**
     * @brief Default constructor for Figure.
     */
    Figure();

    /**
     * @brief Set the fill color of the figure.
     * @param fill The fill color to set.
     */
    void setFill(string& fill);

    /**
     * @brief Set the fill opacity of the figure.
     * @param fill_opacity The fill opacity to set.
     */
    void setFillOpacity(string& fill_opacity);

    /**
     * @brief Set the stroke color of the figure.
     * @param stroke The stroke color to set.
     */
    void setStroke(string& stroke);

    /**
     * @brief Set the stroke opacity of the figure.
     * @param stroke_opacity The stroke opacity to set.
     */
    void setStrokeOpacity(string& stroke_opacity);

    /**
     * @brief Set the stroke width of the figure.
     * @param stroke_width The stroke width to set.
     */
    void setStrokeWidth(string& stroke_width);

    /**
     * @brief Set attributes for a group of figures.
     * @param group The group of figures to set attributes for.
     */
    void setGroupAttributes(Figure* group);

    /**
     * @brief Set attributes for an individual element.
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    void setElementAttributes(const string& attribute, string& value) override final;

    /**
     * @brief Virtual method to set specific figure attributes.
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    virtual void setFigureAttributes(const string& attribute, string& value) {};

    /**
     * @brief Destructor for Figure.
     */
    virtual ~Figure();
};



/**
 * @brief Factory class for creating Figure instances.
 */
class FigureFactory {
private:
    static FigureFactory* Instance; ///< Singleton instance of FigureFactory.

    /**
     * @brief Private constructor for FigureFactory.
     */
    FigureFactory() = default;

public:
    /**
     * @brief Get the singleton instance of FigureFactory.
     * @return The singleton instance of FigureFactory.
     */
    static FigureFactory* getInstance();

    /**
     * @brief Get a specific type of figure.
     * @param figure The type of figure to create.
     * @return A pointer to the created figure.
     */
    static Figure* getFigure(const string& figure);

    /**
     * @brief Delete the singleton instance of FigureFactory.
     */
    static void deleteInstance();
};

#endif // !FIGURE_H
