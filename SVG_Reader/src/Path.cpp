#include "Path.h"

// class Path
// Set attribute
void Path::setPath(const string& line) {
	string value = line;
	for (char& c : value) if (c == ',') c = ' ';

	vector<int> pos;
	vector<string> subline;

	for (int i = 0; i < value.length(); i++) {
		if (isalpha(value[i])) pos.push_back(i);
		if (i == value.length() - 1) pos.push_back(i + 1);
	}

	for (int i = 0; i < pos.size() - 1; i++) {
		string substring = line.substr(pos[i], pos[i + 1] - pos[i]);
		subline.push_back(substring);
		cout << substring << endl;
	}
	 // M 10 20 30 40 C 10 30 10 10 20 10 80 78
	char cmd;
	float x, y;
	Point end;
	// đọc file đưa vô vector
	for (int i = 0; i < subline.size(); i++) {
		stringstream ss(subline[i]);
		ss >> cmd;
		if (cmd == 'M' || cmd == 'm') {
			ss >> x >> y;
			vector<Point> tmp(1);
			tmp[0] = { x, y };
			path.push_back({ cmd, tmp });
		}
		else if (cmd == 'C' || cmd == 'c') {
			while (ss >> x >> y) {
				vector<Point> tmp(3);
				tmp[0] = { x, y };
				for (int i = 1; i < 3; i++) {
					ss >> x >> y;
					tmp[i] = { x, y };
				}
				path.push_back({ cmd, tmp });
			}
		}
		else if (cmd == 'H' || cmd == 'h') {
			float x;
			while (ss >> x) {
				vector<Point> tmp(1);
				tmp[0] = { x, 0 };
				path.push_back({ cmd, tmp });
			}
		}
		else if (cmd == 'L' || cmd == 'L') {
			float y;
			while (ss >> y) {
				vector<Point> tmp(1);
				tmp[0] = { 0, y };
				path.push_back({ cmd, tmp });
			}
		}
		else if (cmd == 'Z' || cmd == 'z') {
			vector<Point> tmp;
			path.push_back({ cmd, tmp });
		}
	}

	// thêm point cho đủ tương ứng với mỗi loại
	cout << "====================" << endl;
	for (int i = 1; i < path.size(); i++) {
		char cmd = path[i].first;
		Point end = path[i - 1].second[path[i - 1].second.size() - 1];

		if (cmd == 'M' || cmd == 'm') {
			path[i].second.insert(path[i].second.begin(), end); // đưa point cuối của vector trước vào đầu vector sau
		}
		else if (cmd == 'C' || cmd == 'c') {
			path[i].second.insert(path[i].second.begin(), end);
		}
		else if (cmd == 'H' || cmd == 'h') {

		}
		else if (cmd == 'L' || cmd == 'L') {

		}
		else if (cmd == 'Z' || cmd == 'z') {
			path[i].second.push_back(end);
			path[i].second[0] = path[0].second[path[i].second.size() - 1];
		}

		cout << cmd << endl;
		for (int j = 0; j < path[i].second.size(); j++) {
			cout << path[i].second[j].x << " " << path[i].second[j].y << endl;
		}
	}
}

// Virtual method
void Path::setAttribute(const string& attribute, const string& value) {
	if (attribute == "d") setPath(value);
}
