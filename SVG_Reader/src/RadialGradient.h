#ifndef RADIAL_GRADIENT_H
#define RADIAL_GRADIENT_H

#include "Gradient.h"

class RadialGradient : public Gradient {
protected:
	float cx;
	float cy;
	float r;

public:
	RadialGradient();
	RadialGradient(const RadialGradient& other);

	void setCX(string& cx);
	void setCY(string& cy);
	void setR(string& r);
	void setElementAttributes(const string& attribute, string& value) override;

	float getCX() const;
	float getCY() const;
	float getR() const;
};

#endif // !RADIAL_GRADIENT_H
