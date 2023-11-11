#include "Text.h"

// Constructor
Text::Text() {
	x = 0;
	y = 0;
	font_family = "times-new-roman";
	font_size = 0;
	font_weight = "";
	text_anchor = "start";
	data = "";
}

// Set attribute
void Text::setX(const string& x) {
	this->x = stoi(x);
}

void Text::setY(const string& y) {
	this->y = stoi(y);
}

void Text::setFontSize(const string& font_size) {
	this->font_size = stoi(font_size);
}

void Text::setFontWeight(const string& font_weight) {
	this->font_weight = font_weight;
}
void Text::setFontFamily(const string& font_family) {
	this->font_family = font_family;
}

void Text::setTextAnchor(const string& text_anchor) {
	this->text_anchor = text_anchor;
}

void Text::setData(const string& data) {
	this->data = line;
}

// Virtual method
void Text::setAttribute(const string& attribute, const string& value) {
	
}

void Text::draw(sf::RenderWindow& window, sf::Transform& transform) {
	
}
