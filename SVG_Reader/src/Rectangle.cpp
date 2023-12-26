#include "Rectangle.h"

// Constructor
Rectangle::Rectangle() :
	x(0), y(0), 
	rx(0), ry(0),
	width(0), height(0)
{}

// Set attribute
void Rectangle::setX(string& x) {
	check_exception("rectangle", "x", this->x = stof(x));
}

void Rectangle::setY(string& y) {
	check_exception("rectangle", "y", this->y = stof(y));
}

void Rectangle::setRX(string& rx) {
	check_exception("rectangle", "rx", this->rx = stof(rx));
}

void Rectangle::setRY(string& ry) {
	check_exception("rectangle", "ry", this->ry = stof(ry));
}

void Rectangle::setWidth(string& width) {
	check_exception("rectangle", "width", this->width = stof(width));
}

void Rectangle::setHeight(string& height) {
	check_exception("rectangle", "height", this->height = stof(height));
}

// Virtual method
void Rectangle::setFigureAttributes(const string& attribute, string& value) {
	if (attribute == "x") setX(value);
	else if (attribute == "y") setY(value);
	else if (attribute == "rx") setRX(value);
	else if (attribute == "ry") setRY(value);
	else if (attribute == "width") setWidth(value);
	else if (attribute == "height") setHeight(value);
}