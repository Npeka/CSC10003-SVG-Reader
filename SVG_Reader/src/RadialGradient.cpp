#include "RadialGradient.h"

RadialGradient::RadialGradient() :
	cx(0), cy(0), r(0),
	fx(0), fy(0), fr(0)
{}
	
RadialGradient::RadialGradient(const RadialGradient& other) : Gradient(other),
	cx(other.cx), cy(other.cy), r(other.r),
	fx(other.fx), fy(other.fy), fr(other.fr)
{}

void RadialGradient::setCX(string& cx) {
	if (cx.find("%") != string::npos) isPercent = true;
	check_exception("RadialGradient", "cx", this->cx = stof(cx));
}

void RadialGradient::setCY(string& cy) {
	if (cy.find("%") != string::npos) isPercent = true;
	check_exception("RadialGradient", "cy", this->cy = stof(cy));
}

void RadialGradient::setR(string& r) {
	if (r.find("%") != string::npos) isPercent = true;
	check_exception("RadialGradient", "r", this->r = stof(r));
}

void RadialGradient::setFX(string& fx) {
	if (fx.find("%") != string::npos) isPercent = true;
	check_exception("RadialGradient", "fx", this->fx = stof(fx));
}

void RadialGradient::setFY(string& fy) {
	if (fy.find("%") != string::npos) isPercent = true;
	check_exception("RadialGradient", "fy", this->fy = stof(fy));
}

void RadialGradient::setFR(string& fr) {
	if (fr.find("%") != string::npos) isPercent = true;
	check_exception("RadialGradient", "fr", this->fr = stof(fr));
}

void RadialGradient::setElementAttributes(const string& attribute, string& value) {
	if (attribute == "cx") setCX(value);
	else if (attribute == "cy") setCY(value);
	else if (attribute == "r") setR(value);
	else if (attribute == "fx") setFX(value);
	else if (attribute == "fy") setFY(value);
	else if (attribute == "fr") setFR(value);
	else Gradient::setElementAttributes(attribute, value);
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