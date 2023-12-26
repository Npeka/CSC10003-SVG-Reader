#include "Ellipse.h"

// Constructor
Ellipse::Ellipse() : 
	cx(0), cy(0), rx(0), ry(0) 
{}

// Set attribute
void Ellipse::setCX(string& cx) {
	check_exception("ellipse", "cx", this->cx = stof(cx));
}

void Ellipse::setCY(string& cy) {
	check_exception("ellipse", "cy", this->cy = stof(cy));
}

void Ellipse::setRX(string& rx) {
	check_exception("ellipse", "rx", this->rx = stof(rx));
}

void Ellipse::setRY(string& ry) {
	check_exception("ellipse", "ry", this->ry = stof(ry));
}

// Virtual method
void Ellipse::setFigureAttributes(const string& attribute, string& value) {
	if (attribute == "cx")	setCX(value);
	else if (attribute == "cy") setCY(value);
	else if (attribute == "rx") setRX(value);
	else if (attribute == "ry") setRY(value);
}