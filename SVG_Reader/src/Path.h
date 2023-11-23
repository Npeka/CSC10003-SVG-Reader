#ifndef PATH_H
#define PATH_H

#include "Figure.h"
#include "Point.h"
#include "Circle.h"
#include "Ellipse.h" 
#include "Line.h" 
#include "Polygon.h"
#include "Rectangle.h" 
#include "Text.h" 

class SubPath;

class Path : public Figure {
private:
	vector <SubPath*> path;
public:
	// Set attribute
	void setPath(const string& line);

	// Virtual method 
	void setAttribute(const string& attribute, const string& value) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
	~Path() override;

	void setSFigure() {};
};

class SubPath
{
protected:
	Point initialPoint; 
	char command;

public:
	// Constructor
	SubPath();

	// Set attribute
	void setCommand(const char& command);

	// Calculate method 
	float computeBinominal(int n, int k);
	vector<Point> BezierCurveVertices(vector<Point> Position);

	// Virtual method
	virtual Point getEndPoint() = 0;
	virtual void setAttribute(const string& value, Point initialPoint) = 0;
	virtual void draw(sf::RenderWindow& window, sf::Transform& transform) = 0;
};

class SubPathFactory {
private:
	// Attribute
	static SubPathFactory* Instance;

	// Method
	SubPathFactory();
public:
	static SubPathFactory* getInstance();
	static SubPath* getSubPath(const char& command);
	static void deleteInstance();
};

class MPath : public SubPath {
private:
	Point move;
public:
	MPath();
	MPath(const float& x, const float& y);
	Point getEndPoint();
	void setAttribute(const string& value, Point initialPoint) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class LPath : public SubPath {
private:
	Point lineTo; 
public:
	Point getEndPoint();
	void setAttribute(const string& value, Point initialPoint) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class lPath : public SubPath {
private:
	Point lineTo;
public:
	Point getEndPoint();
	void setAttribute(const string& value, Point initialPoint) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};   

class HPath : public SubPath {
private:
	float px;
public:
	Point getEndPoint();
	void setAttribute(const string& value, Point initialPoint) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class VPath : public SubPath {
private:
	float py;
public:
	Point getEndPoint();
	void setAttribute(const string& value, Point initialPoint) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class hPath : public SubPath {
private:
	float px;
public:
	Point getEndPoint();
	void setAttribute(const string& value, Point initialPoint) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class vPath : public SubPath {
private:
	float py;
public:
	Point getEndPoint();
	void setAttribute(const string& value, Point initialPoint) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class CPath : public SubPath {
private: 
	vector<Point> point;

public:
	Point getEndPoint();
	void setAttribute(const string& value, Point initialPoint) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class cPath : public SubPath {
private:
	vector<Point> point;

public:
	Point getEndPoint();
	void setAttribute(const string& value, Point initialPoint) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class ZPath : public SubPath {
private:
	Point initialSubpath; 
public:
	ZPath(){}
	Point getEndPoint();
	void setAttribute(const string& value, Point initialPoint) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

#endif // !PATH_H

