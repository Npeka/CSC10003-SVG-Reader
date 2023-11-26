#include "Point.h"

//class Point
// Constructor
Point::Point() {
	x = y = 0;
}

Point::Point(const float& x, const float& y) {
	this->x = x;
	this->y = y;
}

Point::Point(const Point& point) {
	x = point.x;
	y = point.y;
}
//-----------END-OF-IMPLEMENTATION-----------//
/*
 
 
 
 */
// class FPoint
// Constructor
FPoint::FPoint() : Point() {
	fill = false;
}

FPoint::FPoint(const float& x, const float& y) : Point(x, y) {
	fill = false;
}

FPoint::FPoint(const FPoint& fpoint) {
	x = fpoint.x;
	y = fpoint.y;
	fill = fpoint.fill;
}
//-----------END-OF-IMPLEMENTATION-----------//