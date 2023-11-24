#ifndef POLYGON_H
#define POLYGON_H
#include "Figure.h"
#include "Point.h"

class Polygon : public Figure {
protected:
	vector <Point> point;
public:
	// Constructor
	Polygon();
	Polygon(const Polygon& polygon);

	// Set attribute
	void setPoint(const string& line);

	// Virtual method
	void setAttribute(const string& attribute, const string& value) override;
	~Polygon() override = default;
};

#endif // !POLYGON_H

