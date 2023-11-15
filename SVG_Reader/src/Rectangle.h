#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Figure.h"
#include "Point.h"

class Rectangle : public Figure {
private:
    Point p; 
    float rx; 
    float ry; 
    float width;
    float height;
public:
    // Constructor
    Rectangle();

    // Set attribute
    void setX(const string& x);
    void setY(const string& y);
    void setRX(const string& rx);
    void setRY(const string& ry);
    void setWidth(const string& width);
    void setHeight(const string& height);

    // Virtual method
    void setAttribute(const string& attribute, const string& value) override;
    void draw(sf::RenderWindow& window, sf::Transform& transform) override;
    ~Rectangle() override = default;
};

#endif // !RECTANGLE_H

