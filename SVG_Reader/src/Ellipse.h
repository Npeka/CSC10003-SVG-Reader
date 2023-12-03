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
	void setCX(const std::string& cx);
	void setCY(const std::string& cy);
	void setRX(const std::string& rx);
	void setRY(const std::string& ry);

	// Virtual method
	void setAttribute(const std::string& attribute, const std::string& value) override;
	~Ellipse() override = default;
};

#endif // !ELLIPSE_H