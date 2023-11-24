#include "Polyline.h"

// Private
// Method
FPoint Polyline::IntersectionPoint(const FPoint& p1, const FPoint& p2, const FPoint& p3, const FPoint& p4) {
	FPoint IntersectionPoint;
	IntersectionPoint.x = ((p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x) - (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x)) / ((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));
	IntersectionPoint.y = ((p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x)) / ((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));
	IntersectionPoint.fill = true;
	return IntersectionPoint;
}

bool Polyline::checkIntersection(const FPoint& p1, const FPoint& p2, const FPoint& p3, const FPoint& p4) {
	if ((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x) == 0)
		return false;
	else
		return true;
}

void Polyline::updateListPoint(vector<FPoint>& pointList) {
	for (int i = 1; i < pointList.size(); i++) {
		if (checkIntersection(pointList[i - 1], pointList[i], pointList.front(), pointList.back())) {
			FPoint p = IntersectionPoint(pointList[i - 1], pointList[i], pointList.front(), pointList.back());
			pointList.insert(pointList.begin() + i, p);
			i++;
		}
	}
}

float Polyline::getAngle(const FPoint& start, const FPoint& end) {
	float angle = atan((end.y - start.y) / (end.x - start.x));
	angle = angle * 180 / M_PI;
	return angle;
}

// Public
// Constructor
Polyline::Polyline() {}

Polyline::Polyline(const Polyline& polyline) {
	fpoint = polyline.fpoint;
	lines = NULL;
	joint = NULL;
}

// Set attribute
void Polyline::setPoint(const string& line) {
	stringstream ss(line);
	float x, y; char ignore;
	while (ss >> x >> ignore >> y) {
		fpoint.push_back(FPoint(x, y));
	}
}

// Virtual method
void Polyline::setAttribute(const string& attribute, const string& value) {
	if (attribute == "points") setPoint(value);
}
