#include "Text.h"

Text::Text() :
	x(0), y(0),
	dx(0), dy(0),
	font_size(16),
	text_anchor(""),
	font_family("Times New Roman"),
	font_style("regular"),
	data("")
{}

// Set attribute
void Text::setX(string& x) {
	check_exception("text", "x", this->x = stof(x));
}

void Text::setY(string& y) {
	check_exception("text", "y", this->y = stof(y));
}

void Text::setDx(string& dx) {
	check_exception("text", "dx", this->dx = stof(dx));
}

void Text::setDy(string& dy) {
	check_exception("text", "dy", this->dy = stof(dy));
}

void Text::setFontSize(string& font_size) {
	check_exception("text", "font-size", this->font_size = stof(font_size));
}

void Text::setTextAnchor(string& text_anchor) {
	this->text_anchor = text_anchor;
}

void Text::setFontFamily(string& font_family) {
	auto pos = font_family.find(',');
	if (pos != std::string::npos) {
		this->font_family = font_family.substr(0, pos);
		return;
	}
	this->font_family = font_family;
}

void Text::setFontStyle(string& font_style) {
	this->font_style = font_style;
}

void Text::setData(string& data) {
	int i = 0;
	while (i < data.size()) {
		if (data[i] == ' ' && data[i + 1] == ' ')
			data.erase(i, 1);
		else ++i;
	}
	if (data[0] == ' ') data.erase(0, 1);
	this->data = data;
}

// Virtual method
void Text::setFigureAttributes(const string& attribute, string& value) {
	if (attribute == "|") setData(value);
	else if (attribute == "x") setX(value);
	else if (attribute == "y") setY(value);
	else if (attribute == "dx") setDx(value);
	else if (attribute == "dy") setDy(value);
	else if (attribute == "font-size") setFontSize(value);
	else if (attribute == "font-family") setFontFamily(value);
	else if (attribute == "font-style") setFontStyle(value);
	else if (attribute == "text-anchor") setTextAnchor(value);
}