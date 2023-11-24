#include "Line.h"
#include "Point.h"

// Constructor
Line::Line() {
	p1 = p2 = { 0, 0 };
}

Line::Line(const Point& p1, const Point& p2) {
	this->p1 = p1; 
	this->p2 = p2; 
}

// Set attribute
void Line::setX1(const string& x1) {
	this->p1.x = stof(x1);
}

void Line::setY1(const string& y1) {
	this->p1.y = stof(y1);
}

void Line::setX2(const string& x2) {
	this->p2.x = stof(x2);
}

void Line::setY2(const string& y2) {
	this->p2.y = stof(y2);
}

// Virtual method
void Line::setAttribute(const string& attribute, const string& value) {
	if (attribute == "x1") setX1(value);
	else if (attribute == "y1") setY1(value);
	else if (attribute == "x2") setX2(value);
	else if (attribute == "y2") setY2(value);
}

void Line::setSFigure() {}

void Line::draw(sf::RenderWindow& window, sf::Transform& transform) {
  Point start(p1);
	Point end(p2);
	if (end.x < start.x) swap(start, end);

	float length = sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
	line.setSize(sf::Vector2f(length, stroke_width));

	float angle = atan((end.y - start.y) / (end.x - start.x));
	angle = angle * 180 / M_PI;
	start.x += (stroke_width / 2) * cos(M_PI_2 - angle);
	start.y -= (stroke_width / 2) * sin(M_PI_2 - angle);

	line.rotate(angle);
	line.setPosition(start.x, start.y);
	line.setFillColor(stroke.sfColor());
	window.draw(line, transform);
}