#ifndef GROUP_H
#define GROUP_H

#include "Drawable.h"
#include "Figure.h"

/**
 * @brief Represents a group of drawable figures.
 *
 * This class extends both the Figure and Drawable classes to
 * create a group that can contain multiple drawable figures.
 */
class Group : public Figure, public Drawable {
private:
    Group* parent; /**< Pointer to the parent group. */
    std::vector<Drawable*> figures; /**< Vector of drawable figures in the group. */
    std::vector<std::pair<std::string, std::string>> childAttributes; /**< Vector of attributes for child figures. */

public:
    /**
     * @brief Default constructor for Group.
     */
    Group();

    /**
     * @brief Virtual destructor for Group.
     */
    ~Group() override;

    /**
     * @brief Set the parent group.
     * @param parent Pointer to the parent group.
     */
    void setParent(Group* parent);

    /**
     * @brief Set attributes for the parent group.
     */
    void setParentAttributes();

    /**
     * @brief Set attributes for the figures in the group.
     * Overrides the setFigureAttributes method from the Figure class.
     * @param attribute The attribute to set.
     * @param value The value to set for the attribute.
     */
    void setFigureAttributes(const std::string& attribute, std::string& value) override;

    /**
     * @brief Set attributes for child figures in the group.
     * @param figure Pointer to the child figure.
     */
    void setChildAttributes(Figure* figure);

    /**
     * @brief Get the parent group.
     * @return Pointer to the parent group.
     */
    Group* getParent();

    /**
     * @brief Get the vector of drawable figures in the group.
     * @return Vector of drawable figures.
     */
    const std::vector<Drawable*>& getFigures() const;

    /**
     * @brief Add a drawable figure to the group.
     * @param drawable Pointer to the drawable figure.
     */
    void addDrawable(Drawable* drawable);

    /**
     * @brief Draw the group and its child figures.
     * Overrides the draw method from the Drawable class.
     * @param graphics The GDI+ Graphics object.
     */
    void draw(Render_Window) override;
};

#endif // !GROUP_H
