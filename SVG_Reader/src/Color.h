#ifndef COLOR_H
#define COLOR_H

#include "Header.h"

class Color {
public:
	// Attribute
	float r;
	float g;
	float b;
	float a;

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
};

const Color& setColorByName(const string& color);

extern const Color aliceblue, antiquewhite, aqua, aquamarine,
azure, beige, bisque, black, blanchedalmond, blue, blueviolet,
brown, burlywood, cadetblue, chartreuse, chocolate, coral,
cornflowerblue, cornsilk, crimson, cyan, darkblue, darkcyan,
darkgoldenrod, darkgray, darkgreen, darkkhaki, darkmagenta,
darkolivegreen, darkorange, darkorchid, darkred, darksalmon,
darkseagreen, darkslateblue, darkslategray, darkturquoise,
darkviolet, deeppink, deepskyblue, dimgray, dodgerblue, 
firebrick, floralwhite, forestgreen, fuchsia, gainsboro, 
ghostwhite, gold,  goldenrod, gray, green, greenyellow, 
honeydew, hotpink, indianred,  indigo, ivory, khaki, lavender, 
lavenderblush,lawngreen, lemonchiffon, lightblue, lightcoral, 
lightcyan, lightgoldenrodyellow, lightgray, lightgreen, lightpink, 
lightsalmon, lightseagreen, lightskyblue, lightslategray, 
lightsteelblue, lightyellow, lime, limegreen, linen, magenta, 
maroon, mediumaquamarine, mediumblue, mediumorchid, mediumpurple, 
mediumseagreen, mediumslateblue, mediumspringgreen, mediumturquoise, 
mediumvioletred, midnightblue, mintcream, mistyrose, moccasin,
navajowhite, navy, oldlace, olive, olivedrab, orange, orangered, 
orchid, palegoldenrod, palegreen, paleturquoise, palevioletred, 
papayawhip, peachpuff, peru, pink, plum, powderblue, purple, 
rebeccapurple, red, rosybrown, royalblue, saddlebrown, salmon, 
sandybrown, seagreen, seashell, sienna, silver, skyblue, slateblue, 
slategray, snow, springgreen, steelblue, teal, thistle, tomato,
turquoise, violet, wheat, white, whitesmoke, yellow, yellowgreen, 
CYAN, aliceBlue, antiqueWhite, azure, blanchedAlmond, blueViolet, 
brown, burlyWood, cadetBlue, cornflowerBlue, crimson, darkBlue, 
darkCyan, darkGoldenRod, darkGray, darkGrey, darkGreen, darkKhaki,
darkMagenta, darkOliveGreen, darkOrange, darkOrchid, darkRed, 
darkSalmon, darkSeaGreen, darkSlateBlue, darkSlateGray, darkSlateGrey, 
darkTurquoise, darkViolet, deepPink, deepSkyBlue, dimGray, dimGrey, 
dodgerBlue, fireBrick, floralWhite, forestGreen, gainsboro, ghostWhite, 
goldenRod, grey, greenYellow, honeyDew, hotPink, indianRed, ivory, 
lavenderBlush, lawnGreen, lemonChiffon, lightBlue, lightCoral, lightCyan, 
lightGoldenRodYellow, lightGray, lightGrey, lightGreen, lightPink, 
lightSalmon,lightSeaGreen, lightSkyBlue, lightSlateGray, lightSlateGrey, 
lightSteelBlue, lightYellow, limeGreen, mediumAquaMarine, mediumBlue,
mediumOrchid, mediumPurple, mediumSeaGreen, mediumSlateBlue, mediumSpringGreen,
mediumTurquoise, mediumVioletRed, midnightBlue, mintCream, mistyRose, 
navajoWhite, oldLace, oliveDrab, orange, orangeRed, paleGoldenRod, 
paleGreen, paleTurquoise, paleVioletRed, papayaWhip, peachPuff, peru, 
powderBlue, rosyBrown, royalBlue, saddleBrown, sandyBrown, seaGreen, 
seaShell, silver, skyBlue, slateBlue, slateGray, slateGrey, springGreen, 
steelBlue, blueSteel, teal, whiteSmoke, yellowGreen;

#endif // !COLOR_H