#include "Path.h"

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

		// in this case path.second contain array of Point
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

		// H, V, h and v base on previous point so we store it one by one 
		else if (cmd == 'h' || cmd == 'v' || cmd == 'H' || cmd == 'V') {
			while (ss >> x) {
				std::vector<Point> tmp(1);
				if (cmd == 'h' || cmd == 'H')
					tmp[0] = { x, 0 };
				if (cmd == 'v' || cmd == 'V')
					tmp[0] = { 0, x };
				path.push_back({ cmd, tmp });
			}
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
			if (i == 0) end = { 0,0 };
			else end = path[i - 1].second[path[i - 1].second.size() - 1];
			// process 'm' case 
			if (cmd == 'm') {
				path[i].second[0].x += end.x; 
				path[i].second[0].y += end.y;
				for (int j = 1; j < path[i].second.size(); j++) {
					path[i].second[j].x += path[i].second[j - 1].x;
					path[i].second[j].y += path[i].second[j - 1].y;
				}
			}
			initialSubpath = path[i].second.back();
		}

		if (cmd == 'C' || cmd == 'L') {
			path[i].second.insert(path[i].second.begin(), end); // đưa point cuối của vector trước vào đầu vector sau
		}

		else if (cmd == 'h' || cmd == 'v' || cmd == 'c' || cmd == 'l' || cmd == 'H' || cmd == 'V') {
			path[i].second.insert(path[i].second.begin(), end);
			for (int j = 1; j < path[i].second.size(); j++) {
				path[i].second[j].x += end.x;
				path[i].second[j].y += end.y;
			}
		}

		// vector<Point> in z path just contain the initialPoint of all path
		else if (cmd == 'Z' || cmd == 'z') {
			path[i].second.push_back(initialSubpath);
			path[i].second.push_back(end);
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

// Virtual method
void Path::setAttribute(const std::string& attribute, const std::string& value) {
	if (attribute == "d") setPath(value);
}
