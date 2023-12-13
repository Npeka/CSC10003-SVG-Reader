#include "Color.h"

// Constructor
Color::Color() {
	r = g = b = 0;
	a = 255;
}

Color::Color(const std::string& color) {
	setRGB(color);
}

Color::Color(const Color& color) {
    *this = color;
}

Color::Color(const float& r, const float& g, const float& b, const float& a) {
	this->r = r; 
	this->g = g;
	this->b = b;
	this->a = a;
}

// Set attribute
void Color::setA(const std::string& a) {
    if (this->a) check_exception("color", "a", this->a = stof(a) * 255);
}
void Color::setA(const float& a) {
    if (this->a) this->a = a * 255;
}

void Color::setRGB(const std::string& color) {
    std::string Color(color);
    for (int i = 0; i < Color.size(); i++) {
        if (Color[i] == ' ') {
            Color.erase(i, 1);
            i--;
        }
    }

    if (a == 0) a = 255;
    if (Color == "none") {
        a = 0;
    }
	else if (color.find("rgb") != std::string::npos) {
		std::string rgb(Color);
		for (char& c : rgb) if (!isdigit(c)) c = ' ';
		std::stringstream ss(rgb); ss >> r >> g >> b;
	}
    else if (Color[0] == '#') {
        if (Color.size() < 7) {
            Color.insert(2, 1, Color[1]);
            Color.insert(4, 1, Color[3]);
            Color.insert(6, 1, Color[5]);
        }
        check_exception("color #6", "r", r = stoi(Color.substr(1, 2), NULL, 16));
        check_exception("color #6", "g", g = stoi(Color.substr(3, 2), NULL, 16));
        check_exception("color #6", "b", b = stoi(Color.substr(5, 2), NULL, 16));
	}
    else {
        int saveA = a;
        auto it = mapColor.find(Color);
        if (it != mapColor.end())
            *this = it->second;
        if (a == 255) a = saveA;
	}
}

void Color::setRGB(const float& r, const float& g, const float& b, const float& a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color& Color::operator=(const Color& color) {
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
    return *this;
}

std::unordered_map<std::string, Color> Color::mapColor {
    {"CYAN", Color(0.f, 255.f, 255.f)},
    {"aliceBlue", Color(0.941176f * 255.0f, 0.972549f * 255.0f, 1.0f * 255.0f)},
    {"aliceblue", Color(240.f, 248.f, 255.f)},
    {"antiqueWhite", Color(0.980392f * 255.0f, 0.921569f * 255.0f, 0.843137f * 255.0f)},
    {"antiquewhite", Color(250.f, 235.f, 215.f)},
    {"aqua", Color(0.f, 255.f, 255.f)},
    {"aquamarine", Color(127.f, 255.f, 212.f)},
    {"azure", Color(240.f, 255.f, 255.f)},
    {"beige", Color(245.f, 245.f, 220.f)},
    {"bisque", Color(255.f, 228.f, 196.f)},
    {"black", Color(0.f, 0.f, 0.f)},
    {"blanchedAlmond", Color(1.0f * 255.0f, 0.921569f * 255.0f, 0.803922f * 255.0f)},
    {"blanchedalmond", Color(255.f, 235.f, 205.f)},
    {"blue", Color(0.f, 0.f, 255.f)},
    {"blueSteel", Color(0.27451f * 255.0f, 0.509804f * 255.0f, 0.705882f * 255.0f)},
    {"blueViolet", Color(0.541176f * 255.0f, 0.168627f * 255.0f, 0.886275f * 255.0f)},
    {"blueviolet", Color(138.f, 43.f, 226.f)},
    {"brown", Color(165.f, 42.f, 42.f)},
    {"burlyWood", Color(0.870588f * 255.0f, 0.721569f * 255.0f, 0.529412f * 255.0f)},
    {"burlywood", Color(222.f, 184.f, 135.f)},
    {"cadetBlue", Color(0.372549f * 255.0f, 0.619608f * 255.0f, 0.627451f * 255.0f)},
    {"cadetblue", Color(95.f, 158.f, 160.f)},
    {"chartreuse", Color(127.f, 255.f, 0.f)},
    {"chocolate", Color(210.f, 105.f, 30.f)},
    {"coral", Color(255.f, 127.f, 80.f)},
    {"cornflowerBlue", Color(0.392157f * 255.0f, 0.584314f * 255.0f, 0.929412f * 255.0f)},
    {"cornflowerblue", Color(100.f, 149.f, 237.f)},
    {"cornsilk", Color(255.f, 248.f, 220.f)},
    {"crimson", Color(220.f, 20.f, 60.f)},
    {"cyan", Color(0.f, 255.f, 255.f)},
    {"darkBlue", Color(0.0f, 0.0f, 0.545098f * 255.0f)},
    {"darkCyan", Color(0.0f, 0.545098f * 255.0f, 0.545098f * 255.0f)},
    {"darkGoldenRod", Color(0.721569 * 255.0f, 0.52549 * 255.0f, 0.0431373 * 255.0f)},
    {"darkGray", Color(0.662745 * 255.0f, 0.662745 * 255.0f, 0.662745 * 255.0f)},
    {"darkGreen", Color(0 * 255.0f, 0.392157 * 255.0f, 0 * 255.0f)},
    {"darkGrey", Color(0.662745 * 255.0f, 0.662745 * 255.0f, 0.662745 * 255.0f)},
    {"darkKhaki", Color(0.741176 * 255.0f, 0.717647 * 255.0f, 0.419608 * 255.0f)},
    {"darkMagenta", Color(0.545098 * 255.0f, 0 * 255.0f, 0.545098 * 255.0f)},
    {"darkOliveGreen", Color(0.333333 * 255.0f, 0.419608 * 255.0f, 0.184314 * 255.0f)},
    {"darkOrange", Color(1 * 255.0f, 0.54902 * 255.0f, 0 * 255.0f)},
    {"darkOrchid", Color(0.6 * 255.0f, 0.196078 * 255.0f, 0.8 * 255.0f)},
    {"darkRed", Color(0.545098 * 255.0f, 0 * 255.0f, 0 * 255.0f)},
    {"darkSalmon", Color(0.913725 * 255.0f, 0.588235 * 255.0f, 0.478431 * 255.0f)},
    {"darkSeaGreen", Color(0.560784 * 255.0f, 0.737255 * 255.0f, 0.560784 * 255.0f)},
    {"darkSlateBlue", Color(0.282353 * 255.0f, 0.239216 * 255.0f, 0.545098 * 255.0f)},
    {"darkSlateGray", Color(0.184314 * 255.0f, 0.309804 * 255.0f, 0.309804 * 255.0f)},
    {"darkSlateGrey", Color(0.184314 * 255.0f, 0.309804 * 255.0f, 0.309804 * 255.0f)},
    {"darkTurquoise", Color(0 * 255.0f, 0.807843 * 255.0f, 0.819608 * 255.0f)},
    {"darkViolet", Color(0.580392 * 255.0f, 0 * 255.0f, 0.827451 * 255.0f)},
    {"darkblue", Color(0.f, 0.f, 139.f)},
    {"darkcyan", Color(0.f, 139.f, 139.f)},
    {"darkgoldenrod", Color(184.f, 134.f, 11.f)},
    {"darkgray", Color(169.f, 169.f, 169.f)},
    {"darkgreen", Color(0.f, 100.f, 0.f)},
    {"darkkhaki", Color(189.f, 183.f, 107.f)},
    {"darkmagenta", Color(139.f, 0.f, 139.f)},
    {"darkolivegreen", Color(85.f, 107.f, 47.f)},
    {"darkorange", Color(255.f, 140.f, 0.f)},
    {"darkorchid", Color(153.f, 50.f, 204.f)},
    {"darkred", Color(139.f, 0.f, 0.f)},
    {"darksalmon", Color(233.f, 150.f, 122.f)},
    {"darkseagreen", Color(143.f, 188.f, 143.f)},
    {"darkslateblue", Color(72.f, 61.f, 139.f)},
    {"darkslategray", Color(47.f, 79.f, 79.f)},
    {"darkturquoise", Color(0.f, 206.f, 209.f)},
    {"darkviolet", Color(148.f, 0.f, 211.f)},
    {"deepPink", Color(1 * 255.0f, 0.0784314 * 255.0f, 0.576471 * 255.0f)},
    {"deepSkyBlue", Color(0 * 255.0f, 0.74902 * 255.0f, 1 * 255.0f)},
    {"deeppink", Color(255.f, 20.f, 147.f)},
    {"deepskyblue", Color(0.f, 191.f, 255.f)},
    {"dimGray", Color(0.411765 * 255.0f, 0.411765 * 255.0f, 0.411765 * 255.0f)},
    {"dimGrey", Color(0.411765 * 255.0f, 0.411765 * 255.0f, 0.411765 * 255.0f)},
    {"dimgray", Color(105.f, 105.f, 105.f)},
    {"dodgerBlue", Color(0.117647 * 255.0f, 0.564706 * 255.0f, 1 * 255.0f)},
    {"dodgerblue", Color(30.f, 144.f, 255.f)},
    {"fireBrick", Color(0.698039 * 255.0f, 0.133333 * 255.0f, 0.133333 * 255.0f)},
    {"firebrick", Color(178.f, 34.f, 34.f)},
    {"floralWhite", Color(1 * 255.0f, 0.980392 * 255.0f, 0.941176 * 255.0f)},
    {"floralwhite", Color(255.f, 250.f, 240.f)},
    {"forestGreen", Color(0.133333 * 255.0f, 0.545098 * 255.0f, 0.133333 * 255.0f)},
    {"forestgreen", Color(34.f, 139.f, 34.f)},
    {"fuchsia", Color(255.f, 0.f, 255.f)},
    {"gainsboro", Color(220.f, 220.f, 220.f)},
    {"ghostWhite", Color(0.972549 * 255.0f, 0.972549 * 255.0f, 1 * 255.0f)},
    {"ghostwhite", Color(248.f, 248.f, 255.f)},
    {"gold", Color(255.f, 215.f, 0.f)},
    {"goldenRod", Color(0.854902 * 255.0f, 0.647059 * 255.0f, 0.12549 * 255.0f)},
    {"goldenrod", Color(218.f, 165.f, 32.f)},
    {"gray", Color(128.f, 128.f, 128.f)},
    {"green", Color(0.f, 128.f, 0.f)},
    {"greenYellow", Color(0.678431 * 255.0f, 1 * 255.0f, 0.184314 * 255.0f)},
    {"greenyellow", Color(173.f, 255.f, 47.f)},
    {"grey", Color(0.501961 * 255.0f, 0.501961 * 255.0f, 0.501961 * 255.0f)},
    {"honeyDew", Color(0.941176 * 255.0f, 1 * 255.0f, 0.941176 * 255.0f)},
    {"honeydew", Color(240.f, 255.f, 240.f)},
    {"hotPink", Color(1 * 255.0f, 0.411765 * 255.0f, 0.705882 * 255.0f)},
    {"hotpink", Color(255.f, 105.f, 180.f)},
    {"indianRed", Color(0.803922 * 255.0f, 0.360784 * 255.0f, 0.360784 * 255.0f)},
    {"indianred", Color(205.f, 92.f, 92.f)},
    {"indigo", Color(75.f, 0.f, 130.f)},
    {"ivory", Color(255.f, 255.f, 240.f)},
    {"khaki", Color(240.f, 230.f, 140.f)},
    {"lavender", Color(230.f, 230.f, 250.f)},
    {"lavenderBlush", Color(1.0f * 255.0f, 0.941176f * 255.0f, 0.960784f * 255.0f)},
    {"lavenderblush", Color(255.f, 240.f, 245.f)},
    {"lawnGreen", Color(0.486275f * 255.0f, 0.988235f * 255.0f, 0.0f * 255.0f)},
    {"lawngreen", Color(124.f, 252.f, 0.f)},
    {"lemonChiffon", Color(1.0f * 255.0f, 0.980392f * 255.0f, 0.803922f * 255.0f)},
    {"lemonchiffon", Color(255.f, 250.f, 205.f)},
    {"lightBlue", Color(0.678431f * 255.0f, 0.847059f * 255.0f, 0.901961f * 255.0f)},
    {"lightCoral", Color(0.941176f * 255.0f, 0.501961f * 255.0f, 0.501961f * 255.0f)},
    {"lightCyan", Color(0.878431f * 255.0f, 1.0f * 255.0f, 1.0f * 255.0f)},
    {"lightGoldenRodYellow", Color(0.980392f * 255.0f, 0.980392f * 255.0f, 0.823529f * 255.0f)},
    {"lightGray", Color(0.827451f * 255.0f, 0.827451f * 255.0f, 0.827451f * 255.0f)},
    {"lightGreen", Color(0.564706f * 255.0f, 0.933333f * 255.0f, 0.564706f * 255.0f)},
    {"lightGrey", Color(0.827451f * 255.0f, 0.827451f * 255.0f, 0.827451f * 255.0f)},
    {"lightPink", Color(1.0f * 255.0f, 0.713726f * 255.0f, 0.756863f * 255.0f)},
    {"lightSalmon", Color(1.0f * 255.0f, 0.627451f * 255.0f, 0.478431f * 255.0f)},
    {"lightSeaGreen", Color(0.12549f * 255.0f, 0.698039f * 255.0f, 0.666667f * 255.0f)},
    {"lightSkyBlue", Color(0.529412f * 255.0f, 0.807843f * 255.0f, 0.980392f * 255.0f)},
    {"lightSlateGray", Color(0.466667f * 255.0f, 0.533333f * 255.0f, 0.6f * 255.0f)},
    {"lightSlateGrey", Color(0.466667f * 255.0f, 0.533333f * 255.0f, 0.6f * 255.0f)},
    {"lightSteelBlue", Color(0.690196f * 255.0f, 0.768627f * 255.0f, 0.870588f * 255.0f)},
    {"lightYellow", Color(1.0f * 255.0f, 1.0f * 255.0f, 0.878431f * 255.0f)},
    {"lightblue", Color(173.f, 216.f, 230.f)},
    {"lightcoral", Color(240.f, 128.f, 128.f)},
    {"lightcyan", Color(224.f, 255.f, 255.f)},
    {"lightgoldenrodyellow", Color(250.f, 250.f, 210.f)},
    {"lightgray", Color(211.f, 211.f, 211.f)},
    {"lightgreen", Color(144.f, 238.f, 144.f)},
    {"lightpink", Color(255.f, 182.f, 193.f)},
    {"lightsalmon", Color(255.f, 160.f, 122.f)},
    {"lightseagreen", Color(32.f, 178.f, 170.f)},
    {"lightskyblue", Color(135.f, 206.f, 250.f)},
    {"lightslategray", Color(119.f, 136.f, 153.f)},
    {"lightsteelblue", Color(176.f, 196.f, 222.f)},
    {"lightyellow", Color(255.f, 255.f, 224.f)},
    {"lime", Color(0.f, 255.f, 0.f)},
    {"limeGreen", Color(0.196078f * 255.0f, 0.803922f * 255.0f, 0.196078f * 255.0f)},
    {"limegreen", Color(50.f, 205.f, 50.f)},
    {"linen", Color(250.f, 240.f, 230.f)},
    {"magenta", Color(255.f, 0.f, 255.f)},
    {"maroon", Color(128.f, 0.f, 0.f)},
    {"mediumAquaMarine", Color(0.4f * 255.0f, 0.803922f * 255.0f, 0.666667f * 255.0f)},
    {"mediumBlue", Color(0.0f, 0.0f, 0.803922f * 255.0f)},
    {"mediumOrchid", Color(0.729412f * 255.0f, 0.333333f * 255.0f, 0.827451f * 255.0f)},
    {"mediumPurple", Color(0.576471f * 255.0f, 0.439216f * 255.0f, 0.858824f * 255.0f)},
    {"mediumSeaGreen", Color(0.235294f * 255.0f, 0.701961f * 255.0f, 0.443137f * 255.0f)},
    {"mediumSlateBlue", Color(0.482353f * 255.0f, 0.407843f * 255.0f, 0.933333f * 255.0f)},
    {"mediumSpringGreen", Color(0.0f, 0.980392f * 255.0f, 0.603922f * 255.0f)},
    {"mediumTurquoise", Color(0.282353f * 255.0f, 0.819608f * 255.0f, 0.8f * 255.0f)},
    {"mediumVioletRed", Color(0.780392f * 255.0f, 0.0823529f * 255.0f, 0.521569f * 255.0f)},
    {"mediumaquamarine", Color(102.f, 205.f, 170.f)},
    {"mediumblue", Color(0.f, 0.f, 205.f)},
    {"mediumorchid", Color(186.f, 85.f, 211.f)},
    {"mediumpurple", Color(147.f, 112.f, 219.f)},
    {"mediumseagreen", Color(60.f, 179.f, 113.f)},
    {"mediumslateblue", Color(123.f, 104.f, 238.f)},
    {"mediumspringgreen", Color(0.f, 250.f, 154.f)},
    {"mediumturquoise", Color(72.f, 209.f, 204.f)},
    {"mediumvioletred", Color(199.f, 21.f, 133.f)},
    {"midnightBlue", Color(0.0980392f * 255.0f, 0.0980392f * 255.0f, 0.439216f * 255.0f)},
    {"midnightblue", Color(25.f, 25.f, 112.f)},
    {"mintCream", Color(0.960784f * 255.0f, 1.0f * 255.0f, 0.980392f * 255.0f)},
    {"mintcream", Color(245.f, 255.f, 250.f)},
    {"mistyRose", Color(1.0f * 255.0f, 0.894118f * 255.0f, 0.882353f * 255.0f)},
    {"mistyrose", Color(255.f, 228.f, 225.f)},
    {"moccasin", Color(255.f, 228.f, 181.f)},
    {"navajoWhite", Color(1.0f * 255.0f, 0.870588f * 255.0f, 0.678431f * 255.0f)},
    {"navajowhite", Color(255.f, 222.f, 173.f)},
    {"navy", Color(0.f, 0.f, 128.f)},
    {"oldLace", Color(0.992157f * 255.0f, 0.960784f * 255.0f, 0.901961f * 255.0f)},
    {"oldlace", Color(253.f, 245.f, 230.f)},
    {"olive", Color(128.f, 128.f, 0.f)},
    {"oliveDrab", Color(0.419608f * 255.0f, 0.556863f * 255.0f, 0.137255f * 255.0f)},
    {"olivedrab", Color(107.f, 142.f, 35.f)},
    {"orange", Color(255.f, 165.f, 0.f)},
    {"orangeRed", Color(1.0f * 255.0f, 0.270588f * 255.0f, 0.0f * 255.0f)},
    {"orangered", Color(255.f, 69.f, 0.f)},
    {"orchid", Color(218.f, 112.f, 214.f)},
    {"paleGoldenRod", Color(0.933333f * 255.0f, 0.909804f * 255.0f, 0.666667f * 255.0f)},
    {"paleGreen", Color(0.596078f * 255.0f, 0.984314f * 255.0f, 0.596078f * 255.0f)},
    {"paleTurquoise", Color(0.686275f * 255.0f, 0.933333f * 255.0f, 0.933333f * 255.0f)},
    {"paleVioletRed", Color(0.858824f * 255.0f, 0.439216f * 255.0f, 0.576471f * 255.0f)},
    {"palegoldenrod", Color(238.f, 232.f, 170.f)},
    {"palegreen", Color(152.f, 251.f, 152.f)},
    {"paleturquoise", Color(175.f, 238.f, 238.f)},
    {"palevioletred", Color(219.f, 112.f, 147.f)},
    {"papayaWhip", Color(1.0f * 255.0f, 0.937255f * 255.0f, 0.835294f * 255.0f)},
    {"papayawhip", Color(255.f, 239.f, 213.f)},
    {"peachPuff", Color(1.0f * 255.0f, 0.854902f * 255.0f, 0.72549f * 255.0f)},
    {"peachpuff", Color(255.f, 218.f, 185.f)},
    {"peru", Color(205.f, 133.f, 63.f)},
    {"pink", Color(255.f, 192.f, 203.f)},
    {"plum", Color(221.f, 160.f, 221.f)},
    {"powderBlue", Color(0.690196f * 255.0f, 0.878431f * 255.0f, 0.901961f * 255.0f)},
    {"powderblue", Color(176.f, 224.f, 230.f)},
    {"purple", Color(128.f, 0.f, 128.f)},
    {"rebeccapurple", Color(102.f, 51.f, 153.f)},
    {"red", Color(255.f, 0.f, 0.f)},
    {"rosyBrown", Color(0.737255f * 255.0f, 0.560784f * 255.0f, 0.560784f * 255.0f)},
    {"rosybrown", Color(188.f, 143.f, 143.f)},
    {"royalBlue", Color(0.254902f * 255.0f, 0.411765f * 255.0f, 0.882353f * 255.0f)},
    {"royalblue", Color(65.f, 105.f, 225.f)},
    {"saddleBrown", Color(0.545098f * 255.0f, 0.270588f * 255.0f, 0.0745098f * 255.0f)},
    {"saddlebrown", Color(139.f, 69.f, 19.f)},
    {"salmon", Color(250.f, 128.f, 114.f)},
    {"sandyBrown", Color(0.956863f * 255.0f, 0.643137f * 255.0f, 0.376471f * 255.0f)},
    {"sandybrown", Color(244.f, 164.f, 96.f)},
    {"seaGreen", Color(0.180392f * 255.0f, 0.545098f * 255.0f, 0.341176f * 255.0f)},
    {"seaShell", Color(1.0f * 255.0f, 0.960784f * 255.0f, 0.933333f * 255.0f)},
    {"seagreen", Color(46.f, 139.f, 87.f)},
    {"seashell", Color(255.f, 245.f, 238.f)},
    {"sienna", Color(160.f, 82.f, 45.f)},
    {"silver", Color(192.f, 192.f, 192.f)},
    {"skyBlue", Color(0.529412f * 255.0f, 0.807843f * 255.0f, 0.921569f * 255.0f)},
    {"skyblue", Color(135.f, 206.f, 235.f)},
    {"slateBlue", Color(0.415686f * 255.0f, 0.352941f * 255.0f, 0.803922f * 255.0f)},
    {"slateGray", Color(0.439216f * 255.0f, 0.501961f * 255.0f, 0.564706f * 255.0f)},
    {"slateGrey", Color(0.439216f * 255.0f, 0.501961f * 255.0f, 0.564706f * 255.0f)},
    {"slateblue", Color(106.f, 90.f, 205.f)},
    {"slategray", Color(112.f, 128.f, 144.f)},
    {"snow", Color(255.f, 250.f, 250.f)},
    {"springGreen", Color(0.0f, 1.0f * 255.0f, 0.498039f * 255.0f)},
    {"springgreen", Color(0.f, 255.f, 127.f)},
    {"steelBlue", Color(0.27451f * 255.0f, 0.509804f * 255.0f, 0.705882f * 255.0f)},
    {"steelblue", Color(70.f, 130.f, 180.f)},
    {"teal", Color(0.f, 128.f, 128.f)},
    {"thistle", Color(216.f, 191.f, 216.f)},
    {"tomato", Color(255.f, 99.f, 71.f)},
    {"turquoise", Color(64.f, 224.f, 208.f)},
    {"violet", Color(238.f, 130.f, 238.f)},
    {"wheat", Color(245.f, 222.f, 179.f)},
    {"white", Color(255.f, 255.f, 255.f)},
    {"whiteSmoke", Color(0.960784f * 255.0f, 0.960784f * 255.0f, 0.960784f * 255.0f)},
    {"whitesmoke", Color(245.f, 245.f, 245.f)},
    {"yellow", Color(255.f, 255.f, 0.f)},
    {"yellowGreen", Color(0.603922f * 255.0f, 0.803922f * 255.0f, 0.196078f * 255.0f)},
    {"yellowgreen", Color(154.f, 205.f, 50.f)},
};