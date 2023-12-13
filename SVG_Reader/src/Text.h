#ifndef TEXT_H
#define TEXT_H

#include "Figure.h"

class Text : public Figure {
protected:
	float x;
	float y;
	float dx;
	float dy;
	float font_size;
	std::string text_anchor;
	std::string font_family;
	std::string font_style;
	std::string data;
	const static std::string font[];
public:
	// Constructor
	Text();
	Text(const Text& text);

	// Set attribute
	void setX(const std::string& x);
	void setY(const std::string& y);
	void setTextAnchor(const std::string& text_anchor);
	void setFontSize(const std::string& font_size);
	void setFontFamily(const std::string& font_family);
	void setFontStyle(const std::string& font_style);
	void setData(const std::string& data);
	void setChangePositionDx(const std::string& dx);
	void setChangePositionDy(const std::string& dy);

	// Virtual method
	void setAttributes(const std::string& attribute, const std::string& value) override;
	~Text() override = default;
};

#endif // !TEXT_H

