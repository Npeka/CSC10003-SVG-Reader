#ifndef CIRCLE_H
#define CIRCLE_H

#include "Figure.h"

class Circle : public Figure {
protected:
	float cx;
	float cy;
	float r;
public:
	// Constructor
	Circle();
	Circle(const Circle& circle);

	// Set attribute
	void setCX(const string& cx);
	void setCY(const string& cy);
	void setR(const string& r);

	// Virtual method
	void setAttribute(const string& attribute, const string& value) override;
	~Circle() override = default;
};

#endif // !CIRCLE_H