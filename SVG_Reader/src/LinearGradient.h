#ifndef LINEAR_GRADIENT_H
#define LINEAR_GRADIENT_H

#include "Gradient.h"

class LinearGradient : public Gradient {
private:
	Point p1;
	Point p2;

public:
	LinearGradient();
	LinearGradient(const LinearGradient& other);

	void setX1(string& x1);
	void setY1(string& y1);
	void setX2(string& x2);
	void setY2(string& y2);
	void setElementAttributes(const string& attribute, string& value) override;

	Point getP1() const;
	Point getP2() const;
};

#endif // !LINEAR_GRADIENT_H

