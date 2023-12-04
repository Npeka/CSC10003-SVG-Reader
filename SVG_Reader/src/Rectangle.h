#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"

class Rectangle : public Figure {
protected:
    float x;
    float y;
    float rx; 
    float ry; 
    float width;
    float height;
public:
    // Constructor
    Rectangle();
    Rectangle(const Rectangle& rectangle);

    // Set attribute
    void setX(const std::string& x);
    void setY(const std::string& y);
    void setRX(const std::string& rx);
    void setRY(const std::string& ry);
    void setWidth(const std::string& width);
    void setHeight(const std::string& height);

    // Virtual method
    void setAttribute(const std::string& attribute, const std::string& value) override;
    ~Rectangle() override = default;
};

#endif // !RECTANGLE_H

