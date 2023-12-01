#ifndef FIGURE_H
#define FIGURE_H

#include "Header.h"
#include "Color.h"
#include "Point.h"

// class Ficgure
class Figure {
protected:
	Color fill;
	Color stroke;
	float stroke_width;
	vector< pair<int, Point> > transform;
public:
	// Constructor
	Figure();
	Figure(const Figure& figure);

	// Set attribute
	void setFill(const string& fill);
	void setFillOpacity(const string& fill_opacity);
	void setStroke(const string& stroke);
	void setStrokeOpacity(const string& stroke_opacity);
	void setStrokeWidth(const string& stroke_width);
	void setTranslate(const string& translate);
	void setRotate(const string& rotate);
	void setScale(const string& scale);
	void setTransform(const string& transform);
	void setGroup(const Figure* other);
	void setAttribute(const string& line);

	// Virtual method
	virtual void setAttribute(const string& attribute, const string& value);
	virtual ~Figure() = default;
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



