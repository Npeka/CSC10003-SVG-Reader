#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Header.h"

/**
 * @brief Represents a transformation applied to an object.
 *
 * This class provides methods to set various types of transformations
 * such as translate, rotate, scale, matrix, and a combined transform.
 * The transformations are stored in the Transform_Type enum.
 */
class Transform {
protected:
    Transform_Type transforms; /**< Enum representing various transformations. */

public:
    /**
     * @brief Default constructor for Transform.
     */
    Transform() = default;

    /**
     * @brief Copy constructor for Transform.
     * @param other The Transform object to copy.
     */
    Transform(const Transform& other);

    /**
     * @brief Virtual destructor for Transform.
     */
    virtual ~Transform();

    /**
     * @brief Set the translate transformation.
     * @param translate String representation of the translation.
     */
    void setTranslate(string& translate);

    /**
     * @brief Set the rotate transformation.
     * @param rotate String representation of the rotation.
     */
    void setRotate(string& rotate);

    /**
     * @brief Set the scale transformation.
     * @param scale String representation of the scaling.
     */
    void setScale(string& scale);

    /**
     * @brief Set the matrix transformation.
     * @param matrix String representation of the transformation matrix.
     */
    void setMatrix(string& matrix);

    /**
     * @brief Set the combined transform.
     * @param transform String representation of the combined transform.
     */
    void setTransform(string& transform);

    /**
     * @brief Get the Transform_Type enum representing the transformations.
     * @return Transform_Type enum.
     */
    Transform_Type getTransform() const;
};

#endif // !TRANSFORM_H
