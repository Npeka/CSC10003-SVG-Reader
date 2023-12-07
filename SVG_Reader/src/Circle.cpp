#include "Circle.h"

// Constructor
Circle::Circle() {
	cx = cy = r = 0;
}

Circle::Circle(const Circle& circle) : Figure(circle){
	cx = circle.cx;
	cy = circle.cy;
	r = circle.r;
}

// Set attribute
void Circle::setCX(const std::string& cx) {
	check_exception("circle", "cx", this->cx = stof(cx));
}

void Circle::setCY(const std::string& cy) {
	check_exception("circle", "cy", this->cy = stof(cy));
}

void Circle::setR(const std::string& r) {
	check_exception("circle", "r", this->r = stof(r));
}

// Virtual method
void Circle::setAttributes(const std::string& attribute, const std::string& value) {
	if (attribute == "cx") setCX(value);
	else if (attribute == "cy") setCY(value);
	else if (attribute == "r") setR(value);
}