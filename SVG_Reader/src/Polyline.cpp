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
	if (abs((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x)) < 0.01)
		return false;
	else
		return true;
}

void Polyline::findCornerPoint(float& min_x, float& max_x, float& min_y, float& max_y) {
	for (int i = 0; i < fpoint.size(); i++) {
		if (fpoint[i].x < min_x) min_x = fpoint[i].x;
		if (fpoint[i].x > max_x) max_x = fpoint[i].x;
		if (fpoint[i].x < min_y) min_y = fpoint[i].y;
		if (fpoint[i].x > max_y) max_y = fpoint[i].y;
	}
}

void Polyline::updateListPoint(vector<FPoint>& pointList) {
	float min_x = INT_MAX;
	float min_y = INT_MAX;
	float max_x = INT_MIN;
	float max_y = INT_MIN;
	findCornerPoint(min_x, max_x, min_y, max_y);

	for (int i = 1; i < pointList.size(); i++) {
		if (checkIntersection(pointList[i - 1], pointList[i], pointList.front(), pointList.back())) {
			FPoint p = IntersectionPoint(pointList[i - 1], pointList[i], pointList.front(), pointList.back());
			bool add = true;
			for (int j = 0; j < pointList.size(); j++) {
				if (abs(p.x - pointList[j].x) < 0.1 && abs(p.y - pointList[j].y) < 0.1 && p.fill == pointList[j].fill) {
					add = false;
					break;
				}
			}

			if (p.x > max_x || p.x < min_x || p.y > max_y || p.y < min_y) {
				add = false;
			}

			if (p.x > max(pointList[i].x, pointList[i - 1].x) || p.x < min(pointList[i].x, pointList[i - 1].x) || p.y > max(pointList[i].y, pointList[i - 1].y) || p.y < min(pointList[i].y, pointList[i - 1].y)) {
				add = false;
			}

			if (add) {
				pointList.insert(pointList.begin() + i, p);
				i++;
			}
		}
	}
}

float Polyline::getAngle(const FPoint& start, const FPoint& end) {
	float angle;
	if (end.x - start.x == 0) {
		if (end.y < start.y)
			angle = 270;
		else
			angle = 90;
	}
	else {
		angle = atan((end.y - start.y) / (end.x - start.x));
		angle = angle * 180 / M_PI;

		if (end.x < start.x)
			angle += 180;
		else {
			if (end.y < start.y)
				angle += 360;
		}
	}
	return angle;
}

// Public
// Constructor
Polyline::Polyline(const Polyline& polyline) : Figure(polyline) {
	fpoint = polyline.fpoint;
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
