#include "Polyline.h"

// Private
// Method
Point Polyline::IntersectionPoint(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {

}

bool Polyline::checkIntersection(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
	
}

void Polyline::updateListPoint(vector<Point>& pointList) {
	
}

float Polyline::getAngle(const Point& start, const Point& end) {
	
}

sf::RectangleShape Polyline::Line(Point start, Point end, const float& x, const float& y) {
	
}

void Polyline::drawPolyline(vector<Point> PointArr, const float& x, const float& y, sf::RenderWindow& window, sf::Transform transform) {
	
}

void Polyline::drawPolyline2(vector<Point> listPoint, const float& x, const float& y, sf::RenderWindow& window, sf::Transform transform) {
	
}
  
// Public
// Constructor
Polyline::Polyline() {}

// Set attribute
void Polyline::setPoint(const string& line) {
	stringstream ss(line);
	float x, y; char ignore;
	while (ss >> x >> ignore >> y) {
		point.push_back(Point(x, y));
	}
}

// Virtual method
void Polyline::setAttribute(const string& attribute, const string& value) {
	
}

void Polyline::draw(sf::RenderWindow& window, sf::Transform& transform) {
	
}
