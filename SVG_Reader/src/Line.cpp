#include "Line.h"
#include "Point.h"

// Constructor
Line::Line() {
	p1 = p2 = { 0, 0 };
}

Line::Line(Point p1, Point p2) {
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

void Line::draw(sf::RenderWindow& window, sf::Transform& transform) {

	if (p2.x < p1.x) swap(p1, p2);

	float length = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	sf::RectangleShape line(sf::Vector2f(length, stroke_width));

	float angle = atan((p2.y - p1.y) / (p2.x - p1.x));
	angle = angle * 180 / M_PI;
	p1.x -= stroke_width / 2 * cos(angle);
	p1.y -= stroke_width / 2 * cos(angle);

	line.rotate(angle);
	line.setPosition(p1.x, p1.y);
	line.setFillColor(stroke.sfColor());
	line.setOutlineThickness(0);
	window.draw(line, transform);
}