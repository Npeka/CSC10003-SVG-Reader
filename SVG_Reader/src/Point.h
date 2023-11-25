#ifndef POINT_H
#define POINT_H

class Point {
public:
	float x;
	float y;
	Point();
	Point(const float& x, const float& y);
	Point(const Point& point);
};

class FPoint : public Point {
public:
	bool fill;
	FPoint();
	FPoint(const float& x, const float& y);
	FPoint(const FPoint& fpoint);
};

#endif // !POINT_H

