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

void Stop::setColor(string& color) {
	this->color.setRGB(color);
}

void Stop::setOffset(string& offset) {
	check_exception("Stop", "offset", this->offset = stof(offset));
}

RGB_Color Stop::getColor() {
	return color;
}

float Stop::getOffset() {
	return offset;
}

// Gradient
Gradient::Gradient() : Color(),
	isPercent(false)
{}

Gradient::Gradient(const Gradient& other) : Color(other),
	ColorOffset(other.ColorOffset),
	isPercent(other.isPercent)
{}

void Gradient::addStop(string& line) {
	std::stringstream ss(line);
	string attribute, value;
	Stop stop;
	while (ss >> attribute) {
		char end;
		ss >> end;
		getline(ss, value, end);
		if (attribute == "stop-color") stop.setColor(value);
		if (attribute == "offset") stop.setOffset(value);
	}
	ColorOffset.push_back(stop);
}

void Gradient::setHref(string& href) {
	auto gradient = findGlobalElement(href);
	if (gradient != nullptr) {
		ColorOffset = dynamic_cast<Gradient*>(gradient)->getColorOffset();
	}
}

void Gradient::setElementAttributes(const string& attribute, string& value) {
	if (attribute == "xlink:href") setHref(value);
}

vector<Stop> Gradient::getColorOffset() const {
	return ColorOffset;
}

bool Gradient::getIsPercent() const {
	return isPercent;
}