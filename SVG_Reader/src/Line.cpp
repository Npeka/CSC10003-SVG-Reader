#include "Line.h"
#include "Point.h"

// Constructor
Line::Line() {
	x1 = y1 = x2 = y2 = 0;
}

// Set attribute
void Line::setX1(const string& x1) {
	this->x1 = stof(x1);
}

void Line::setY1(const string& y1) {
	this->y1 = stof(y1);
}

void Line::setX2(const string& x2) {
	this->x2 = stof(x2);
}

void Line::setY2(const string& y2) {
	this->y2 = stof(y2);
}

// Virtual method
void Line::setAttribute(const string& attribute, const string& value) {
	if (attribute == "x1") setX1(value);
	else if (attribute == "y1") setY1(value);
	else if (attribute == "x2") setX2(value);
	else if (attribute == "y2") setY2(value);
}

void Line::draw(sf::RenderWindow& window, sf::Transform& transform) {
	Point start = { x1, y1 };
	Point end = { x2, y2 };
	if (end.x < start.x) swap(start, end);

	float length = sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
	sf::RectangleShape line(sf::Vector2f(length, stroke_width));

	float angle = atan((end.y - start.y) / (end.x - start.x));
	angle = angle * 180 / M_PI;
	start.x += (stroke_width / 2) * cos(M_PI_2 - angle);
	start.y -= (stroke_width / 2) * sin(M_PI_2 - angle);

	line.rotate(angle);
	line.setPosition(start.x, start.y);
	line.setFillColor(stroke.sfColor());
	window.draw(line, transform);
}