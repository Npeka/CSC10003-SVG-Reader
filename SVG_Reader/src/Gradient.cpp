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

void Gradient::setTransform(string& transform) {
	for (char& c : transform) if (c == '(' || c == ',') c = ' ';
	std::stringstream ss(transform);
	string attribute, value;
	while (ss >> attribute) {
		getline(ss, value, ')');
		if (attribute == "translate") setTranslate(value);
		else if (attribute == "rotate") setRotate(value);
		else if (attribute == "scale") setScale(value);
		else if (attribute == "matrix") setMatrix(value);
	}
}

void Gradient::setTranslate(string& translate) {
	std::stringstream ss(translate);
	float x, y;
	ss >> x >> y;
	vector<float> value = { x, y };
	transform.push_back({ SVG_Translate, value });
}

void Gradient::setRotate(string& rotate) {
	std::stringstream ss(rotate);
	float r;
	ss >> r;
	vector<float> value = { r };
	transform.push_back({ SVG_Rotate, value });
}

void Gradient::setScale(string& scale) {
	std::stringstream ss(scale);
	float x, y(0);
	ss >> x >> y;
	if (y == 0) y = x;
	vector<float> value = { x, y };
	transform.push_back({ SVG_Scale, value });
}

void Gradient::setMatrix(string& matrix) {
	std::stringstream ss(matrix);
	float m;
	vector<float> value;
	for (int i = 0; i < 6; i++) {
		ss >> m;
		value.push_back(m);
	}
	transform.push_back({ SVG_Matrix, value });
}

void Gradient::setElementAttributes(const string& attribute, string& value) {
	if (attribute == "xlink:href") setHref(value);
	else if (attribute == "gradientTransform") setTransform(value);
}

vector<Stop> Gradient::getColorOffset() const {
	return ColorOffset;
}

bool Gradient::getIsPercent() const {
	return isPercent;
}

vector<pair<int, vector<float>>> Gradient::getTransform() const {
	return transform;
}