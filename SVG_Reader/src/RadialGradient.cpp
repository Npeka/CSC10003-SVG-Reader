#include "RadialGradient.h"

RadialGradient::RadialGradient() :
	cx(0), cy(0), r(0)
{}
	
RadialGradient::RadialGradient(const RadialGradient& other) : Gradient(other),
	cx(other.cx), cy(other.cy), r(other.r)
{}

void RadialGradient::setCX(string& cx) {
	this->cx = stof(cx);
}

void RadialGradient::setCY(string& cy) {
	this->cy = stof(cy);
}

void RadialGradient::setR(string& r) {
	this->r = stof(r);
}

void RadialGradient::setElementAttributes(const string& attribute, string& value) {
	if (attribute == "cx") setCX(value);
	else if (attribute == "cy") setCY(value);
	else if (attribute == "r") setR(value);
}

float RadialGradient::getCX() const {
	return cx;
}

float RadialGradient::getCY() const {
	return cy;
}

float RadialGradient::getR() const {
	return r;
}