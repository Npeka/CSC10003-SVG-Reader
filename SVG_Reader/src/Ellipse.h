#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "Figure.h"

class Ellipse : public Figure {
protected:
	float cx;
	float cy;
	float rx;
	float ry;
public:
	// Constructor
	Ellipse();
	Ellipse(const Ellipse& ellipse);
	
	// Set attribute
	void setCX(const string& cx);
	void setCY(const string& cy);
	void setRX(const string& rx);
	void setRY(const string& ry);

	// Virtual method
	void setAttribute(const string& attribute, const string& value) override;
	~Ellipse() override = default;
};

#endif // !ELLIPSE_H