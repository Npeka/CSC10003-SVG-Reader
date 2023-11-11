#ifndef POLYLINE_H
#define POLYLINE_H
#include "Figure.h"
#include "Point.h"

class Polyline : public Figure
{
private:
	// Attribute
	vector <Point> point;

	// Method
	Point IntersectionPoint(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
	bool checkIntersection(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
	void updateListPoint(vector<Point>& PointArr);
	float getAngle(const Point& start, const Point& end);
	sf::RectangleShape Line(Point start, Point end, const float& x, const float& y);
	void drawPolyline(vector <Point> PointArr, const float& x, const float& y, sf::RenderWindow& window, sf::Transform transform);
	void drawPolyline2(vector <Point> listPoint, const float& x, const float& y, sf::RenderWindow& window, sf::Transform transform);
public:
	// Constructor
	Polyline();
	
	// Set attribute
	void setPoint(const string& line);

	// Virtual method
	void setAttribute(const string& attribute, const string& value) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
	~Polyline() override = default;
};

#endif // !POLYLINE_H


