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
	std::vector< std::pair<int, Point> > transform;
public:
	// Constructor
	Figure();
	Figure(const Figure& figure);

	// Set attribute
	void setFill(const std::string& fill);
	void setFillOpacity(const std::string& fill_opacity);
	void setStroke(const std::string& stroke);
	void setStrokeOpacity(const std::string& stroke_opacity);
	void setStrokeWidth(const std::string& stroke_width);
	void setTranslate(const std::string& translate);
	void setRotate(const std::string& rotate);
	void setScale(const std::string& scale);
	void setTransform(const std::string& transform);
	void setGroupAttributes(Figure* group);
	void setAttributes(const std::string& line);

	// Virtual method
	virtual void setAttributes(const std::string& attribute, const std::string& value) {};
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
	static Figure* getFigure(const std::string& figure);
	static void deleteInstance();
};
//-------------END-OF-DECLARATION------------//

#endif // !FIGURE_H



