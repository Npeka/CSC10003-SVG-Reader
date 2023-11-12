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
	string line(data);
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
void Text::setAttribute(const string& attribute, const string& value) {
	if (attribute == "|") setData(value);
	else if (attribute == "x") setX(value);
	else if (attribute == "y") setY(value);
	else if (attribute == "font-family") setFontFamily(value);
	else if (attribute == "font-size") setFontSize(value);
	else if (attribute == "text-anchor") setTextAnchor(value);
}

void Text::draw(sf::RenderWindow& window, sf::Transform& transform) {
	sf::Font font;
	if (!font.loadFromFile(string("SFML/font-family/" + font_family + ".ttf"))) exit(1);
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(font_size);
	text.setPosition(x, y - font_size);
	text.setFillColor(fill.sfColor());
	text.setString(data);
	window.draw(text, transform);
}
