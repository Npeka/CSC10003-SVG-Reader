#include "Polyline.h"

// Set attribute
void Polyline::setPoint(string& line) {
	COMMA_TO_SPACE(line);
	std::stringstream ss(line);
	float x, y; 
	while (ss >> x >> y) {
		points.push_back(Point(x, y));
	}
}

// Virtual method
void Polyline::setFigureAttributes(const string& attribute, string& value) {
	if (attribute == "points") setPoint(value);
}

Polyline::~Polyline() {
	points.clear();
}
