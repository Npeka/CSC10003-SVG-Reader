#include "RGB_Color.h"
#include "LinearGradient.h"
#include "RadialGradient.h"

Color::Color() :
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
		color = dynamic_cast<Color*>(it);
		return;
	}
	if (color == nullptr) color = new RGB_Color(name);
	else dynamic_cast<RGB_Color*>(color)->setRGB(name);
}

void copyColor(Color*& color, Color* copy) {
	if (color != nullptr) dealocate(color);
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

