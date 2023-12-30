#include "Path.h"

// class Path
// Set attribute
void Path::setPath(string& line) {
	string value = line;
	for (char& c : value) if (c == ',') c = ' ';
	vector<int> pos;
	vector<string> subline;

	for (int i = 0; i < value.length(); i++) {
		if (isalpha(value[i]) && value[i] != 'e') pos.push_back(i);
		if (i == value.length() - 1) pos.push_back(i + 1);
	}

	for (int i = 0; i < pos.size() - 1; i++) {
		string substring = value.substr(pos[i], pos[i + 1] - pos[i]);
		subline.push_back(substring);
	}

	// prrse path
	for (int i = 0; i < subline.size(); i++) {
		std::stringstream ss(subline[i]);
		char cmd; ss >> cmd;

		// init n points
		int n = 0; char tcmd = toupper(cmd);
		switch (tcmd) {
		case 'H':case 'V':			n = 1; break;
		case 'M':case 'L':case 'T': n = 2; break;
		case 'S':case 'Q':			n = 4; break;
		case 'C':					n = 6; break;
		case 'A':					n = 7; break;
		}

		if (tcmd == 'Z') {
			path.push_back({ cmd, {} });
			continue;
		}

		float x;
		while (ss >> x) {
			// read n - 1 points
			vector<float> tmp = { x };
			for (int i = 0; i < n - 1; i++) {
				ss >> x;
				tmp.push_back(x);
			}

			// special case for h, v
			if (tcmd == 'H') tmp.push_back(0);
			else if (tcmd == 'V') tmp.insert(tmp.begin(), 0);

			// push vector of points into path
			path.push_back({ cmd, tmp });

			if (tcmd == 'M') {
				cmd = 'L';
				if (cmd == 'm') cmd = 'l';
			}
		}
	}
	
	//Add initial point and update l, v, h, V, H, c for each path element 
	Point end;
	for (int i = 0; i < path.size(); i++) {
		char cmd = path[i].first;
		vector<float>& point = path[i].second;

		if (cmd == 'M' || cmd == 'm') {
			if (cmd == 'm') {
				point[0] += end.x;
				point[1] += end.y;
			}
			end = { point[0], point[1] };
		}

		else if (cmd == 'Z' || cmd == 'z') {
			continue;
		}

		else if (cmd == 'H') point[1] = end.y;
		else if (cmd == 'V') point[0] = end.x;

		else if (string("SsTt").find(cmd) != string::npos) {
			char prevCmd = path[i - 1].first;
			vector<float> prevPoint = path[i - 1].second;
			Point prevEnd;

			if ((string("CcSs").find(prevCmd) != string::npos && (cmd == 'S' || cmd == 's')) ||
				(string("QqTt").find(prevCmd) != string::npos && (cmd == 'T' || cmd == 't'))) {
				int size = prevPoint.size();
				prevEnd = { prevPoint[size - 4], prevPoint[size - 3] };
			}
			else prevEnd = end;

			if (islower(cmd)) {
				point[0] += end.x;
				point[1] += end.y;
				if (cmd == 's') {
					point[2] += end.x;
					point[3] += end.y;
				}
			}
			Point controlPoint = { 2 * end.x - prevEnd.x, 2 * end.y - prevEnd.y };
			point.insert(point.begin(), { controlPoint.x, controlPoint.y});
		}

		else if (cmd == 'A' || cmd == 'a') {
			if (cmd == 'a') {
				point[5] += end.x;
				point[6] += end.y;
			}
		}
	
		// h - v - c - l 
		else  {
			if (islower(cmd)) {
				for (int i = 0; i < point.size(); i += 2) {
					point[i] += end.x;
					point[i + 1] += end.y;
				}
			}
		}

		if (cmd != 'M' && cmd != 'm') {
			point.insert(point.begin(), { end.x, end.y });
			end = { point[point.size() - 2], point[point.size() - 1] };
		}
	}

	/*for (auto p : path) {
		char cmd = p.first;
		std::
		<< cmd << ' ';
		for (auto x : p.second) std::cout << x << ' ';
		std::cout << std::endl;
	}*/
}

// Virtual method
void Path::setFigureAttributes(const string& attribute, string& value) {
	if (attribute == "d") setPath(value);
}
