#ifndef TEXT_H
#define TEXT_H

#include "Figure.h"

class Text : public Figure {
protected:
	float x;
	float y;
	float font_size;
	string font_weight;
	string font_family;
	string data;
public:
	// Constructor
	Text();
	Text(const Text& text);

	// Set attribute
	void setX(const string& x);
	void setY(const string& y);
	void setFontSize(const string& font_size);
	void setFontWeight(const string& font_weight);
	void setFontFamily(const string& font_family);
	void setData(const string& data);

	// Virtual method
	void setAttribute(const string& attribute, const string& value) override;
	~Text() override = default;
};

#endif // !TEXT_H

