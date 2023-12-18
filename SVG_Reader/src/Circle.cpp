#include "Circle.h"

// Constructor
Circle::Circle() : 
	cx(0), cy(0), r(0)
{}

// Set attribute
void Circle::setCX(string& cx) {
	check_exception("circle", "cx", this->cx = stof(cx));
}

void Circle::setCY(string& cy) {
	check_exception("circle", "cy", this->cy = stof(cy));
}

void Circle::setR(string& r) {
	check_exception("circle", "r", this->r = stof(r));
}

// Virtual method
void Circle::setFigureAttributes(const string& attribute, string& value) {
	if (attribute == "cx") setCX(value);
	else if (attribute == "cy") setCY(value);
	else if (attribute == "r") setR(value);
}