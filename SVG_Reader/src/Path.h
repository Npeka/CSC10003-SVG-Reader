#ifndef PATH_H
#define PATH_H

#include "Figure.h"
#include "Line.h"

class SubPath;

class Path : public Figure {
protected:
	vector< pair<char, vector<Point>> > path;
public:
	// Set attribute
	void setPath(const string& line);

	// test
	void drawCPath(vector<Point> point) {

	}
	void draw() {
		for (int i = 0; i < path.size(); i++) {
			char cmd = path[i].first;
			if (tolower(cmd) == 'C') drawCPath(path[i].second);
		}
	}
	//--end-test--//

	// Virtual method 
	void setAttribute(const string& attribute, const string& value) override;
	~Path() override = default;
};


#endif // !PATH_H

