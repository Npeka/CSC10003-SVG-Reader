#include "RGB_Color.h"
#include "LinearGradient.h"
#include "RadialGradient.h"

Color::Color() : SVG_Element(),
	opacity(255)
{}

Color::Color(const Color& other) : SVG_Element(other),
	opacity(other.opacity)
{}

void Color::setOpacity(string& opacity) {
	check_exception("Color", "opacity", this->opacity = stof(opacity) * 255);
}

void Color::setOpacity(const float& opacity) {
	this->opacity = opacity * 255;
}

void createColor(Color*& color, string name) {
	auto it = color->findGlobalElement(name);
	if (it != nullptr) {
		copyColor(color, dynamic_cast<Color*>(it));
	}
	else if (color == nullptr) color = new RGB_Color(name);
	else color->setRGB(name);
}

void copyColor(Color*& color, Color* copy) {
	dealocate(color);
	if (dynamic_cast<RGB_Color*>(copy)) {
		color = new RGB_Color(*dynamic_cast<RGB_Color*>(copy));
	} 
	else if (dynamic_cast<LinearGradient*>(copy)) {
		color = new LinearGradient(*dynamic_cast<LinearGradient*>(copy));
	}
	else if (dynamic_cast<RadialGradient*>(copy)) {
		color = new RadialGradient(*dynamic_cast<RadialGradient*>(copy));
	}
}

