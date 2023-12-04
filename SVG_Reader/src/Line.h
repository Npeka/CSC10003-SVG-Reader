#ifndef LINE_H
#define LINE_H

#include "Figure.h"

class Line : public Figure {
protected:
	Point p1; 
	Point p2;
public:
	// Constructor
	Line();
	Line(const Point& p1, const Point& p2);
	Line(const Line& line);

	// Set attribute
	void setX1(const std::string& x1);
	void setY1(const std::string& y1);
	void setX2(const std::string& x2);
	void setY2(const std::string& y2);

	// Virtual method
	void setAttributes(const std::string& attribute, const std::string& value) override;
	~Line() override = default;
};

#endif // !LINE_H