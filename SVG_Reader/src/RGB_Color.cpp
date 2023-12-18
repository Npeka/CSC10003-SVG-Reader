#include "RGB_Color.h"

// Constructor
RGB_Color::RGB_Color() :
    r(0), g(0), b(0)
{}

RGB_Color::RGB_Color(string& color) {
    setRGB(color);
}

RGB_Color::RGB_Color(const RGB_Color& color) {
    *this = color;
    balance();
}

RGB_Color::RGB_Color(const float& r, const float& g, const float& b, const float& a) {
    this->r = r;
    this->g = g;
    this->b = b;
    opacity = a;
    balance();
}

// Set attribute

void RGB_Color::setRGB(string& color) {
    for (int i = 0; i < color.size(); i++) {
        if (color[i] == ' ') {
            color.erase(i, 1);
            i--;
        }
    }

    if (opacity == 0) opacity = 255;
    if (color == "none") {
        opacity = 0;
    }
    else if (color.find("rgb") != string::npos) {
        for (char& c : color) if (!isdigit(c)) c = ' ';
        std::stringstream ss(color); ss >> r >> g >> b;
    }
    else if (color[0] == '#') {
        if (color.size() < 7) {
            color.insert(2, 1, color[1]);
            color.insert(4, 1, color[3]);
            color.insert(6, 1, color[5]);
        }
        check_exception("RGB_Hex #6", "r", r = stoi(color.substr(1, 2), NULL, 16));
        check_exception("RGB_Hex #6", "g", g = stoi(color.substr(3, 2), NULL, 16));
        check_exception("RGB_Hex #6", "b", b = stoi(color.substr(5, 2), NULL, 16));
    }
    else {
        int saveA = opacity;
        auto it = rgb_map.find(color);
        if (it != rgb_map.end())
            *this = it->second;
        if (opacity == 255) opacity = saveA;
    }
    balance();
}

void RGB_Color::setRGB(const float& r, const float& g, const float& b, const float& a) {
    this->r = r;
    this->g = g;
    this->b = b;
    opacity = a;
    balance();
}

void RGB_Color::balance() {
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;
}

RGB_Color& RGB_Color::operator=(const RGB_Color& color) {
    r = color.r;
    g = color.g;
    b = color.b;
    opacity = color.opacity;
    return *this;
}

std::unordered_map<std::string, RGB_Color> RGB_Color::rgb_map {
    {"CYAN", RGB_Color(0.f, 255.f, 255.f)},
    {"aliceBlue", RGB_Color(0.941176f * 255.0f, 0.972549f * 255.0f, 1.0f * 255.0f)},
    {"aliceblue", RGB_Color(240.f, 248.f, 255.f)},
    {"antiqueWhite", RGB_Color(0.980392f * 255.0f, 0.921569f * 255.0f, 0.843137f * 255.0f)},
    {"antiquewhite", RGB_Color(250.f, 235.f, 215.f)},
    {"aqua", RGB_Color(0.f, 255.f, 255.f)},
    {"aquamarine", RGB_Color(127.f, 255.f, 212.f)},
    {"azure", RGB_Color(240.f, 255.f, 255.f)},
    {"beige", RGB_Color(245.f, 245.f, 220.f)},
    {"bisque", RGB_Color(255.f, 228.f, 196.f)},
    {"black", RGB_Color(0.f, 0.f, 0.f)},
    {"blanchedAlmond", RGB_Color(1.0f * 255.0f, 0.921569f * 255.0f, 0.803922f * 255.0f)},
    {"blanchedalmond", RGB_Color(255.f, 235.f, 205.f)},
    {"blue", RGB_Color(0.f, 0.f, 255.f)},
    {"blueSteel", RGB_Color(0.27451f * 255.0f, 0.509804f * 255.0f, 0.705882f * 255.0f)},
    {"blueViolet", RGB_Color(0.541176f * 255.0f, 0.168627f * 255.0f, 0.886275f * 255.0f)},
    {"blueviolet", RGB_Color(138.f, 43.f, 226.f)},
    {"brown", RGB_Color(165.f, 42.f, 42.f)},
    {"burlyWood", RGB_Color(0.870588f * 255.0f, 0.721569f * 255.0f, 0.529412f * 255.0f)},
    {"burlywood", RGB_Color(222.f, 184.f, 135.f)},
    {"cadetBlue", RGB_Color(0.372549f * 255.0f, 0.619608f * 255.0f, 0.627451f * 255.0f)},
    {"cadetblue", RGB_Color(95.f, 158.f, 160.f)},
    {"chartreuse", RGB_Color(127.f, 255.f, 0.f)},
    {"chocolate", RGB_Color(210.f, 105.f, 30.f)},
    {"coral", RGB_Color(255.f, 127.f, 80.f)},
    {"cornflowerBlue", RGB_Color(0.392157f * 255.0f, 0.584314f * 255.0f, 0.929412f * 255.0f)},
    {"cornflowerblue", RGB_Color(100.f, 149.f, 237.f)},
    {"cornsilk", RGB_Color(255.f, 248.f, 220.f)},
    {"crimson", RGB_Color(220.f, 20.f, 60.f)},
    {"cyan", RGB_Color(0.f, 255.f, 255.f)},
    {"darkBlue", RGB_Color(0.0f, 0.0f, 0.545098f * 255.0f)},
    {"darkCyan", RGB_Color(0.0f, 0.545098f * 255.0f, 0.545098f * 255.0f)},
    {"darkGoldenRod", RGB_Color(0.721569 * 255.0f, 0.52549 * 255.0f, 0.0431373 * 255.0f)},
    {"darkGray", RGB_Color(0.662745 * 255.0f, 0.662745 * 255.0f, 0.662745 * 255.0f)},
    {"darkGreen", RGB_Color(0 * 255.0f, 0.392157 * 255.0f, 0 * 255.0f)},
    {"darkGrey", RGB_Color(0.662745 * 255.0f, 0.662745 * 255.0f, 0.662745 * 255.0f)},
    {"darkKhaki", RGB_Color(0.741176 * 255.0f, 0.717647 * 255.0f, 0.419608 * 255.0f)},
    {"darkMagenta", RGB_Color(0.545098 * 255.0f, 0 * 255.0f, 0.545098 * 255.0f)},
    {"darkOliveGreen", RGB_Color(0.333333 * 255.0f, 0.419608 * 255.0f, 0.184314 * 255.0f)},
    {"darkOrange", RGB_Color(1 * 255.0f, 0.54902 * 255.0f, 0 * 255.0f)},
    {"darkOrchid", RGB_Color(0.6 * 255.0f, 0.196078 * 255.0f, 0.8 * 255.0f)},
    {"darkRed", RGB_Color(0.545098 * 255.0f, 0 * 255.0f, 0 * 255.0f)},
    {"darkSalmon", RGB_Color(0.913725 * 255.0f, 0.588235 * 255.0f, 0.478431 * 255.0f)},
    {"darkSeaGreen", RGB_Color(0.560784 * 255.0f, 0.737255 * 255.0f, 0.560784 * 255.0f)},
    {"darkSlateBlue", RGB_Color(0.282353 * 255.0f, 0.239216 * 255.0f, 0.545098 * 255.0f)},
    {"darkSlateGray", RGB_Color(0.184314 * 255.0f, 0.309804 * 255.0f, 0.309804 * 255.0f)},
    {"darkSlateGrey", RGB_Color(0.184314 * 255.0f, 0.309804 * 255.0f, 0.309804 * 255.0f)},
    {"darkTurquoise", RGB_Color(0 * 255.0f, 0.807843 * 255.0f, 0.819608 * 255.0f)},
    {"darkViolet", RGB_Color(0.580392 * 255.0f, 0 * 255.0f, 0.827451 * 255.0f)},
    {"darkblue", RGB_Color(0.f, 0.f, 139.f)},
    {"darkcyan", RGB_Color(0.f, 139.f, 139.f)},
    {"darkgoldenrod", RGB_Color(184.f, 134.f, 11.f)},
    {"darkgray", RGB_Color(169.f, 169.f, 169.f)},
    {"darkgreen", RGB_Color(0.f, 100.f, 0.f)},
    {"darkkhaki", RGB_Color(189.f, 183.f, 107.f)},
    {"darkmagenta", RGB_Color(139.f, 0.f, 139.f)},
    {"darkolivegreen", RGB_Color(85.f, 107.f, 47.f)},
    {"darkorange", RGB_Color(255.f, 140.f, 0.f)},
    {"darkorchid", RGB_Color(153.f, 50.f, 204.f)},
    {"darkred", RGB_Color(139.f, 0.f, 0.f)},
    {"darksalmon", RGB_Color(233.f, 150.f, 122.f)},
    {"darkseagreen", RGB_Color(143.f, 188.f, 143.f)},
    {"darkslateblue", RGB_Color(72.f, 61.f, 139.f)},
    {"darkslategray", RGB_Color(47.f, 79.f, 79.f)},
    {"darkturquoise", RGB_Color(0.f, 206.f, 209.f)},
    {"darkviolet", RGB_Color(148.f, 0.f, 211.f)},
    {"deepPink", RGB_Color(1 * 255.0f, 0.0784314 * 255.0f, 0.576471 * 255.0f)},
    {"deepSkyBlue", RGB_Color(0 * 255.0f, 0.74902 * 255.0f, 1 * 255.0f)},
    {"deeppink", RGB_Color(255.f, 20.f, 147.f)},
    {"deepskyblue", RGB_Color(0.f, 191.f, 255.f)},
    {"dimGray", RGB_Color(0.411765 * 255.0f, 0.411765 * 255.0f, 0.411765 * 255.0f)},
    {"dimGrey", RGB_Color(0.411765 * 255.0f, 0.411765 * 255.0f, 0.411765 * 255.0f)},
    {"dimgray", RGB_Color(105.f, 105.f, 105.f)},
    {"dodgerBlue", RGB_Color(0.117647 * 255.0f, 0.564706 * 255.0f, 1 * 255.0f)},
    {"dodgerblue", RGB_Color(30.f, 144.f, 255.f)},
    {"fireBrick", RGB_Color(0.698039 * 255.0f, 0.133333 * 255.0f, 0.133333 * 255.0f)},
    {"firebrick", RGB_Color(178.f, 34.f, 34.f)},
    {"floralWhite", RGB_Color(1 * 255.0f, 0.980392 * 255.0f, 0.941176 * 255.0f)},
    {"floralwhite", RGB_Color(255.f, 250.f, 240.f)},
    {"forestGreen", RGB_Color(0.133333 * 255.0f, 0.545098 * 255.0f, 0.133333 * 255.0f)},
    {"forestgreen", RGB_Color(34.f, 139.f, 34.f)},
    {"fuchsia", RGB_Color(255.f, 0.f, 255.f)},
    {"gainsboro", RGB_Color(220.f, 220.f, 220.f)},
    {"ghostWhite", RGB_Color(0.972549 * 255.0f, 0.972549 * 255.0f, 1 * 255.0f)},
    {"ghostwhite", RGB_Color(248.f, 248.f, 255.f)},
    {"gold", RGB_Color(255.f, 215.f, 0.f)},
    {"goldenRod", RGB_Color(0.854902 * 255.0f, 0.647059 * 255.0f, 0.12549 * 255.0f)},
    {"goldenrod", RGB_Color(218.f, 165.f, 32.f)},
    {"gray", RGB_Color(128.f, 128.f, 128.f)},
    {"green", RGB_Color(0.f, 128.f, 0.f)},
    {"greenYellow", RGB_Color(0.678431 * 255.0f, 1 * 255.0f, 0.184314 * 255.0f)},
    {"greenyellow", RGB_Color(173.f, 255.f, 47.f)},
    {"grey", RGB_Color(0.501961 * 255.0f, 0.501961 * 255.0f, 0.501961 * 255.0f)},
    {"honeyDew", RGB_Color(0.941176 * 255.0f, 1 * 255.0f, 0.941176 * 255.0f)},
    {"honeydew", RGB_Color(240.f, 255.f, 240.f)},
    {"hotPink", RGB_Color(1 * 255.0f, 0.411765 * 255.0f, 0.705882 * 255.0f)},
    {"hotpink", RGB_Color(255.f, 105.f, 180.f)},
    {"indianRed", RGB_Color(0.803922 * 255.0f, 0.360784 * 255.0f, 0.360784 * 255.0f)},
    {"indianred", RGB_Color(205.f, 92.f, 92.f)},
    {"indigo", RGB_Color(75.f, 0.f, 130.f)},
    {"ivory", RGB_Color(255.f, 255.f, 240.f)},
    {"khaki", RGB_Color(240.f, 230.f, 140.f)},
    {"lavender", RGB_Color(230.f, 230.f, 250.f)},
    {"lavenderBlush", RGB_Color(1.0f * 255.0f, 0.941176f * 255.0f, 0.960784f * 255.0f)},
    {"lavenderblush", RGB_Color(255.f, 240.f, 245.f)},
    {"lawnGreen", RGB_Color(0.486275f * 255.0f, 0.988235f * 255.0f, 0.0f * 255.0f)},
    {"lawngreen", RGB_Color(124.f, 252.f, 0.f)},
    {"lemonChiffon", RGB_Color(1.0f * 255.0f, 0.980392f * 255.0f, 0.803922f * 255.0f)},
    {"lemonchiffon", RGB_Color(255.f, 250.f, 205.f)},
    {"lightBlue", RGB_Color(0.678431f * 255.0f, 0.847059f * 255.0f, 0.901961f * 255.0f)},
    {"lightCoral", RGB_Color(0.941176f * 255.0f, 0.501961f * 255.0f, 0.501961f * 255.0f)},
    {"lightCyan", RGB_Color(0.878431f * 255.0f, 1.0f * 255.0f, 1.0f * 255.0f)},
    {"lightGoldenRodYellow", RGB_Color(0.980392f * 255.0f, 0.980392f * 255.0f, 0.823529f * 255.0f)},
    {"lightGray", RGB_Color(0.827451f * 255.0f, 0.827451f * 255.0f, 0.827451f * 255.0f)},
    {"lightGreen", RGB_Color(0.564706f * 255.0f, 0.933333f * 255.0f, 0.564706f * 255.0f)},
    {"lightGrey", RGB_Color(0.827451f * 255.0f, 0.827451f * 255.0f, 0.827451f * 255.0f)},
    {"lightPink", RGB_Color(1.0f * 255.0f, 0.713726f * 255.0f, 0.756863f * 255.0f)},
    {"lightSalmon", RGB_Color(1.0f * 255.0f, 0.627451f * 255.0f, 0.478431f * 255.0f)},
    {"lightSeaGreen", RGB_Color(0.12549f * 255.0f, 0.698039f * 255.0f, 0.666667f * 255.0f)},
    {"lightSkyBlue", RGB_Color(0.529412f * 255.0f, 0.807843f * 255.0f, 0.980392f * 255.0f)},
    {"lightSlateGray", RGB_Color(0.466667f * 255.0f, 0.533333f * 255.0f, 0.6f * 255.0f)},
    {"lightSlateGrey", RGB_Color(0.466667f * 255.0f, 0.533333f * 255.0f, 0.6f * 255.0f)},
    {"lightSteelBlue", RGB_Color(0.690196f * 255.0f, 0.768627f * 255.0f, 0.870588f * 255.0f)},
    {"lightYellow", RGB_Color(1.0f * 255.0f, 1.0f * 255.0f, 0.878431f * 255.0f)},
    {"lightblue", RGB_Color(173.f, 216.f, 230.f)},
    {"lightcoral", RGB_Color(240.f, 128.f, 128.f)},
    {"lightcyan", RGB_Color(224.f, 255.f, 255.f)},
    {"lightgoldenrodyellow", RGB_Color(250.f, 250.f, 210.f)},
    {"lightgray", RGB_Color(211.f, 211.f, 211.f)},
    {"lightgreen", RGB_Color(144.f, 238.f, 144.f)},
    {"lightpink", RGB_Color(255.f, 182.f, 193.f)},
    {"lightsalmon", RGB_Color(255.f, 160.f, 122.f)},
    {"lightseagreen", RGB_Color(32.f, 178.f, 170.f)},
    {"lightskyblue", RGB_Color(135.f, 206.f, 250.f)},
    {"lightslategray", RGB_Color(119.f, 136.f, 153.f)},
    {"lightsteelblue", RGB_Color(176.f, 196.f, 222.f)},
    {"lightyellow", RGB_Color(255.f, 255.f, 224.f)},
    {"lime", RGB_Color(0.f, 255.f, 0.f)},
    {"limeGreen", RGB_Color(0.196078f * 255.0f, 0.803922f * 255.0f, 0.196078f * 255.0f)},
    {"limegreen", RGB_Color(50.f, 205.f, 50.f)},
    {"linen", RGB_Color(250.f, 240.f, 230.f)},
    {"magenta", RGB_Color(255.f, 0.f, 255.f)},
    {"maroon", RGB_Color(128.f, 0.f, 0.f)},
    {"mediumAquaMarine", RGB_Color(0.4f * 255.0f, 0.803922f * 255.0f, 0.666667f * 255.0f)},
    {"mediumBlue", RGB_Color(0.0f, 0.0f, 0.803922f * 255.0f)},
    {"mediumOrchid", RGB_Color(0.729412f * 255.0f, 0.333333f * 255.0f, 0.827451f * 255.0f)},
    {"mediumPurple", RGB_Color(0.576471f * 255.0f, 0.439216f * 255.0f, 0.858824f * 255.0f)},
    {"mediumSeaGreen", RGB_Color(0.235294f * 255.0f, 0.701961f * 255.0f, 0.443137f * 255.0f)},
    {"mediumSlateBlue", RGB_Color(0.482353f * 255.0f, 0.407843f * 255.0f, 0.933333f * 255.0f)},
    {"mediumSpringGreen", RGB_Color(0.0f, 0.980392f * 255.0f, 0.603922f * 255.0f)},
    {"mediumTurquoise", RGB_Color(0.282353f * 255.0f, 0.819608f * 255.0f, 0.8f * 255.0f)},
    {"mediumVioletRed", RGB_Color(0.780392f * 255.0f, 0.0823529f * 255.0f, 0.521569f * 255.0f)},
    {"mediumaquamarine", RGB_Color(102.f, 205.f, 170.f)},
    {"mediumblue", RGB_Color(0.f, 0.f, 205.f)},
    {"mediumorchid", RGB_Color(186.f, 85.f, 211.f)},
    {"mediumpurple", RGB_Color(147.f, 112.f, 219.f)},
    {"mediumseagreen", RGB_Color(60.f, 179.f, 113.f)},
    {"mediumslateblue", RGB_Color(123.f, 104.f, 238.f)},
    {"mediumspringgreen", RGB_Color(0.f, 250.f, 154.f)},
    {"mediumturquoise", RGB_Color(72.f, 209.f, 204.f)},
    {"mediumvioletred", RGB_Color(199.f, 21.f, 133.f)},
    {"midnightBlue", RGB_Color(0.0980392f * 255.0f, 0.0980392f * 255.0f, 0.439216f * 255.0f)},
    {"midnightblue", RGB_Color(25.f, 25.f, 112.f)},
    {"mintCream", RGB_Color(0.960784f * 255.0f, 1.0f * 255.0f, 0.980392f * 255.0f)},
    {"mintcream", RGB_Color(245.f, 255.f, 250.f)},
    {"mistyRose", RGB_Color(1.0f * 255.0f, 0.894118f * 255.0f, 0.882353f * 255.0f)},
    {"mistyrose", RGB_Color(255.f, 228.f, 225.f)},
    {"moccasin", RGB_Color(255.f, 228.f, 181.f)},
    {"navajoWhite", RGB_Color(1.0f * 255.0f, 0.870588f * 255.0f, 0.678431f * 255.0f)},
    {"navajowhite", RGB_Color(255.f, 222.f, 173.f)},
    {"navy", RGB_Color(0.f, 0.f, 128.f)},
    {"oldLace", RGB_Color(0.992157f * 255.0f, 0.960784f * 255.0f, 0.901961f * 255.0f)},
    {"oldlace", RGB_Color(253.f, 245.f, 230.f)},
    {"olive", RGB_Color(128.f, 128.f, 0.f)},
    {"oliveDrab", RGB_Color(0.419608f * 255.0f, 0.556863f * 255.0f, 0.137255f * 255.0f)},
    {"olivedrab", RGB_Color(107.f, 142.f, 35.f)},
    {"orange", RGB_Color(255.f, 165.f, 0.f)},
    {"orangeRed", RGB_Color(1.0f * 255.0f, 0.270588f * 255.0f, 0.0f * 255.0f)},
    {"orangered", RGB_Color(255.f, 69.f, 0.f)},
    {"orchid", RGB_Color(218.f, 112.f, 214.f)},
    {"paleGoldenRod", RGB_Color(0.933333f * 255.0f, 0.909804f * 255.0f, 0.666667f * 255.0f)},
    {"paleGreen", RGB_Color(0.596078f * 255.0f, 0.984314f * 255.0f, 0.596078f * 255.0f)},
    {"paleTurquoise", RGB_Color(0.686275f * 255.0f, 0.933333f * 255.0f, 0.933333f * 255.0f)},
    {"paleVioletRed", RGB_Color(0.858824f * 255.0f, 0.439216f * 255.0f, 0.576471f * 255.0f)},
    {"palegoldenrod", RGB_Color(238.f, 232.f, 170.f)},
    {"palegreen", RGB_Color(152.f, 251.f, 152.f)},
    {"paleturquoise", RGB_Color(175.f, 238.f, 238.f)},
    {"palevioletred", RGB_Color(219.f, 112.f, 147.f)},
    {"papayaWhip", RGB_Color(1.0f * 255.0f, 0.937255f * 255.0f, 0.835294f * 255.0f)},
    {"papayawhip", RGB_Color(255.f, 239.f, 213.f)},
    {"peachPuff", RGB_Color(1.0f * 255.0f, 0.854902f * 255.0f, 0.72549f * 255.0f)},
    {"peachpuff", RGB_Color(255.f, 218.f, 185.f)},
    {"peru", RGB_Color(205.f, 133.f, 63.f)},
    {"pink", RGB_Color(255.f, 192.f, 203.f)},
    {"plum", RGB_Color(221.f, 160.f, 221.f)},
    {"powderBlue", RGB_Color(0.690196f * 255.0f, 0.878431f * 255.0f, 0.901961f * 255.0f)},
    {"powderblue", RGB_Color(176.f, 224.f, 230.f)},
    {"purple", RGB_Color(128.f, 0.f, 128.f)},
    {"rebeccapurple", RGB_Color(102.f, 51.f, 153.f)},
    {"red", RGB_Color(255.f, 0.f, 0.f)},
    {"rosyBrown", RGB_Color(0.737255f * 255.0f, 0.560784f * 255.0f, 0.560784f * 255.0f)},
    {"rosybrown", RGB_Color(188.f, 143.f, 143.f)},
    {"royalBlue", RGB_Color(0.254902f * 255.0f, 0.411765f * 255.0f, 0.882353f * 255.0f)},
    {"royalblue", RGB_Color(65.f, 105.f, 225.f)},
    {"saddleBrown", RGB_Color(0.545098f * 255.0f, 0.270588f * 255.0f, 0.0745098f * 255.0f)},
    {"saddlebrown", RGB_Color(139.f, 69.f, 19.f)},
    {"salmon", RGB_Color(250.f, 128.f, 114.f)},
    {"sandyBrown", RGB_Color(0.956863f * 255.0f, 0.643137f * 255.0f, 0.376471f * 255.0f)},
    {"sandybrown", RGB_Color(244.f, 164.f, 96.f)},
    {"seaGreen", RGB_Color(0.180392f * 255.0f, 0.545098f * 255.0f, 0.341176f * 255.0f)},
    {"seaShell", RGB_Color(1.0f * 255.0f, 0.960784f * 255.0f, 0.933333f * 255.0f)},
    {"seagreen", RGB_Color(46.f, 139.f, 87.f)},
    {"seashell", RGB_Color(255.f, 245.f, 238.f)},
    {"sienna", RGB_Color(160.f, 82.f, 45.f)},
    {"silver", RGB_Color(192.f, 192.f, 192.f)},
    {"skyBlue", RGB_Color(0.529412f * 255.0f, 0.807843f * 255.0f, 0.921569f * 255.0f)},
    {"skyblue", RGB_Color(135.f, 206.f, 235.f)},
    {"slateBlue", RGB_Color(0.415686f * 255.0f, 0.352941f * 255.0f, 0.803922f * 255.0f)},
    {"slateGray", RGB_Color(0.439216f * 255.0f, 0.501961f * 255.0f, 0.564706f * 255.0f)},
    {"slateGrey", RGB_Color(0.439216f * 255.0f, 0.501961f * 255.0f, 0.564706f * 255.0f)},
    {"slateblue", RGB_Color(106.f, 90.f, 205.f)},
    {"slategray", RGB_Color(112.f, 128.f, 144.f)},
    {"snow", RGB_Color(255.f, 250.f, 250.f)},
    {"springGreen", RGB_Color(0.0f, 1.0f * 255.0f, 0.498039f * 255.0f)},
    {"springgreen", RGB_Color(0.f, 255.f, 127.f)},
    {"steelBlue", RGB_Color(0.27451f * 255.0f, 0.509804f * 255.0f, 0.705882f * 255.0f)},
    {"steelblue", RGB_Color(70.f, 130.f, 180.f)},
    {"teal", RGB_Color(0.f, 128.f, 128.f)},
    {"thistle", RGB_Color(216.f, 191.f, 216.f)},
    {"tomato", RGB_Color(255.f, 99.f, 71.f)},
    {"turquoise", RGB_Color(64.f, 224.f, 208.f)},
    {"violet", RGB_Color(238.f, 130.f, 238.f)},
    {"wheat", RGB_Color(245.f, 222.f, 179.f)},
    {"white", RGB_Color(255.f, 255.f, 255.f)},
    {"whiteSmoke", RGB_Color(0.960784f * 255.0f, 0.960784f * 255.0f, 0.960784f * 255.0f)},
    {"whitesmoke", RGB_Color(245.f, 245.f, 245.f)},
    {"yellow", RGB_Color(255.f, 255.f, 0.f)},
    {"yellowGreen", RGB_Color(0.603922f * 255.0f, 0.803922f * 255.0f, 0.196078f * 255.0f)},
    {"yellowgreen", RGB_Color(154.f, 205.f, 50.f)},
};