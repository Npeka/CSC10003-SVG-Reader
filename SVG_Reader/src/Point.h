#ifndef POINT_H
#define POINT_H

// class Point
class Point {
public:
	// Attribute
	float x;
	float y;

	// Constructor
	Point();
	Point(const float& x, const float& y);
	Point(const Point& point);
};
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class FPoint (+fill)
class FPoint : public Point {
public:
	// Attribute
	bool fill;

	// Constructor
	FPoint();
	FPoint(const float& x, const float& y);
	FPoint(const FPoint& fpoint);
};
//-----------END-OF-IMPLEMENTATION-----------//

#endif // !POINT_H

