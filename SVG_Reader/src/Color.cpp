#include "Color.h"

// Constructor
Color::Color() {
	r = g = b = 0;
	a = 255;
}

Color::Color(const string& color) {
	setRGB(color);
}

Color::Color(const Color& color) {
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
}

Color::Color(const float& r, const float& g, const float& b, const float& a) {
	this->r = r; 
	this->g = g;
	this->b = b;
	this->a = a;
}

// Set attribute
void Color::setA(const float& a) {
	this->a = a * 255;
}

void Color::setA(const string& a) {
    if (this->a) this->a = stof(a) * 256;
}

void Color::setRGB(const string& color) {
	if (color.find("rgb") != string::npos) {
		string rgb(color);
		for (char& c : rgb) if (!isdigit(c)) c = ' ';
		stringstream ss(rgb); ss >> r >> g >> b;
	}
	else if (color[0] == '#') {
		r = stoi(color.substr(1, 2), NULL, 16);
		g = stoi(color.substr(3, 2), NULL, 16);
		b = stoi(color.substr(5, 2), NULL, 16);
	}
    else if (color == "none") {
        a = 0;
    }
    else {
        *this = setColorByName(color);
	}
}

void Color::setRGB(const float& r, const float& g, const float& b, const float& a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color& Color::operator=(const Color& color) {
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
    return *this;
}

sf::Color Color::sfColor() {
    return sf::Color(r, g, b, a);
}

const Color& setColorByName(const string& color) {
    
}