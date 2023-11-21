#ifndef PATH_H
#define PATH_H
#include "Figure.h"
#include "Point.h"

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
	char command;
public:
	// Constructor
	SubPath();

	// Set attribute
	void setCommand(const char& command);

	// Virtual method
	virtual void setAttribute(const string& value) = 0;
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
	void setAttribute(const string& value) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class LPath : public SubPath {
private:
	vector<Point> point;
public:
	void setAttribute(const string& value) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class HPath : public SubPath {
private:
	float px;
public:
	void setAttribute(const string& value) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class VPath : public SubPath {
private:
	float px;
public:
	void setAttribute(const string& value) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class CPath : public SubPath {
private:
	vector<Point> point;
public:
	void setAttribute(const string& value) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class SPath : public SubPath {
private:
	vector<Point> point;
public:
	void setAttribute(const string& value) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class QPath : public SubPath {
private:
	vector<Point> point;
public:
	void setAttribute(const string& value) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class TPath : public SubPath {
private:
	vector<Point> point;
public:
	void setAttribute(const string& value) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class APath : public SubPath {
private:
	float rx;
	float ry;
	float large_arc_flag;
	float sweep_flag;
	float rotation;
	vector<Point> point;
public:
	void setAttribute(const string& value) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

class ZPath : public SubPath {
private:
public:
	ZPath(){}
	void setAttribute(const string& value) override;
	void draw(sf::RenderWindow& window, sf::Transform& transform) override;
};

#endif // !PATH_H

