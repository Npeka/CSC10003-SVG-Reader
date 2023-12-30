#include "Gradient.h"
#include "LinearGradient.h"
#include "RadialGradient.h"

Gradient* getGradient(const string& color) {
	if (color == "linearGradient") return new LinearGradient();
	if (color == "radialGradient") return new RadialGradient();
	return nullptr;
}

// Stop gradient
Stop::Stop() : 
	color(), 
	offset(0) 
{}

Stop::Stop(const Stop& other) : 
	color(other.color), 
	offset(other.offset) 
{}

void Stop::setColor(string& color) {
	this->color.setRGB(color);
}

void Stop::setOffset(string& offset) {
	check_exception("Stop", "offset", this->offset = stof(offset));
}

void Stop::setOpacity(string& opacity) {
	check_exception("Stop", "opacity", color.setOpacity(opacity));
}

RGB_Color Stop::getColor() {
	return color;
}

float Stop::getOffset() {
	return offset;
}

// Gradient
Gradient::Gradient() : Color(), Transform(),
	isPercent(false)
{}

Gradient::Gradient(const Gradient& other) : Color(other), Transform(other),
	ColorOffset(other.ColorOffset),
	isPercent(other.isPercent)
{}

void Gradient::addStop(string& line) {
	std::stringstream ss(line);
	string attribute, value;
	Stop stop;
	while (ss >> attribute) {
		char end; ss >> end;
		getline(ss, value, end);
		if (attribute == "stop-color") stop.setColor(value);
		else if (attribute == "stop-opacity") stop.setOpacity(value);
		else if (attribute == "offset") stop.setOffset(value);
	}
	ColorOffset.push_back(stop);
}

void Gradient::setHref(string& href) {
	auto gradient = findGlobalElement(href);
	if (gradient != nullptr) {
		ColorOffset = dynamic_cast<Gradient*>(gradient)->getColorOffset();
	}
}

void Gradient::setGradientUnits(string& gradientUnits) {
	if (gradientUnits == "userSpaceOnUse") isPercent = false;
	else if (gradientUnits == "objectBoundingBox") isPercent = true;
}

void Gradient::setElementAttributes(const string& attribute, string& value) {
	if (attribute == "xlink:href") setHref(value);
	else if (attribute == "gradientTransform") setTransform(value);
	else if (attribute == "gradientUnits") setGradientUnits(value);
}

vector<Stop> Gradient::getColorOffset() const {
	return ColorOffset;
}

bool Gradient::getIsPercent() const {
	return isPercent;
}