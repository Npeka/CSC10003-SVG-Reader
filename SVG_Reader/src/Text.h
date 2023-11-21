#ifndef TEXT_H
#define TEXT_H
#include "Figure.h"

class Text : public Figure {
private:
	float x;
	float y;
	float font_size;
	string font_weight;
	string font_family;
	string text_anchor;
	string data;
	sf::Font font;
	sf::Text text;
public:
	// Constructor
	Text();

	// Set attribute
	void setX(const string& x);
	void setY(const string& y);
	void setFontSize(const string& font_size);
	void setFontWeight(const string& font_weight);
	void setFontFamily(const string& font_family);
	void setTextAnchor(const string& text_anchor);
	void setData(const string& data);

	// Virtual method
	void setAttribute(const string& attribute, const string& value) override;
	void setSFigure() override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
	~Text() override = default;
};

#endif // !TEXT_H

