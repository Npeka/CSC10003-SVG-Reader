#ifndef RGB_H
#define RGB_H

#include "Color.h"

class RGB_Color : public Color {
private:
	static std::unordered_map<string, RGB_Color> rgb_map;

public:
	// Attribute
	float r;
	float g;
	float b;

	// Constructor
	RGB_Color();
	RGB_Color(string& color);
	RGB_Color(const RGB_Color& color);
	RGB_Color(const float& r, const float& g, const float& b, const float& a = 255);

	// Set attribute
	void setRGB(string& color);
	void setRGB(const float& r, const float& g, const float& b, const float& a = 255);
	void balance();

	RGB_Color& operator=(const RGB_Color& color);
};

#endif // !RGB_H

