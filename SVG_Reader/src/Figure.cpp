#include "Figure.h"
#include "Render.h"

// class Ficgure
// Constructor
Figure::Figure() {
	stroke_width = 1;
	stroke.setA(0);
}

Figure::Figure(const Figure& figure) {
	fill = figure.fill;
	stroke = figure.stroke;
	stroke_width = figure.stroke_width;
	transform = figure.transform;
}

// Set attribute
void Figure::setFill(const std::string& fill) {
	this->fill.setRGB(fill);
}

void Figure::setFillOpacity(const std::string& fill_opacity) {
	fill.setA(fill_opacity);
}

void Figure::setStroke(const std::string& stroke) {
	this->stroke.setRGB(stroke);
}

void Figure::setStrokeOpacity(const std::string& stroke_opacity) {
	stroke.setA(stroke_opacity);
}

void Figure::setStrokeWidth(const std::string& stroke_width) {
	this->stroke_width = stof(stroke_width);
}

void Figure::setTranslate(const std::string& translate) {
	std::stringstream ss(translate);
	float x, y;
	ss >> x >> y;
	transform.push_back({ SVG_Translate, Point(x, y) });
}

void Figure::setRotate(const std::string& rotate) {
	transform.push_back({ SVG_Rotate, Point(stof(rotate), 0) });
}

void Figure::setScale(const std::string& scale) {
	std::stringstream ss(scale);
	float x, y = 0;
	ss >> x >> y;
	if (y == 0) y = x;
	transform.push_back({ SVG_Scale, Point(x, y) });
}

void Figure::setTransform(const std::string& transform) {
	std::string line = transform;
	for (char& c : line) if (c == '(' || c == ',') c = ' ';

	std::stringstream ss(line);
	std::string attribute, value;
	while (ss >> attribute) {
		getline(ss, value, ')');
		if (attribute == "translate") setTranslate(value);
		else if (attribute == "rotate") setRotate(value);
		else if (attribute == "scale") setScale(value);
	}
}

void Figure::setGroupAttributes(Figure* group) {
	fill = group->fill;
	stroke = group->stroke;
	stroke_width = group->stroke_width;
	transform = group->transform;
}

void Figure::setAttributes(const std::string& line) {
	std::stringstream ss(line);
	std::string attribute, value;
	while (ss >> attribute) {
		static char end;
		end = (attribute == "|") ? '<' : '"';
		getline(ss, value, end);
		getline(ss, value, end);
		if (attribute == "fill") setFill(value);
		else if (attribute == "stroke") setStroke(value);
		else if (attribute == "fill-opacity") setFillOpacity(value);
		else if (attribute == "stroke-width") setStrokeWidth(value);
		else if (attribute == "stroke-opacity") setStrokeOpacity(value);
		else if (attribute == "transform") setTransform(value);
		else setAttributes(attribute, value);
		//cout << "{" << attribute << "," << value << "}\n";
	}
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class FigureFactory
// Private
	// Attribute
FigureFactory* FigureFactory::Instance = NULL;

// Public
	// Method
FigureFactory* FigureFactory::getInstance() {
	if (Instance == NULL)
		Instance = new FigureFactory();
	return Instance;
}

Figure* FigureFactory::getFigure(const std::string& figure) {
	if (figure == "rect") return new Drawable_Rectangle();
	if (figure == "ellipse") return new Drawable_Ellipse();
	if (figure == "circle") return new Drawable_Circle();
	if (figure == "line") return new Drawable_Line();
	if (figure == "polyline") return new Drawable_Polyline();
	if (figure == "polygon") return new Drawable_Polygon();
	if (figure == "text") return new Drawable_Text();
	if (figure == "path") return new Drawable_Path();
	return NULL;
}

void FigureFactory::deleteInstance() {
	if (Instance != NULL)
		delete Instance;
	Instance = NULL;
}
//-----------END-OF-IMPLEMENTATION-----------//