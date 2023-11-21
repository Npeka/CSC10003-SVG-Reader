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

void Polygon::setSFigure() {
	int vertex = (int)point.size();
	polygon.setPointCount(vertex);
	for (int i = 0; i < vertex; ++i)
		polygon.setPoint(i, sf::Vector2f(point[i].x, point[i].y));
	polygon.setFillColor(fill.sfColor());							// fill + fill-opacity
	polygon.setOutlineThickness(stroke_width / 2);						// stroke-width
	polygon.setOutlineColor(stroke.sfColor());

	outline = polygon;
	outline.setOutlineThickness(-stroke_width / 2);						// stroke-width
	outline.setFillColor(sf::Color(0, 0, 0, 0));
};

void Polygon::draw(sf::RenderWindow& window, sf::Transform& transform) {
	window.draw(polygon, transform);
	window.draw(outline, transform);
}