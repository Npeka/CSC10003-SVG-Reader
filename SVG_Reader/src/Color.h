#ifndef COLOR_H
#define COLOR_H
#include "Header.h"

class Color {
public:
	float r;
	float g;
	float b;
	float a;
public:
	// Constructor
	Color();
	Color(const string& color);
	Color(const Color& color);
	Color(const float& r, const float& g, const float& b , const float& a = 255);

	// Set attribute
	void setA(const string& a);
	void setA(const float& a);
	void setRGB(const string& color);
	void setRGB(const float& r, const float& g, const float& b, const float& a = 255);
	Color& operator=(const Color& color);
	sf::Color sfColor();
};

const Color& setColorByName(const string& color);

extern const Color white, gray, black, red, green, blue, cyan, magenta,
yellow, aliceBlue, antiqueWhite, aqua, aquamarine, azure, beige, bisque, blanchedAlmond,
blueViolet, brown, burlyWood, cadetBlue, chartreuse, chocolate, coral, cornflowerBlue, cornsilk,
crimson, darkBlue, darkCyan, darkGoldenRod, darkGray, darkGrey, darkGreen, darkKhaki,
darkMagenta, darkOliveGreen, darkOrange, darkOrchid, darkRed, darkSalmon, darkSeaGreen,
darkSlateBlue, darkSlateGray, darkSlateGrey, darkTurquoise, darkViolet, deepPink,
deepSkyBlue, dimGray, dimGrey, dodgerBlue, fireBrick, floralWhite, forestGreen, fuchsia,
gainsboro, ghostWhite, gold, goldenRod, grey, greenYellow, honeyDew, hotPink, indianRed, indigo,
ivory, khaki, lavender, lavenderBlush, lawnGreen, lemonChiffon, lightBlue, lightCoral,
lightCyan, lightGoldenRodYellow, lightGray, lightGrey, lightGreen, lightPink, lightSalmon,
lightSeaGreen, lightSkyBlue, lightSlateGray, lightSlateGrey, lightSteelBlue, lightYellow,
lime, limeGreen, linen, maroon, mediumAquaMarine, mediumBlue, mediumOrchid, mediumPurple,
mediumSeaGreen, mediumSlateBlue, mediumSpringGreen, mediumTurquoise, mediumVioletRed,
midnightBlue, mintCream, mistyRose, moccasin, navajoWhite, navy, oldLace, olive, oliveDrab,
orange, orangeRed, orchid, paleGoldenRod, paleGreen, paleTurquoise, paleVioletRed, papayaWhip,
peachPuff, peru, pink, plum, powderBlue, purple, rosyBrown, royalBlue, saddleBrown, salmon,
sandyBrown, seaGreen, seaShell, sienna, silver, skyBlue, slateBlue, slateGray, slateGrey, snow,
springGreen, steelBlue, blueSteel, teal, thistle, tomato, turquoise, violet, wheat, whiteSmoke,
yellowGreen;

#endif // !COLOR_H