#ifndef TEXT_H
#define TEXT_H

#include "Figure.h"

class Text : public Figure {
protected:
	float x;
	float y;
	float font_size;
	std::string font_weight;
	std::string font_family;
	std::string data;
	const static std::string font[];
public:
	// Constructor
	Text();
	Text(const Text& text);

	// Set attribute
	void setX(const std::string& x);
	void setY(const std::string& y);
	void setFontSize(const std::string& font_size);
	void setFontWeight(const std::string& font_weight);
	void setFontFamily(const std::string& font_family);
	void setData(const std::string& data);

	// Virtual method
	void setAttribute(const std::string& attribute, const std::string& value) override;
	~Text() override = default;
};

#endif // !TEXT_H

