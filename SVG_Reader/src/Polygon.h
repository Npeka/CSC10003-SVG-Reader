#ifndef POLYGON_H
#define POLYGON_H

#include "Figure.h"

class Polygon : public Figure {
protected:
	std::vector <Point> point;
public:
	// Constructor
	Polygon() = default;
	Polygon(const Polygon& polygon);

	// Set attribute
	void setPoint(const std::string& line);

	// Virtual method
	void setAttribute(const std::string& attribute, const std::string& value) override;
	~Polygon() override = default;
};

#endif // !POLYGON_H

