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
	if (attribute == "cx") setCX(value);
	else if (attribute == "cy") setCY(value);
	else if (attribute == "rx") setRX(value);
	else if (attribute == "ry") setRY(value);
}

void Ellipse::setSFigure() {
	ellipse.setPosition(cx, cy);
	ellipse.setFillColor(fill.sfColor());
	ellipse.setOutlineThickness(stroke_width / 2);
	ellipse.setOutlineColor(stroke.sfColor());

	unsigned short quality = 180;
	ellipse.setPointCount(quality);

	for (unsigned short i = 0; i < quality; ++i) {
		float rad = (360 / quality * i) / (360 / M_PI / 2);
		float x = cos(rad) * rx;
		float y = sin(rad) * ry;
		ellipse.setPoint(i, sf::Vector2f(x, y));
	}

	outline = ellipse;
	outline.setFillColor(sf::Color(0, 0, 0, 0));
	outline.setOutlineThickness(-stroke_width / 2);
};

void Ellipse::draw(sf::RenderWindow& window, sf::Transform& transform) {
	window.draw(ellipse, transform);
	window.draw(outline, transform);
}