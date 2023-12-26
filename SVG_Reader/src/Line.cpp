#include "Line.h"

// Constructor
Line::Line() : 
	p1(Point()),
	p2(Point())
{}

// Set attribute
void Line::setX1(string& x1) {
	check_exception("line", "x1", this->p1.x = stof(x1));
}

void Line::setY1(string& y1) {
	check_exception("line", "y1", this->p1.y = stof(y1));
}

void Line::setX2(string& x2) {
	check_exception("line", "x2", this->p2.x = stof(x2));
}

void Line::setY2(string& y2) {
	check_exception("line", "y2", this->p2.y = stof(y2));
}

// Virtual method
void Line::setFigureAttributes(const string& attribute, string& value) {
	if (attribute == "x1") setX1(value);
	else if (attribute == "y1") setY1(value);
	else if (attribute == "x2") setX2(value);
	else if (attribute == "y2") setY2(value);
}
