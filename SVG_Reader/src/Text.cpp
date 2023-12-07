#include "Text.h"

const std::string Text::font[] = {
	"arial.ttf",
	"OpenSans-Bold.ttf",
	"OpenSans-Boldltalic.ttf",
	"OpenSans-ExtraBold.ttf",
	"OpenSans-ExtraBoldltalic.ttf",
	"OpenSans-Italic.ttf",
	"OpenSans-Light.ttf",
	"OpenSans-Lightltalic.ttf",
	"OpenSans-Regular.ttf",
	"OpenSans-Semibold.ttf",
	"OpenSans-SemiboldItalic.ttf",
	"times-new-roman.ttf"
};

Text::Text() {
	x = 0;
	y = 0;
	dx = 0;
	dy = 0;
	font_family = "Times New Roman";
	font_size = 16;
	font_style = "regular";
	data = "";
}

Text::Text(const Text& text) : Figure(text) {
	x = text.x;
	y = text.y;
	font_family = text.font_family;
	font_size = text.font_size;
	font_style = text.font_style;
	data = text.data;
}

// Set attribute
void Text::setX(const std::string& x) {
	check_exception("text", "x", this->x = stof(x));
}

void Text::setY(const std::string& y) {
	check_exception("text", "y", this->y = stof(y));
}

void Text::setChangePositionDx(const std::string& dx) {
	check_exception("text", "dx", this->dx = stof(dx));
	this->x += this->dx;
}

void Text::setChangePositionDy(const std::string& dy) {
	check_exception("text", "dy", this->dy = stof(dy));
	this->y += this->dy;
}


void Text::setFontSize(const std::string& font_size) {
	check_exception("text", "font-size", this->font_size = stof(font_size));
}

void Text::setFontStyle(const std::string& font_style) {
	this->font_style = font_style;
}

void Text::setFontFamily(const std::string& font_family) {
	for (int i = 0; i < font->length(); ++i) {
		if (font_family == font[i]) {
			this->font_family = font_family;
		}
	}
	return;
}

void Text::setTextAnchor(const std::string& text_anchor) {
	this->text_anchor = text_anchor;
}

void Text::setData(const std::string& data) {
	std::string line(data);
	int i = 0;
	while (i < line.size()) {
		if (line[i] == ' ' && line[i + 1] == ' ')
			line.erase(i, 1);
		else ++i;
	}
	if (line[0] == ' ') line.erase(0, 1);
	this->data = line;
}

// Virtual method
void Text::setAttribute(const std::string& attribute, const std::string& value) {
	if (attribute == "|") setData(value);
	else if (attribute == "x") setX(value);
	else if (attribute == "y") setY(value);
	else if (attribute == "dx") setChangePositionDx(value);
	else if (attribute == "dy") setChangePositionDy(value);
	else if (attribute == "font-family") setFontFamily(value);
	else if (attribute == "font-size") setFontSize(value);
	else if (attribute == "font-style") setFontStyle(value);
	else if (attribute == "text-anchor") setTextAnchor(value);
}