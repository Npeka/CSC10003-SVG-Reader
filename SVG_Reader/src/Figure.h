#ifndef FIGURE_H
#define FIGURE_H
#include "Header.h"
#include "Color.h"

class Figure {
protected:
	Color fill;
	Color stroke;
	float stroke_width; // stroke.a
	// wait
	string stroke_linecap;
	string stroke_linejoin;
	string stroke_dasharray;
public:
	// Constructor
	Figure();

	// Set attribute
	void setFill(const string& fill);
	void setFillOpacity(const string& fill_opacity);
	void setStroke(const string& stroke);
	void setStrokeWidth(const string& stroke_width);
	void setStrokeOpacity(const string& stroke_opacity);
	void setStrokeLinecap(const string& stroke_linecap);
	void setStrokeLinejoin(const string& stroke_linejoin);
	void setStrokeDasharray(const string& stroke_dasharray);
	void setAttribute(const string& line);

	// Virtual method
	virtual void setAttribute(const string& attribute, const string& value) = 0;
	virtual void draw(sf::RenderWindow& window, sf::Transform& transform) = 0;
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



