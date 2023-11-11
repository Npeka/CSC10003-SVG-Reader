#include "Ellipse.h"

// Constructor
Ellipse::Ellipse() {
	cx = cy = rx = ry = 0;
}

// Set attribute
void Ellipse::setCX(const string& cx) {
	this->cx = stof(cx);
}

void Ellipse::setCY(const string& cy) {
	this->cy = stof(cy);
}

void Ellipse::setRX(const string& rx) {
	this->rx = stof(rx);
}

void Ellipse::setRY(const string& ry) {
	this->ry = stof(ry);
}

// Virtual method
void Ellipse::setAttribute(const string& attribute, const string& value) {
	
}

void Ellipse::draw(sf::RenderWindow& window, sf::Transform& transform) {
	
}