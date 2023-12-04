#ifndef PATH_H
#define PATH_H

#include "Figure.h"
#include "Line.h"

class Path : public Figure {
protected:
	std::vector<std::pair<char, std::vector<Point>>> path;
public:
	// Constructor 
	Path() = default; 
	Path(const Path& other);

	// Set attribute
	void setPath(const std::string& line);

	// Calculate method 
	float computeBinominal(int n, int k);
	std::vector<Point> CVertices(const std::vector<Point> Position);

	// Virtual method 
	void setAttribute(const std::string& attribute, const std::string& value) override;
	~Path() override = default;
};


#endif // !PATH_H

