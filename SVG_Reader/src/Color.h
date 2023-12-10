#ifndef COLOR_H
#define COLOR_H

#include "Header.h"

class Color {
private:
	static std::unordered_map<std::string, Color> mapColor;
public:
	// Attribute
	float r;
	float g;
	float b;
	float a;

	// Constructor
	Color();
	Color(const std::string& color);
	Color(const Color& color);
	Color(const float& r, const float& g, const float& b , const float& a = 255);

	// Set attribute
	void setA(const std::string& a);
	void setA(const float& a);
	void setRGB(const std::string& color);
	void setRGB(const float& r, const float& g, const float& b, const float& a = 255);
	Color& operator=(const Color& color);
};

#endif // !COLOR_H