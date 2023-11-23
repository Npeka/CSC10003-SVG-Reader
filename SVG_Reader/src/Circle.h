#ifndef CIRCLE_H
#define CIRCLE_H
#include "Figure.h"

class Circle : public Figure {
private:
	float cx;
	float cy;
	float r;
	sf::CircleShape circle;
	sf::CircleShape outline;

public:
	// Constructor
	Circle();

	// Set attribute
	void setCX(const string& cx);
	void setCY(const string& cy);
	void setR(const string& r);

	// Virtual method
	void setAttribute(const string& attribute, const string& value) override;
	void setSFigure() override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
	~Circle() override = default;

	
};

#endif // !CIRCLE_H