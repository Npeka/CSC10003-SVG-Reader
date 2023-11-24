#ifndef FIGURE_H
#define FIGURE_H
#include "Header.h"
#include "Color.h"

class Figure {
protected:
	Color fill;
	Color stroke;
	float stroke_width;

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
	void setAttribute(const string& line);
	void setAttribute(const Figure* other);

	// Virtual method
	virtual void setAttribute(const string& attribute, const string& value) {};
	virtual ~Figure() = default;
};

class FigureFactory {
private:
	// Attribute
	static FigureFactory* Instance;

	// Method
	FigureFactory();
public:
	static FigureFactory* getInstance();
	static Figure* getFigure(const string& figure);
	static void deleteInstance();
};

#endif // !FIGURE_H



