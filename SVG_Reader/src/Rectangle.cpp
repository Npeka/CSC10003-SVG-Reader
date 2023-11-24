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
	this->x = stof(x);
}

void Rectangle::setY(const string& y) {
	this->y = stof(y);
}

void Rectangle::setRX(const string& rx) {
	this->rx = stof(rx);
}

void Rectangle::setRY(const string& ry) {
	this->ry = stof(ry);
}

void Rectangle::setWidth(const string& width) {
	this->width = stof(width);
}

void Rectangle::setHeight(const string& height) {
	this->height = stof(height);
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