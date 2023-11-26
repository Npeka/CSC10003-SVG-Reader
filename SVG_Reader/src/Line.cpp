#include "Line.h"

// Constructor
Line::Line() {
	p1 = p2 = { 0, 0 };
}

Line::Line(const Point& p1, const Point& p2) {
	this->p1 = p1; 
	this->p2 = p2; 
}

Line::Line(const Line& line) : Figure(line) {
	p1 = line.p1;
	p2 = line.p2;
}

// Set attribute
void Line::setX1(const string& x1) {
	check_exception("line", "x1", this->p1.x = stof(x1));
}

void Line::setY1(const string& y1) {
	check_exception("line", "y1", this->p1.y = stof(y1));
}

void Line::setX2(const string& x2) {
	check_exception("line", "x2", this->p2.x = stof(x2));
}

void Line::setY2(const string& y2) {
	check_exception("line", "y2", this->p2.y = stof(y2));
}

// Virtual method
void Line::setAttribute(const string& attribute, const string& value) {
	if (attribute == "x1") setX1(value);
	else if (attribute == "y1") setY1(value);
	else if (attribute == "x2") setX2(value);
	else if (attribute == "y2") setY2(value);
}
