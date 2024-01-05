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

void createColor(Color*& color, string name, const Defs_Type* defs) {
	auto it = findGlobalElement(name, defs);
	if (it != nullptr) {
		copyColor(color, dynamic_cast<Color*>(it));
	}
	else if (color == nullptr) {
		color = new RGB_Color(name);
	}
	else dynamic_cast<RGB_Color*>(color)->setRGB(name);
}

void copyColor(Color*& color, Color* copy) {
	dealocate(color);
	if (auto it = dynamic_cast<RGB_Color*>(copy)) {
		color = new RGB_Color(*it);
	} 
	else if (auto it = dynamic_cast<LinearGradient*>(copy)) {
		color = new LinearGradient(*it);
	}
	else if (auto it = dynamic_cast<RadialGradient*>(copy)) {
		color = new RadialGradient(*it);
	}
}

