#ifndef POLYGON_H
#define POLYGON_H
#include "Figure.h"
#include "Point.h"

class Polygon : public Figure
{
private:
	vector <Point> point;
public:
	// Constructor
	Polygon();

	// Set attribute
	void setPoint(const string& line);

	// Virtual method
	void setAttribute(const string& attribute, const string& value) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
	~Polygon() override = default;
};

#endif // !POLYGON_H

