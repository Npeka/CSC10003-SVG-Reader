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
void Figure::setFill(const string& fill) {
	this->fill.setRGB(fill);
}

void Figure::setFillOpacity(const string& fill_opacity) {
	fill.setA(fill_opacity);
}

void Figure::setStroke(const string& stroke) {
	this->stroke.setRGB(stroke);
}

void Figure::setStrokeOpacity(const string& stroke_opacity) {
	stroke.setA(stroke_opacity);
}

void Figure::setStrokeWidth(const string& stroke_width) {
	this->stroke_width = stof(stroke_width);
}

void Figure::setTranslate(const string& translate) {
	stringstream ss(translate);
	float x, y;
	ss >> x >> y;
	transform.push_back({ Translate, Point(x, y) });
}

void Figure::setRotate(const string& rotate) {
	transform.push_back({ Rotate, Point(stof(rotate), 0) });
}

void Figure::setScale(const string& scale) {
	stringstream ss(scale);
	float x, y = 0;
	ss >> x >> y;
	if (y == 0) y = x;
	transform.push_back({ Scale, Point(x, y) });
}

void Figure::setTransform(const string& transform) {
	string line = transform;
	for (char& c : line) if (c == '(' || c == ',') c = ' ';

	stringstream ss(line);
	string attribute, value;
	while (ss >> attribute) {
		getline(ss, value, ')');
		if (attribute == "translate") setTranslate(value);
		else if (attribute == "rotate") setRotate(value);
		else if (attribute == "scale") setScale(value);
	}
}

void Figure::setAttribute(const string& line) {
	stringstream ss(line);
	string attribute, value;
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
		else setAttribute(attribute, value);
		//cout << "{" << attribute << "," << value << "}\n";
	}
}

void Figure::setAttribute(const Figure* other) {
	fill = other->fill;
	stroke = other->stroke;
	stroke_width = other->stroke_width;
	transform = other->transform;
}
// Virtual method
void Figure::setAttribute(const string& attribute, const string& value) {};
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

Figure* FigureFactory::getFigure(const string& figure) {
	if (figure == "rect") return new DrawableRectangle();
	if (figure == "ellipse") return new DrawableEllipse();
	if (figure == "circle") return new DrawableCircle();
	if (figure == "line") return new DrawableLine();
	if (figure == "polyline") return new DrawablePolyline();
	if (figure == "polygon") return new DrawablePolygon();
	if (figure == "text") return new DrawableText();
	if (figure == "path") return new DrawablePath();
	return NULL;
}

void FigureFactory::deleteInstance() {
	if (Instance != NULL)
		delete Instance;
	Instance = NULL;
}
//-----------END-OF-IMPLEMENTATION-----------//