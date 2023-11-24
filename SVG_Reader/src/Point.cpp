#include "Point.h"

Point::Point() {
	x = y = 0;
	fill = false;
}

Point::Point(const float& x, const float& y) {
	this->x = x;
	this->y = y;
	fill = false;
}

Point::Point(const Point& point) {
	x = point.x;
	y = point.y;
	fill = point.fill;
}