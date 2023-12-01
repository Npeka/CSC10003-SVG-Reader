#include "Color.h"

// Constructor
Color::Color() {
	r = g = b = 0;
	a = 255;
}

Color::Color(const string& color) {
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
void Color::setA(const string& a) {
    if (this->a) check_exception("color", "a", this->a = stof(a) * 255);
}
void Color::setA(const float& a) {
    if (this->a) this->a = a * 255;
}

void Color::setRGB(const string& color) {
    string Color(color);
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
	else if (color.find("rgb") != string::npos) {
		string rgb(Color);
		for (char& c : rgb) if (!isdigit(c)) c = ' ';
		stringstream ss(rgb); ss >> r >> g >> b;
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
        *this = setColorByName(Color);
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

const Color& setColorByName(const string& color) {
    if (color == "gray") return gray;
    if (color == "white") return white;
    if (color == "black") return black;
    if (color == "red") return red;
    if (color == "green") return green;
    if (color == "blue") return blue;
    if (color == "cyan") return cyan;
    if (color == "magenta") return magenta;
    if (color == "yellow") return yellow;
    if (color == "aliceBlue") return aliceBlue;
    if (color == "antiqueWhite") return antiqueWhite;
    if (color == "aqua") return aqua;
    if (color == "aquamarine") return aquamarine;
    if (color == "azure") return azure;
    if (color == "beige") return beige;
    if (color == "bisque") return bisque;
    if (color == "blanchedAlmond") return blanchedAlmond;
    if (color == "blueViolet") return blueViolet;
    if (color == "brown") return brown;
    if (color == "burlyWood") return burlyWood;
    if (color == "cadetBlue") return cadetBlue;
    if (color == "chartreuse") return chartreuse;
    if (color == "chocolate") return chocolate;
    if (color == "coral") return coral;
    if (color == "cornflowerBlue") return cornflowerBlue;
    if (color == "cornsilk") return cornsilk;
    if (color == "crimson") return crimson;
    if (color == "darkBlue") return darkBlue;
    if (color == "darkCyan") return darkCyan;
    if (color == "darkGoldenRod") return darkGoldenRod;
    if (color == "darkGray") return darkGray;
    if (color == "darkGrey") return darkGrey;
    if (color == "darkGreen") return darkGreen;
    if (color == "darkKhaki") return darkKhaki;
    if (color == "darkMagenta") return darkMagenta;
    if (color == "darkOliveGreen") return darkOliveGreen;
    if (color == "darkOrange") return darkOrange;
    if (color == "darkOrchid") return darkOrchid;
    if (color == "darkRed") return darkRed;
    if (color == "darkSalmon") return darkSalmon;
    if (color == "darkSeaGreen") return darkSeaGreen;
    if (color == "darkSlateBlue") return darkSlateBlue;
    if (color == "darkSlateGray") return darkSlateGray;
    if (color == "darkSlateGrey") return darkSlateGrey;
    if (color == "darkTurquoise") return darkTurquoise;
    if (color == "darkViolet") return darkViolet;
    if (color == "deepPink") return deepPink;
    if (color == "deepSkyBlue") return deepSkyBlue;
    if (color == "dimGray") return dimGray;
    if (color == "dimGrey") return dimGrey;
    if (color == "dodgerBlue") return dodgerBlue;
    if (color == "fireBrick") return fireBrick;
    if (color == "floralWhite") return floralWhite;
    if (color == "forestGreen") return forestGreen;
    if (color == "fuchsia") return fuchsia;
    if (color == "gainsboro") return gainsboro;
    if (color == "ghostWhite") return ghostWhite;
    if (color == "gold") return gold;
    if (color == "goldenRod") return goldenRod;
    if (color == "grey") return grey;
    if (color == "greenYellow") return greenYellow;
    if (color == "honeyDew") return honeyDew;
    if (color == "hotPink") return hotPink;
    if (color == "indianRed") return indianRed;
    if (color == "indigo") return indigo;
    if (color == "ivory") return ivory;
    if (color == "khaki") return khaki;
    if (color == "lavender") return lavender;
    if (color == "lavenderBlush") return lavenderBlush;
    if (color == "lawnGreen") return lawnGreen;
    if (color == "lemonChiffon") return lemonChiffon;
    if (color == "lightBlue") return lightBlue;
    if (color == "lightCoral") return lightCoral;
    if (color == "lightCyan") return lightCyan;
    if (color == "lightGoldenRodYellow") return lightGoldenRodYellow;
    if (color == "lightGray") return lightGray;
    if (color == "lightGrey") return lightGrey;
    if (color == "lightGreen") return lightGreen;
    if (color == "lightPink") return lightPink;
    if (color == "lightSalmon") return lightSalmon;
    if (color == "lightSeaGreen") return lightSeaGreen;
    if (color == "lightSkyBlue") return lightSkyBlue;
    if (color == "lightSlateGray") return lightSlateGray;
    if (color == "lightSlateGrey") return lightSlateGrey;
    if (color == "lightSteelBlue") return lightSteelBlue;
    if (color == "lightYellow") return lightYellow;
    if (color == "lime") return lime;
    if (color == "limeGreen") return limeGreen;
    if (color == "linen") return linen;
    if (color == "maroon") return maroon;
    if (color == "mediumAquaMarine") return mediumAquaMarine;
    if (color == "mediumBlue") return mediumBlue;
    if (color == "mediumOrchid") return mediumOrchid;
    if (color == "mediumPurple") return mediumPurple;
    if (color == "mediumSeaGreen") return mediumSeaGreen;
    if (color == "mediumSlateBlue") return mediumSlateBlue;
    if (color == "mediumSpringGreen") return mediumSpringGreen;
    if (color == "mediumTurquoise") return mediumTurquoise;
    if (color == "mediumVioletRed") return mediumVioletRed;
    if (color == "midnightBlue") return midnightBlue;
    if (color == "mintCream") return mintCream;
    if (color == "mistyRose") return mistyRose;
    if (color == "moccasin") return moccasin;
    if (color == "navajoWhite") return navajoWhite;
    if (color == "navy") return navy;
    if (color == "oldLace") return oldLace;
    if (color == "olive") return olive;
    if (color == "oliveDrab") return oliveDrab;
    if (color == "orange") return orange;
    if (color == "orangeRed") return orangeRed;
    if (color == "orchid") return orchid;
    if (color == "paleGoldenRod") return paleGoldenRod;
    if (color == "paleGreen") return paleGreen;
    if (color == "paleTurquoise") return paleTurquoise;
    if (color == "paleVioletRed") return paleVioletRed;
    if (color == "papayaWhip") return papayaWhip;
    if (color == "peachPuff") return peachPuff;
    if (color == "peru") return peru;
    if (color == "pink") return pink;
    if (color == "plum") return plum;
    if (color == "powderBlue") return powderBlue;
    if (color == "purple") return purple;
    if (color == "rosyBrown") return rosyBrown;
    if (color == "royalBlue") return royalBlue;
    if (color == "saddleBrown") return saddleBrown;
    if (color == "salmon") return salmon;
    if (color == "sandyBrown") return sandyBrown;
    if (color == "seaGreen") return seaGreen;
    if (color == "seaShell") return seaShell;
    if (color == "sienna") return sienna;
    if (color == "silver") return silver;
    if (color == "skyBlue") return skyBlue;
    if (color == "slateBlue") return slateBlue;
    if (color == "slateGray") return slateGray;
    if (color == "slateGrey") return slateGrey;
    if (color == "snow") return snow;
    if (color == "springGreen") return springGreen;
    if (color == "steelBlue") return steelBlue;
    if (color == "blueSteel") return blueSteel;
    if (color == "teal") return teal;
    if (color == "thistle") return thistle;
    if (color == "tomato") return tomato;
    if (color == "turquoise") return turquoise;
    if (color == "violet") return violet;
    if (color == "wheat") return wheat;
    if (color == "whiteSmoke") return whiteSmoke;
    if (color == "yellowGreen") return yellowGreen;
    return Color();
}

const Color gray(255.0f / 2.0f, 255.0f / 2.0f, 255.0f / 2.0f);
const Color white(255.0f, 255.0f, 255.0f);
const Color red(255.0f, 0, 0);
const Color green(0, 255.0f, 0);
const Color blue(0, 0, 255.0f);
const Color cyan(0, 255.0f, 255.0f);
const Color magenta(255.0f, 0, 255.0f);
const Color yellow(255.0f, 255.0f, 0);
const Color black(0, 0, 0);
const Color aliceBlue(0.941176f * 255.0f, 0.972549f * 255.0f, 1.0f * 255.0f);
const Color antiqueWhite(0.980392f * 255.0f, 0.921569f * 255.0f, 0.843137f * 255.0f);
const Color aqua(0.0f, 1.0f * 255.0f, 1.0f * 255.0f);
const Color aquamarine(0.498039f * 255.0f, 1.0f * 255.0f, 0.831373f * 255.0f);
const Color azure(0.941176f * 255.0f, 1.0f * 255.0f, 1.0f * 255.0f);
const Color beige(0.960784f * 255.0f, 0.960784f * 255.0f, 0.862745f * 255.0f);
const Color bisque(1.0f * 255.0f, 0.894118f * 255.0f, 0.768627f * 255.0f);
const Color blanchedAlmond(1.0f * 255.0f, 0.921569f * 255.0f, 0.803922f * 255.0f);
const Color blueViolet(0.541176f * 255.0f, 0.168627f * 255.0f, 0.886275f * 255.0f);
const Color brown(0.647059f * 255.0f, 0.164706f * 255.0f, 0.164706f * 255.0f);
const Color burlyWood(0.870588f * 255.0f, 0.721569f * 255.0f, 0.529412f * 255.0f);
const Color cadetBlue(0.372549f * 255.0f, 0.619608f * 255.0f, 0.627451f * 255.0f);
const Color chartreuse(0.498039f * 255.0f, 1.0f * 255.0f, 0.0f);
const Color chocolate(0.823529f * 255.0f, 0.411765f * 255.0f, 0.117647f * 255.0f);
const Color coral(1.0f * 255.0f, 0.498039f * 255.0f, 0.313726f * 255.0f);
const Color cornflowerBlue(0.392157f * 255.0f, 0.584314f * 255.0f, 0.929412f * 255.0f);
const Color cornsilk(1.0f * 255.0f, 0.972549f * 255.0f, 0.862745f * 255.0f);
const Color crimson(0.862745f * 255.0f, 0.0784314f * 255.0f, 0.235294f * 255.0f);
const Color darkBlue(0.0f, 0.0f, 0.545098f * 255.0f);
const Color darkCyan(0.0f, 0.545098f * 255.0f, 0.545098f * 255.0f);
const Color darkGoldenRod(0.721569 * 255.0f, 0.52549 * 255.0f, 0.0431373 * 255.0f);
const Color darkGray(0.662745 * 255.0f, 0.662745 * 255.0f, 0.662745 * 255.0f);
const Color darkGrey(0.662745 * 255.0f, 0.662745 * 255.0f, 0.662745 * 255.0f);
const Color darkGreen(0 * 255.0f, 0.392157 * 255.0f, 0 * 255.0f);
const Color darkKhaki(0.741176 * 255.0f, 0.717647 * 255.0f, 0.419608 * 255.0f);
const Color darkMagenta(0.545098 * 255.0f, 0 * 255.0f, 0.545098 * 255.0f);
const Color darkOliveGreen(0.333333 * 255.0f, 0.419608 * 255.0f, 0.184314 * 255.0f);
const Color darkOrange(1 * 255.0f, 0.54902 * 255.0f, 0 * 255.0f);
const Color darkOrchid(0.6 * 255.0f, 0.196078 * 255.0f, 0.8 * 255.0f);
const Color darkRed(0.545098 * 255.0f, 0 * 255.0f, 0 * 255.0f);
const Color darkSalmon(0.913725 * 255.0f, 0.588235 * 255.0f, 0.478431 * 255.0f);
const Color darkSeaGreen(0.560784 * 255.0f, 0.737255 * 255.0f, 0.560784 * 255.0f);
const Color darkSlateBlue(0.282353 * 255.0f, 0.239216 * 255.0f, 0.545098 * 255.0f);
const Color darkSlateGray(0.184314 * 255.0f, 0.309804 * 255.0f, 0.309804 * 255.0f);
const Color darkSlateGrey(0.184314 * 255.0f, 0.309804 * 255.0f, 0.309804 * 255.0f);
const Color darkTurquoise(0 * 255.0f, 0.807843 * 255.0f, 0.819608 * 255.0f);
const Color darkViolet(0.580392 * 255.0f, 0 * 255.0f, 0.827451 * 255.0f);
const Color deepPink(1 * 255.0f, 0.0784314 * 255.0f, 0.576471 * 255.0f);
const Color deepSkyBlue(0 * 255.0f, 0.74902 * 255.0f, 1 * 255.0f);
const Color dimGray(0.411765 * 255.0f, 0.411765 * 255.0f, 0.411765 * 255.0f);
const Color dimGrey(0.411765 * 255.0f, 0.411765 * 255.0f, 0.411765 * 255.0f);
const Color dodgerBlue(0.117647 * 255.0f, 0.564706 * 255.0f, 1 * 255.0f);
const Color fireBrick(0.698039 * 255.0f, 0.133333 * 255.0f, 0.133333 * 255.0f);
const Color floralWhite(1 * 255.0f, 0.980392 * 255.0f, 0.941176 * 255.0f);
const Color forestGreen(0.133333 * 255.0f, 0.545098 * 255.0f, 0.133333 * 255.0f);
const Color fuchsia(1 * 255.0f, 0 * 255.0f, 1 * 255.0f);
const Color gainsboro(0.862745 * 255.0f, 0.862745 * 255.0f, 0.862745 * 255.0f);
const Color ghostWhite(0.972549 * 255.0f, 0.972549 * 255.0f, 1 * 255.0f);
const Color gold(1 * 255.0f, 0.843137 * 255.0f, 0 * 255.0f);
const Color goldenRod(0.854902 * 255.0f, 0.647059 * 255.0f, 0.12549 * 255.0f);
const Color grey(0.501961 * 255.0f, 0.501961 * 255.0f, 0.501961 * 255.0f);
const Color greenYellow(0.678431 * 255.0f, 1 * 255.0f, 0.184314 * 255.0f);
const Color honeyDew(0.941176 * 255.0f, 1 * 255.0f, 0.941176 * 255.0f);
const Color hotPink(1 * 255.0f, 0.411765 * 255.0f, 0.705882 * 255.0f);
const Color indianRed(0.803922 * 255.0f, 0.360784 * 255.0f, 0.360784 * 255.0f);
const Color indigo(0.294118 * 255.0f, 0 * 255.0f, 0.509804 * 255.0f);
const Color ivory(1 * 255.0f, 1 * 255.0f, 0.941176 * 255.0f);
const Color khaki(0.941176 * 255.0f, 0.901961 * 255.0f, 0.54902 * 255.0f);
const Color lavender(0.901961f * 255.0f, 0.901961f * 255.0f, 0.980392f * 255.0f);
const Color lavenderBlush(1.0f * 255.0f, 0.941176f * 255.0f, 0.960784f * 255.0f);
const Color lawnGreen(0.486275f * 255.0f, 0.988235f * 255.0f, 0.0f * 255.0f);
const Color lemonChiffon(1.0f * 255.0f, 0.980392f * 255.0f, 0.803922f * 255.0f);
const Color lightBlue(0.678431f * 255.0f, 0.847059f * 255.0f, 0.901961f * 255.0f);
const Color lightCoral(0.941176f * 255.0f, 0.501961f * 255.0f, 0.501961f * 255.0f);
const Color lightCyan(0.878431f * 255.0f, 1.0f * 255.0f, 1.0f * 255.0f);
const Color lightGoldenRodYellow(0.980392f * 255.0f, 0.980392f * 255.0f, 0.823529f * 255.0f);
const Color lightGray(0.827451f * 255.0f, 0.827451f * 255.0f, 0.827451f * 255.0f);
const Color lightGrey(0.827451f * 255.0f, 0.827451f * 255.0f, 0.827451f * 255.0f);
const Color lightGreen(0.564706f * 255.0f, 0.933333f * 255.0f, 0.564706f * 255.0f);
const Color lightPink(1.0f * 255.0f, 0.713726f * 255.0f, 0.756863f * 255.0f);
const Color lightSalmon(1.0f * 255.0f, 0.627451f * 255.0f, 0.478431f * 255.0f);
const Color lightSeaGreen(0.12549f * 255.0f, 0.698039f * 255.0f, 0.666667f * 255.0f);
const Color lightSkyBlue(0.529412f * 255.0f, 0.807843f * 255.0f, 0.980392f * 255.0f);
const Color lightSlateGray(0.466667f * 255.0f, 0.533333f * 255.0f, 0.6f * 255.0f);
const Color lightSlateGrey(0.466667f * 255.0f, 0.533333f * 255.0f, 0.6f * 255.0f);
const Color lightSteelBlue(0.690196f * 255.0f, 0.768627f * 255.0f, 0.870588f * 255.0f);
const Color lightYellow(1.0f * 255.0f, 1.0f * 255.0f, 0.878431f * 255.0f);
const Color lime(0.0f * 255.0f, 1.0f * 255.0f, 0.0f * 255.0f);
const Color limeGreen(0.196078f * 255.0f, 0.803922f * 255.0f, 0.196078f * 255.0f);
const Color linen(0.980392f * 255.0f, 0.941176f * 255.0f, 0.901961f * 255.0f);
const Color maroon(0.501961f * 255.0f, 0.0f, 0.0f);
const Color mediumAquaMarine(0.4f * 255.0f, 0.803922f * 255.0f, 0.666667f * 255.0f);
const Color mediumBlue(0.0f, 0.0f, 0.803922f * 255.0f);
const Color mediumOrchid(0.729412f * 255.0f, 0.333333f * 255.0f, 0.827451f * 255.0f);
const Color mediumPurple(0.576471f * 255.0f, 0.439216f * 255.0f, 0.858824f * 255.0f);
const Color mediumSeaGreen(0.235294f * 255.0f, 0.701961f * 255.0f, 0.443137f * 255.0f);
const Color mediumSlateBlue(0.482353f * 255.0f, 0.407843f * 255.0f, 0.933333f * 255.0f);
const Color mediumSpringGreen(0.0f, 0.980392f * 255.0f, 0.603922f * 255.0f);
const Color mediumTurquoise(0.282353f * 255.0f, 0.819608f * 255.0f, 0.8f * 255.0f);
const Color mediumVioletRed(0.780392f * 255.0f, 0.0823529f * 255.0f, 0.521569f * 255.0f);
const Color midnightBlue(0.0980392f * 255.0f, 0.0980392f * 255.0f, 0.439216f * 255.0f);
const Color mintCream(0.960784f * 255.0f, 1.0f * 255.0f, 0.980392f * 255.0f);
const Color mistyRose(1.0f * 255.0f, 0.894118f * 255.0f, 0.882353f * 255.0f);
const Color moccasin(1.0f * 255.0f, 0.894118f * 255.0f, 0.709804f * 255.0f);
const Color navajoWhite(1.0f * 255.0f, 0.870588f * 255.0f, 0.678431f * 255.0f);
const Color navy(0.0f * 255.0f, 0.0f * 255.0f, 0.501961f * 255.0f);
const Color oldLace(0.992157f * 255.0f, 0.960784f * 255.0f, 0.901961f * 255.0f);
const Color olive(0.501961f * 255.0f, 0.501961f * 255.0f, 0.0f * 255.0f);
const Color oliveDrab(0.419608f * 255.0f, 0.556863f * 255.0f, 0.137255f * 255.0f);
const Color orange(1.0f * 255.0f, 0.647059f * 255.0f, 0.0f * 255.0f);
const Color orangeRed(1.0f * 255.0f, 0.270588f * 255.0f, 0.0f * 255.0f);
const Color orchid(0.854902f * 255.0f, 0.439216f * 255.0f, 0.839216f * 255.0f);
const Color paleGoldenRod(0.933333f * 255.0f, 0.909804f * 255.0f, 0.666667f * 255.0f);
const Color paleGreen(0.596078f * 255.0f, 0.984314f * 255.0f, 0.596078f * 255.0f);
const Color paleTurquoise(0.686275f * 255.0f, 0.933333f * 255.0f, 0.933333f * 255.0f);
const Color paleVioletRed(0.858824f * 255.0f, 0.439216f * 255.0f, 0.576471f * 255.0f);
const Color papayaWhip(1.0f * 255.0f, 0.937255f * 255.0f, 0.835294f * 255.0f);
const Color peachPuff(1.0f * 255.0f, 0.854902f * 255.0f, 0.72549f * 255.0f);
const Color peru(0.803922f * 255.0f, 0.521569f * 255.0f, 0.247059f * 255.0f);
const Color pink(1.0f * 255.0f, 0.752941f * 255.0f, 0.796078f * 255.0f);
const Color plum(0.866667f * 255.0f, 0.627451f * 255.0f, 0.866667f * 255.0f);
const Color powderBlue(0.690196f * 255.0f, 0.878431f * 255.0f, 0.901961f * 255.0f);
const Color purple(0.501961f * 255.0f, 0.0f * 255.0f, 0.501961f * 255.0f);
const Color rosyBrown(0.737255f * 255.0f, 0.560784f * 255.0f, 0.560784f * 255.0f);
const Color royalBlue(0.254902f * 255.0f, 0.411765f * 255.0f, 0.882353f * 255.0f);
const Color saddleBrown(0.545098f * 255.0f, 0.270588f * 255.0f, 0.0745098f * 255.0f);
const Color salmon(0.980392f * 255.0f, 0.501961f * 255.0f, 0.447059f * 255.0f);
const Color sandyBrown(0.956863f * 255.0f, 0.643137f * 255.0f, 0.376471f * 255.0f);
const Color seaGreen(0.180392f * 255.0f, 0.545098f * 255.0f, 0.341176f * 255.0f);
const Color seaShell(1.0f * 255.0f, 0.960784f * 255.0f, 0.933333f * 255.0f);
const Color sienna(0.627451f * 255.0f, 0.321569f * 255.0f, 0.176471f * 255.0f);
const Color silver(0.752941f * 255.0f, 0.752941f * 255.0f, 0.752941f * 255.0f);
const Color skyBlue(0.529412f * 255.0f, 0.807843f * 255.0f, 0.921569f * 255.0f);
const Color slateBlue(0.415686f * 255.0f, 0.352941f * 255.0f, 0.803922f * 255.0f);
const Color slateGray(0.439216f * 255.0f, 0.501961f * 255.0f, 0.564706f * 255.0f);
const Color slateGrey(0.439216f * 255.0f, 0.501961f * 255.0f, 0.564706f * 255.0f);
const Color snow(1.0f * 255.0f, 0.980392f * 255.0f, 0.980392f * 255.0f);
const Color springGreen(0.0f, 1.0f * 255.0f, 0.498039f * 255.0f);
const Color steelBlue(0.27451f * 255.0f, 0.509804f * 255.0f, 0.705882f * 255.0f);
const Color blueSteel(0.27451f * 255.0f, 0.509804f * 255.0f, 0.705882f * 255.0f);
const Color teal(0.0f, 0.501961f * 255.0f, 0.501961f * 255.0f);
const Color thistle(0.847059f * 255.0f, 0.74902f * 255.0f, 0.847059f * 255.0f);
const Color tomato(1.0f * 255.0f, 0.388235f * 255.0f, 0.278431f * 255.0f);
const Color turquoise(0.25098f * 255.0f, 0.878431f * 255.0f, 0.815686f * 255.0f);
const Color violet(0.933333f * 255.0f, 0.509804f * 255.0f, 0.933333f * 255.0f);
const Color wheat(0.960784f * 255.0f, 0.870588f * 255.0f, 0.701961f * 255.0f);
const Color whiteSmoke(0.960784f * 255.0f, 0.960784f * 255.0f, 0.960784f * 255.0f);
const Color yellowGreen(0.603922f * 255.0f, 0.803922f * 255.0f, 0.196078f * 255.0f);
