#ifndef FIGURE_H
#define FIGURE_H

#include "SVG_Element.h"
#include "Point.h"
#include "RGB_Color.h"
#include "Transform.h"

// class Figure
class Figure : public SVG_Element , public Transform {
protected:
	Color* fill;
	Color* stroke;
	float stroke_width;

public:
	// Constructor
	Figure();

	// Set attribute
	void setFill(string& fill);
	void setFillOpacity(string& fill_opacity);
	void setStroke(string& stroke);
	void setStrokeOpacity(string& stroke_opacity);
	void setStrokeWidth(string& stroke_width);
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