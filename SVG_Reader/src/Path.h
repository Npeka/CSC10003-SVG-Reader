#ifndef PATH_H
#define PATH_H

#include "Figure.h"
#include "Line.h"

class Path : public Figure {
protected:
	vector<pair<char, vector<Point>>> path;
public:
	// Constructor 
	Path() = default; 
	Path(const Path& other);

	// Set attribute
	void setPath(const string& line);

	// Calculate method 
	float computeBinominal(int n, int k);
	vector<Point> CVertices(vector<Point> Position);

	// Virtual method 
	void setAttribute(const string& attribute, const string& value) override;
	~Path() override = default;
};


#endif // !PATH_H

