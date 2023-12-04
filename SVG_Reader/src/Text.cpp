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
	font_family = "Times New Roman";
	font_size = 16;
	font_weight = "";
	data = "";
}

Text::Text(const Text& text) : Figure(text) {
	x = text.x;
	y = text.y;
	font_family = text.font_family;
	font_size = text.font_size;
	font_weight = text.font_weight;
	data = text.data;
}

// Set attribute
void Text::setX(const std::string& x) {
	check_exception("text", "x", this->x = stof(x));
}

void Text::setY(const std::string& y) {
	check_exception("text", "y", this->y = stof(y));
}

void Text::setFontSize(const std::string& font_size) {
	check_exception("text", "font-size", this->font_size = stof(font_size));
}

void Text::setFontWeight(const std::string& font_weight) {
	this->font_weight = font_weight;
}

void Text::setFontFamily(const std::string& font_family) {
	for (int i = 0; i < font->length(); ++i) {
		if (font_family == font[i]) {
			this->font_family = font_family;
		}
	}
	return;
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
	else if (attribute == "font-family") setFontFamily(value);
	else if (attribute == "font-size") setFontSize(value);
}