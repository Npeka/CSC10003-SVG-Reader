#include "LinearGradient.h"

LinearGradient::LinearGradient() : Gradient(),
	p1(), p2()
{}

LinearGradient::LinearGradient(const LinearGradient& other) : Gradient(other),
	p1(other.p1), p2(other.p2)
{}

void LinearGradient::setX1(string& x1) {
	if (x1.find("%") != string::npos) isPercent = true;
	check_exception("LinearGradient", "x1", p1.x = stof(x1));
}

void LinearGradient::setY1(string& y1) {
	if (y1.find("%") != string::npos) isPercent = true;
	check_exception("LinearGradient", "y1", p1.y = stof(y1));
}

void LinearGradient::setX2(string& x2) {
	if (x2.find("%") != string::npos) isPercent = true;
	check_exception("LinearGradient", "x2", p2.x = stof(x2));
}

void LinearGradient::setY2(string& y2) {
	if (y2.find("%") != string::npos) isPercent = true;
	check_exception("LinearGradient", "y2", p2.y = stof(y2));
}

void LinearGradient::setElementAttributes(const string& attribute, string& value) {
	if (attribute == "x1") setX1(value);
	else if (attribute == "y1") setY1(value);
	else if (attribute == "x2") setX2(value);
	else if (attribute == "y2") setY2(value);
}

Point LinearGradient::getP1() const {
	return p1;
}

Point LinearGradient::getP2() const {
	return p2;
}