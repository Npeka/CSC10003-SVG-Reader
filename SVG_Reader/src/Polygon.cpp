#include "Polygon.h"

// Constructor
Polygon::Polygon(const Polygon& polygon) : Figure(polygon) {
	point = polygon.point;
}

// Set attribute
void Polygon::setPoint(const string& line) {
	string modifiedLine = line;
	COMMA_TO_SPACE(modifiedLine);
	stringstream ss(modifiedLine);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x, y));
	}
}

// Virtual method
void Polygon::setAttribute(const string& attribute, const string& value) {
	if (attribute == "points") setPoint(value);
}