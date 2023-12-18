#ifndef COLOR_H
#define COLOR_H

#include "SVG_Element.h"

class Color : public SVG_Element {
public:
	float opacity;

public:
	Color();
	Color(const Color& other);
	void setOpacity(string& opacity);
	void setOpacity(const float& opacity);
	void setElementAttributes(const string& attribute, string& value) override {};
};

void createColor(Color*& color, string name = "");
void copyColor(Color*& color, Color* copy);

#endif // !COLOR_H