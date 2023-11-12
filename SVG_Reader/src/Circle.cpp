#include "Circle.h"

// Constructor
Circle::Circle() {
	cx = cy = r = 0;
}

// Set attribute
void Circle::setCX(const string& cx) {
	this->cx = stof(cx);
}

void Circle::setCY(const string& cy) {
	this->cy = stof(cy);
}

void Circle::setR(const string& r) {
	this->r = stof(r);
}

// Virtual method
void Circle::setAttribute(const string& attribute, const string& value) {
	if (attribute == "cx") setCX(value);
	else if (attribute == "cy") setCY(value);
	else if (attribute == "r") setR(value);
}

void Circle::draw(sf::RenderWindow& window, sf::Transform& transform) {
	sf::CircleShape circle(r);
	circle.setPosition(cx - r, cy - r);								// cx cy
	circle.setFillColor(fill.sfColor());							// fill
	circle.setOutlineThickness(stroke_width);						// stroke-width
	circle.setOutlineColor(stroke.sfColor());						// 
	circle.setPointCount(2000);
	window.draw(circle, transform);
}