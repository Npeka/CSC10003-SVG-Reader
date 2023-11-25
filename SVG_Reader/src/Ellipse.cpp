#include "Ellipse.h"

// Constructor
Ellipse::Ellipse() {
	cx = cy = rx = ry = 0;
}

Ellipse::Ellipse(const Ellipse& ellipse) : Figure(ellipse) {
	cx = ellipse.cx;
	cy = ellipse.cy;
	rx = ellipse.rx;
	ry = ellipse.ry;
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