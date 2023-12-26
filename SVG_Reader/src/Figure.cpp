#include "Figure.h"
#include "Drawable_Figure.h"

// class Ficgure
// Constructor
Figure::Figure() :
	fill(new RGB_Color()),
	stroke(new RGB_Color(0,0,0,0)),
	stroke_width(1)
{}

// Set attribute
void Figure::setFill(string& fill) {
    createColor(this->fill, fill);
}

void Figure::setFillOpacity(string& fill_opacity) {
	fill->setOpacity(fill_opacity);
}

void Figure::setStroke(string& stroke) {
	createColor(this->stroke, stroke);
}

void Figure::setStrokeOpacity(string& stroke_opacity) {
	stroke->setOpacity(stroke_opacity);
}

void Figure::setStrokeWidth(string& stroke_width) {
	check_exception("Figure", "stroke_width", this->stroke_width = stof(stroke_width));
}

void Figure::setGroupAttributes(Figure* group) {
	if (group != nullptr) {
		copyColor(fill, group->fill);
		copyColor(stroke, group->stroke);
		stroke_width = group->stroke_width;
	}
}

void Figure::setElementAttributes(const string& attribute, string& value) {
	if (attribute == "fill") setFill(value);
	else if (attribute == "stroke") setStroke(value);
	else if (attribute == "fill-opacity") setFillOpacity(value);
	else if (attribute == "stroke-opacity") setStrokeOpacity(value);
	else if (attribute == "stroke-width") setStrokeWidth(value);
	else if (attribute == "transform") setTransform(value);
	else setFigureAttributes(attribute, value);
}

Figure::~Figure() {
	dealocate(fill);
	dealocate(stroke);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class FigureFactory
// Private
	// Attribute
FigureFactory* FigureFactory::Instance = nullptr;

// Public
	// Method
FigureFactory* FigureFactory::getInstance() {
	if (Instance == nullptr)
		Instance = new FigureFactory();
	return Instance;
}

Figure* FigureFactory::getFigure(const string& figure) {
	if (figure == "rect") return new Drawable_Rectangle();
	if (figure == "ellipse") return new Drawable_Ellipse();
	if (figure == "circle") return new Drawable_Circle();
	if (figure == "line") return new Drawable_Line();
	if (figure == "polyline") return new Drawable_Polyline();
	if (figure == "polygon") return new Drawable_Polygon();
	if (figure == "text") return new Drawable_Text();
	if (figure == "path") return new Drawable_Path();
	return nullptr;
}

void FigureFactory::deleteInstance() {
	dealocate(Instance);
}
//-----------END-OF-IMPLEMENTATION-----------//