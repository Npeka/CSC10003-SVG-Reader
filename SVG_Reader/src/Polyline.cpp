#include "Polyline.h"

// Private
// Method
Point Polyline::IntersectionPoint(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
	Point IntersectionPoint;
	IntersectionPoint.x = ((p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x) - (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x)) / ((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));
	IntersectionPoint.y = ((p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x)) / ((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));
	IntersectionPoint.fill = true;
	return IntersectionPoint;
}

bool Polyline::checkIntersection(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
	if ((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x) == 0)
		return false;
	else
		return true;
}

void Polyline::updateListPoint(vector<Point>& pointList) {
	for (int i = 1; i < pointList.size(); i++) {
		if (checkIntersection(pointList[i - 1], pointList[i], pointList.front(), pointList.back())) {
			Point p = IntersectionPoint(pointList[i - 1], pointList[i], pointList.front(), pointList.back());
			pointList.insert(pointList.begin() + i, p);
			i++;
		}
	}
}

float Polyline::getAngle(const Point& start, const Point& end) {
	float angle = atan((end.y - start.y) / (end.x - start.x));
	angle = angle * 180 / M_PI;
	return angle;
}

sf::RectangleShape Polyline::Line(Point start, Point end) {
	if (end.x < start.x) swap(start, end);

	float length = sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
	sf::RectangleShape line(sf::Vector2f(length, stroke_width));

	float angle = atan((end.y - start.y) / (end.x - start.x));
	angle = angle * 180 / M_PI;

	line.rotate(angle);
	line.setOutlineThickness(0);
	line.setPosition(start.x - stroke_width / 2, start.y - stroke_width / 2);
	return line;
}

void Polyline::drawPolyline(vector<Point> PointArr, sf::RenderWindow& window, sf::Transform transform) {
	sf::RectangleShape* lines = new sf::RectangleShape[PointArr.size()];
	for (int i = 0; i < PointArr.size() - 1; i++) {
		lines[i] = Line(PointArr[i], PointArr[i + 1]);
		lines[i].setFillColor(stroke.sfColor());
		window.draw(lines[i], transform);

		if (i > 0 && i < PointArr.size() - 1) {
			float angle1 = getAngle(PointArr[i - 1], PointArr[i]) * M_PI / 180;
			float angle2 = getAngle(PointArr[i], PointArr[i + 1]) * M_PI / 180;

			float p3_x = PointArr[i].x - stroke_width * cos(M_PI_2 - (angle1 + angle2) / 2) / cos((angle1 - angle2) / 2);
			float p3_y = PointArr[i].y + stroke_width * sin(M_PI_2 - (angle1 + angle2) / 2) / cos((angle1 - angle2) / 2);

			sf::ConvexShape joint, clear, fillArea;
			joint.setPointCount(4);

			joint.setPoint(0, sf::Vector2f(PointArr[i].x, PointArr[i].y));
			joint.setPoint(1, sf::Vector2f(PointArr[i].x - stroke_width * sin(angle1), PointArr[i].y + stroke_width * cos(angle1)));
			joint.setPoint(2, sf::Vector2f(p3_x, p3_y));
			joint.setPoint(3, sf::Vector2f(PointArr[i].x - stroke_width * sin(angle2), PointArr[i].y + stroke_width * cos(angle2)));

			joint.setOutlineThickness(0);
			joint.setFillColor(sf::Color(stroke.sfColor()));
			joint.setPosition(- stroke_width / 2, - stroke_width / 2);

			clear = joint;
			clear.setFillColor(sf::Color(255, 255, 255));

			fillArea = joint;
			fillArea.setFillColor(fill.sfColor());

			window.draw(clear, transform);
			window.draw(fillArea, transform);
			window.draw(joint, transform);
		}
	}
}

void Polyline::drawPolyline2(vector<Point> listPoint, sf::RenderWindow& window, sf::Transform transform) {
	vector <Point> temp = point;
	updateListPoint(listPoint);
	int start, end;
	for (int i = 0; i < listPoint.size(); i++) {
		if (listPoint[i].fill == true) {
			start = i;
			for (int j = i + 1; j < listPoint.size(); j++) {
				if (listPoint[j].fill == true) {
					end = j;
					break;
				}
				else if (listPoint[j].fill == false && j == listPoint.size() - 1) {
					drawPolyline(temp, window, transform);
					return;
				}
			}

			sf::ConvexShape fillArea;
			for (int k = 0; k < end - start + 1; k++) {
				fillArea.setPointCount(end - start + 1);
				fillArea.setPoint(k, sf::Vector2f(listPoint[start + k].x, listPoint[start + k].y));
			}

			fillArea.setOutlineThickness(0);
			fillArea.setPosition( - stroke_width / 2,  - stroke_width / 2);
			fillArea.setFillColor(fill.sfColor());
			window.draw(fillArea, transform);
			i = end - 1;
		}
	}
	drawPolyline(temp, window, transform);
}

// Public
// Constructor
Polyline::Polyline() {}

// Set attribute
void Polyline::setPoint(const string& line) {
	stringstream ss(line);
	float x, y; char ignore;
	while (ss >> x >> ignore >> y) {
		point.push_back(Point(x, y));
	}
}

// Virtual method
void Polyline::setAttribute(const string& attribute, const string& value) {
	if (attribute == "points") setPoint(value);
}

void Polyline::draw(sf::RenderWindow& window, sf::Transform& transform) {
	drawPolyline2(point, window, transform);
}
