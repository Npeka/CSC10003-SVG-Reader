#ifndef LINE_H
#define LINE_H
#include "Figure.h"

class Line : public Figure
{
private:
	float x1;
	float y1;
	float x2;
	float y2;
public:
	// Constructor
	Line();

	// Set attribute
	void setX1(const string& x1);
	void setY1(const string& y1);
	void setX2(const string& x2);
	void setY2(const string& y2);

	// Virtual method
	void setAttribute(const string& attribute, const string& value) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
	~Line() override = default;
};

#endif // !LINE_H

