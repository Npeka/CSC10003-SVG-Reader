#ifndef FIGURE_H
#define FIGURE_H

#include "SVG_Element.h"
#include "Point.h"
#include "RGB_Color.h"
#include "LinearGradient.h"
#include "RadialGradient.h"

// class Figure
class Figure : public SVG_Element {
public:
	Color* fill;
	Color* stroke;
	float stroke_width;
	vector<pair<int, Point>> transform;

public:
	// Constructor
	Figure();

	// Set attribute
	void setFill(string& fill);
	void setFillOpacity(string& fill_opacity);
	void setStroke(string& stroke);
	void setStrokeOpacity(string& stroke_opacity);
	void setStrokeWidth(string& stroke_width);
	void setTranslate(string& translate);
	void setRotate(string& rotate);
	void setScale(string& scale);
	void setTransform(string& transform);
	void setStyle(string& style);
	void setGroupAttributes(Figure* group);
	void setElementAttributes(const string& attribute, string& value) override final;

	// Virtual method
	virtual void setFigureAttributes(const string& attribute, string& value) {};
	virtual ~Figure();
};
//-------------END-OF-DECLARATION------------//
/*



*/
// class FicgureFactory
class FigureFactory {
private:
	// Attribute
	static FigureFactory* Instance;

	// Method
	FigureFactory() = default;
public:
	static FigureFactory* getInstance();
	static Figure* getFigure(const string& figure);
	static void deleteInstance();
};
//-------------END-OF-DECLARATION------------//

#endif // !FIGURE_H