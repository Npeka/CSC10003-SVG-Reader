#ifndef LINE_H
#define LINE_H
#include "Figure.h"
#include "Point.h"

class Line : public Figure {
private:
	Point p1; 
	Point p2;
	sf::RectangleShape line;
public:
	// Constructor
	Line();
	Line(const Point& p1, const Point& p2);

	// Set attribute
	void setX1(const string& x1);
	void setY1(const string& y1);
	void setX2(const string& x2);
	void setY2(const string& y2);

	// Virtual method
	void setAttribute(const string& attribute, const string& value) override;
	void setSFigure() override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
	~Line() override = default;
};

#endif // !LINE_H