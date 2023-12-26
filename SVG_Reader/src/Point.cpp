#include "Point.h"

// Constructors
Point::Point() :
	x(0), y(0)
{}

Point::Point(const float& x, const float& y) :
	x(x), y(y) 
{}

Point::Point(const Point& point) : 
	x(point.x), y(point.y)
{}