#ifndef POLYLINE_H
#define POLYLINE_H
#include "Figure.h"
#include "Point.h"

class Polyline : public Figure
{
private:
	// Attribute
	vector <Point> point;
	sf::RectangleShape* lines;
	sf::ConvexShape* joint;

	// Method
	Point IntersectionPoint(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
	bool checkIntersection(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
	void updateListPoint(vector<Point>& point);
	float getAngle(const Point& start, const Point& end);
	sf::RectangleShape Line(Point start, Point end);
	void drawPolyline(sf::RenderWindow& window, sf::Transform transform);
	void drawPolyline2(sf::RenderWindow& window, sf::Transform transform);
public:
	// Constructor
	Polyline();
	
	// Set attribute
	void setPoint(const string& line);

	// Virtual method
	void setAttribute(const string& attribute, const string& value) override;
	void setSFigure() override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;

	~Polyline() override = default;
};

#endif // !POLYLINE_H


