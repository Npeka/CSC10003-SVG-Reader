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
void Ellipse::setCX(const std::string& cx) {
	check_exception("ellipse", "cx", this->cx = stof(cx));
}

void Ellipse::setCY(const std::string& cy) {
	check_exception("ellipse", "cy", this->cy = stof(cy));
}

void Ellipse::setRX(const std::string& rx) {
	check_exception("ellipse", "rx", this->rx = stof(rx));
}

void Ellipse::setRY(const std::string& ry) {
	check_exception("ellipse", "ry", this->ry = stof(ry));
}

// Virtual method
void Ellipse::setAttributes(const std::string& attribute, const std::string& value) {
	if (attribute == "cx") setCX(value);
	else if (attribute == "cy") setCY(value);
	else if (attribute == "rx") setRX(value);
	else if (attribute == "ry") setRY(value);
}