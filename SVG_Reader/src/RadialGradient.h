#ifndef RADIAL_GRADIENT_H
#define RADIAL_GRADIENT_H

#include "Gradient.h"

class RadialGradient : public Gradient {
protected:
	float cx;
	float cy;
	float r;
	float fx;
	float fy;
	float fr;

public:
	RadialGradient();
	RadialGradient(const RadialGradient& other);

	void setCX(string& cx);
	void setCY(string& cy);
	void setR(string& r);
	void setFX(string& fx);
	void setFY(string& fy);
	void setFR(string& fr);
	void setElementAttributes(const string& attribute, string& value) override;

	float getCX() const;
	float getCY() const;
	float getR() const;
};

#endif // !RADIAL_GRADIENT_H
