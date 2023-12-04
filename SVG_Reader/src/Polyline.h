#ifndef POLYLINE_H
#define POLYLINE_H

#include "Figure.h"

class Polyline : public Figure {
protected:
	// Attribute
	std::vector <FPoint> fpoint;

	// Methods
	FPoint IntersectionPoint(const FPoint& p1, const FPoint& p2, const FPoint& p3, const FPoint& p4);
	bool checkIntersection(const FPoint& p1, const FPoint& p2, const FPoint& p3, const FPoint& p4);
	void updateListPoint(std::vector<FPoint>& FPoint);
	float getAngle(const FPoint& start, const FPoint& end);
public:
	// Constructor
	Polyline() = default;
	Polyline(const Polyline& polyline);

	// Set attribute
	void setPoint(const std::string& line);

	// Virtual method
	void setAttribute(const std::string& attribute, const std::string& value) override;
	~Polyline() override = default;
};

#endif // !POLYLINE_H


