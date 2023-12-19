#ifndef GRADIENT_H
#define GRADIENT_H

#include "Point.h"
#include "RGB_Color.h"

class Stop {
private:
	RGB_Color color;
	float offset;

public:
	Stop();
	~Stop() = default;
	void setColor(string& color);
	void setOffset(string& offset);
	RGB_Color getColor();
	float getOffset();
};

class Gradient : public Color {
protected:
	vector<Stop> ColorOffset;
	bool isPercent;

public:
	Gradient();
	Gradient(const Gradient& other);
	void addStop(string& line);
	vector<Stop> getColorOffset() const;
	bool getIsPercent() const;

};

Gradient* getGradient(const string& color);

#endif // !GRADIENT_H