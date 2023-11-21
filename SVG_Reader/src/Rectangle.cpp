#include "Rectangle.h"

// Constructor
Rectangle::Rectangle() {
	x = y = rx = ry = 0;
	width = height = 0;
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

void Rectangle::setSFigure() {
	rectangle.setSize(sf::Vector2f(width, height));	// width height
	rectangle.setPosition(x, y);								// x y
	rectangle.setFillColor(fill.sfColor());						// fill 
	rectangle.setOutlineThickness(stroke_width / 2);
	rectangle.setOutlineColor(stroke.sfColor());

	outline = rectangle;
	outline.setFillColor(sf::Color(0, 0, 0, 0));
	outline.setOutlineThickness(-stroke_width / 2);

};

void Rectangle::draw(sf::RenderWindow & window, sf::Transform & transform) {
	window.draw(rectangle, transform);
	window.draw(outline, transform);
}