#include "Rectangle.h"

// Constructor
Rectangle::Rectangle() {
	x = y = rx = ry = 0; 
	width = height = 0;
}

Rectangle::Rectangle(const Rectangle& rectangle) : Figure(rectangle) {
	x = rectangle.x;
	y = rectangle.y;
	rx = rectangle.rx;
	ry = rectangle.ry;
	width = rectangle.width;
	height = rectangle.height;
}

// Set attribute
void Rectangle::setX(const string& x) {
	check_exception("rectangle", "x", this->x = stof(x));
}

void Rectangle::setY(const string& y) {
	check_exception("rectangle", "y", this->y = stof(y));
}

void Rectangle::setRX(const string& rx) {
	check_exception("rectangle", "rx", this->rx = stof(rx));
}

void Rectangle::setRY(const string& ry) {
	check_exception("rectangle", "ry", this->ry = stof(ry));
}

void Rectangle::setWidth(const string& width) {
	check_exception("rectangle", "width", this->width = stof(width));
}

void Rectangle::setHeight(const string& height) {
	check_exception("rectangle", "height", this->height = stof(height));
}

// Virtual method
void Rectangle::setAttribute(const string& attribute, const string& value) {
	if (attribute == "x") setX(value);
	else if (attribute == "y") setY(value);
	else if (attribute == "rx") setRX(value);
	else if (attribute == "ry") setRY(value);
	else if (attribute == "width") setWidth(value);
	else if (attribute == "height") setHeight(value);
}