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
void Circle::setCX(const string& cx) {
	check_exception("circle", "cx", this->cx = stof(cx));
}

void Circle::setCY(const string& cy) {
	check_exception("circle", "cy", this->cy = stof(cy));
}

void Circle::setR(const string& r) {
	check_exception("circle", "r", this->r = stof(r));
}

// Virtual method
void Circle::setAttribute(const string& attribute, const string& value) {
	if (attribute == "cx") setCX(value);
	else if (attribute == "cy") setCY(value);
	else if (attribute == "r") setR(value);
}