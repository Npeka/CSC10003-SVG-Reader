﻿#include "Path.h"

// class Path
// Set attribute
void Path::setPath(const std::string& line) {
	std::string value = line;
	for (char& c : value) if (c == ',') c = ' ';
	std::vector<int> pos;
	std::vector<std::string> subline;


	for (int i = 0; i < value.length(); i++) {
		if (isalpha(value[i])) pos.push_back(i);
		if (i == value.length() - 1) pos.push_back(i + 1);
	}

	for (int i = 0; i < pos.size() - 1; i++) {
		std::string substring = value.substr(pos[i], pos[i + 1] - pos[i]);
		subline.push_back(substring);
	}

	char cmd;
	float x, y;
	Point end;
	// đọc file đưa vô vector
	for (int i = 0; i < subline.size(); i++) {
		std::stringstream ss(subline[i]);
		ss >> cmd;

		// in this case path.second contain array of Point, we just need the end one
		if (cmd == 'M' || cmd == 'm') {
			std::vector<Point> tmp;
			while (ss >> x >> y) {
				Point point{ x, y };
				tmp.push_back(point);
			}
			path.push_back({ cmd, tmp });
		}

		// in this case, each 3 Point we set into an path element
		else if (cmd == 'C' || cmd == 'c') {
			while (ss >> x >> y) {
				std::vector<Point> tmp(3);
				tmp[0] = { x, y };
				for (int i = 1; i < 3; i++) {
					ss >> x >> y;
					tmp[i] = { x, y };
				}
				path.push_back({ cmd, tmp });
			}
		}

		// in this case, each 1 Point we set into an path element
		else if (cmd == 'L' || cmd == 'l') {
			while (ss >> x >> y) {
				std::vector<Point> tmp(1);
				tmp[0] = { x, y };
				path.push_back({ cmd, tmp });
			}
		}

		// h and v base on previous point so we store it one by one 
		else if (cmd == 'h' || cmd == 'v') {
			while (ss >> x) {
				std::vector<Point> tmp(1);
				if (cmd == 'h')
					tmp[0] = { x, 0 };
				if (cmd == 'v')
					tmp[0] = { 0, x };
				path.push_back({ cmd, tmp });
			}
		}

		// H and V base on the initial point (e.g: H 10 5 20), we store it into an vector
		else if (cmd == 'H' || cmd == 'V') {
			std::vector<Point> tmp;
			float minPoint = FLT_MAX;
			float maxPoint = FLT_MIN;

			while (ss >> x) {
				if (x < minPoint) minPoint = x;
				if (x > maxPoint) maxPoint = x;
			}

			Point point1;
			Point point2;
			if (cmd == 'H') {
				point1 = Point{ minPoint, 0 };
				point2 = Point{ maxPoint, 0 };
			}
			if (cmd == 'V') {
				point1 = Point{ 0, minPoint };
				point2 = Point{ 0, maxPoint };
			}
			tmp.push_back(point1);
			tmp.push_back(point2);

			path.push_back({ cmd, tmp });
		}

		// Add M point into tmp for later processing 
		else if (cmd == 'Z' || cmd == 'z') {
			std::vector<Point> tmp;
			path.push_back({ cmd, tmp });
		}
	}

	//Add initial point and update l, v, h, V, H, c for each path element 
	Point initialSubpath;
	for (int i = 0; i < path.size(); i++) {
		cmd = path[i].first;
		Point end;

		if (cmd != 'M' && cmd != 'm') {
			end = path[i - 1].second[path[i - 1].second.size() - 1];
		}
		else {
			initialSubpath = path[i].second.back();
		}

		if (cmd == 'C' || cmd == 'L') {
			path[i].second.insert(path[i].second.begin(), end); // đưa point cuối của vector trước vào đầu vector sau
		}

		else if (cmd == 'H') {
			path[i].second.insert(path[i].second.begin(), end);
			for (int j = 1; j < path[i].second.size(); j++) {
				path[i].second[j].y = end.y;
			}
		}

		else if (cmd == 'V') {
			path[i].second.insert(path[i].second.begin(), end);
			for (int j = 1; j < path[i].second.size(); j++) {
				path[i].second[j].x = end.x;
			}
		}

		else if (cmd == 'h' || cmd == 'v' || cmd == 'c' || cmd == 'l') {
			path[i].second.insert(path[i].second.begin(), end);
			for (int j = 1; j < path[i].second.size(); j++) {
				path[i].second[j].x += end.x;
				path[i].second[j].y += end.y;
			}
		}

		// vector<Point> in z path just contain the initialPoint of all path
		else if (cmd == 'Z' || cmd == 'z') {
			path[i].second.insert(path[i].second.begin(), end);
			path[i].second.push_back(initialSubpath);
		}

		//cout << cmd << endl;
		//for (int j = 0; j < path[i].second.size(); j++) {
		//	cout << path[i].second[j].x << " " << path[i].second[j].y << endl;
		//}
	}	
}

//Constructor 
Path::Path(const Path& other) : Figure(other) {
	this->path = other.path; 
}

// Calculate method 
float Path::computeBinominal(int n, int k) {
	double value = 1.0;

	for (int i = 1; i <= k; i++)
	{

		value = value * ((n + 1 - i) / i);
	}

	if (n == k) {
		value = 1;
	}

	return value;
}

std::vector<Point> Path::CVertices(const std::vector<Point> Position) {
	std::vector<Point> CurvePositions;

	int n = Position.size() - 1;

	for (double t = 0.0; t <= 1.0; t += 0.001)
	{
		Point CurvePos = { 0.0, 0.0 };

		for (int i = 0; i <= n; ++i) {
			CurvePos.x += computeBinominal(n, i) * pow((1 - t), (n - i)) * pow(t, i) * Position[i].x;
			CurvePos.y += computeBinominal(n, i) * pow((1 - t), (n - i)) * pow(t, i) * Position[i].y;
		}

		CurvePositions.push_back(CurvePos);
	}
	return CurvePositions;
}

// Virtual method
void Path::setAttributes(const std::string& attribute, const std::string& value) {
	if (attribute == "d") setPath(value);
}
