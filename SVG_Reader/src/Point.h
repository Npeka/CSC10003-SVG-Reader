#ifndef POINT_H
#define POINT_H

class Point {
public:
	float x;
	float y;
	bool fill;
	Point();
	Point(const float& x, const float& y);
	Point(const Point& point);
};

#endif // !POINT_H

