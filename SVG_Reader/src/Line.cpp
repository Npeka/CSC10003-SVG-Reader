#include "Line.h"
#include "Point.h"

// Constructor
Line::Line() {
	x1 = y1 = x2 = y2 = 0;
}

// Set attribute
void Line::setX1(const string& x1) {
	this->x1 = stof(x1);
}

void Line::setY1(const string& y1) {
	this->y1 = stof(y1);
}

void Line::setX2(const string& x2) {
	this->x2 = stof(x2);
}

void Line::setY2(const string& y2) {
	this->y2 = stof(y2);
}

// Virtual method
void Line::setAttribute(const string& attribute, const string& value) {
	
}

void Line::draw(sf::RenderWindow& window, sf::Transform& transform) {
	
}