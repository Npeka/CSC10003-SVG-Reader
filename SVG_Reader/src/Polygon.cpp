#include "Polygon.h"

// Constructor
Polygon::Polygon(const Polygon& polygon) : Figure(polygon) {
	point = polygon.point;
}

// Set attribute
void Polygon::setPoint(const std::string& line) {
	std::string modifiedLine = line;
	COMMA_TO_SPACE(modifiedLine);
	std::stringstream ss(modifiedLine);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x, y));
	}
}

// Virtual method
void Polygon::setAttributes(const std::string& attribute, const std::string& value) {
	if (attribute == "points") setPoint(value);
}