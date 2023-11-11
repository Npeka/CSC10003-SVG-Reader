#include "Polygon.h"

// Constructor
Polygon::Polygon() {

}

// Set attribute
void Polygon::setPoint(const string& line) {
	stringstream ss(line);
	float x, y;
	char ignore;
	while (ss >> x >> ignore >> y) {
		point.push_back(Point(x, y));
	}
}

// Virtual method
void Polygon::setAttribute(const string& attribute, const string& value) {

}

void Polygon::draw(sf::RenderWindow& window, sf::Transform& transform) {

}