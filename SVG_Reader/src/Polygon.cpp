#include "Polygon.h"

// Constructor
Polygon::Polygon() = default;

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
	if (attribute == "points") setPoint(value);
}

void Polygon::draw(sf::RenderWindow& window, sf::Transform& transform) {
	int vertex = (int)point.size();
	sf::ConvexShape polygon(vertex);
	for (int i = 0; i < vertex; ++i)
		polygon.setPoint(i, sf::Vector2f(point[i].x, point[i].y));
	if (isfill) polygon.setFillColor(fill.sfColor());
	else polygon.setFillColor(sf::Color::Transparent);				// fill + fill-opacity
	polygon.setOutlineThickness(stroke_width);						// stroke-width
	polygon.setOutlineColor(stroke.sfColor());						
	window.draw(polygon, transform);
}