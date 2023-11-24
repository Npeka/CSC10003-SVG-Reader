#include "Figure.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Line.h"
#include "Polyline.h"
#include "Polygon.h"
#include "Path.h"
#include "Text.h"

// class FigureFactory
// Private
// Attribute
FigureFactory* FigureFactory::Instance = NULL;
// Method
FigureFactory::FigureFactory() {};

// Public
// Method
FigureFactory* FigureFactory::getInstance() {
	if (Instance == NULL)
		Instance = new FigureFactory();
	return Instance;
}

Figure* FigureFactory::getFigure(const string& figure) {
	if (figure == "rect") return new Rectangle();
	if (figure == "ellipse") return new Ellipse();
	if (figure == "circle") return new Circle();
	if (figure == "line") return new Line();
	if (figure == "polyline") return new Polyline();
	if (figure == "polygon") return new Polygon();
	if (figure == "path") return new Path();
	if (figure == "text") return new Text();
	return NULL;
}

void FigureFactory::deleteInstance() {
	if (Instance != NULL)
		delete Instance;
	Instance = NULL;
}

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
		else setAttribute(attribute, value);
		if (attribute == "/") break;
		//cout << "{" << attribute << "," << value << "}\n";
	}
}

void Figure::setAttribute(const Figure* other) {
	fill = other->fill;
	stroke = other->stroke;
	stroke_width = other->stroke_width;
}

// Virtual method