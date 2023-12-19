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
	vector<pair<int, vector<float>>> transform;

public:
	Gradient();
	Gradient(const Gradient& other);
	void addStop(string& line);
	void setHref(string& href);
	void setTransform(string& transform);
	void setTranslate(string& translate);
	void setRotate(string& rotate);
	void setScale(string& scale);
	void setMatrix(string& matrix);
	void setElementAttributes(const string& attribute, string& value) override;
	vector<Stop> getColorOffset() const;
	bool getIsPercent() const;
	vector<pair<int, vector<float>>> getTransform() const;
};

Gradient* getGradient(const string& color);

#endif // !GRADIENT_H