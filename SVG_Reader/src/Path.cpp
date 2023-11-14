#include "Path.h"

// class PathFactory
// Private
// Attribute
SubPathFactory* SubPathFactory::Instance = NULL;
// Method
SubPathFactory::SubPathFactory() {}

// Public
SubPathFactory* SubPathFactory::getInstance() {
	if (Instance == NULL)
		Instance = new SubPathFactory();
	return Instance;
}

SubPath* SubPathFactory::getSubPath(const char& command) {
	if (command == 'M' || command == 'm') return new MPath;
	else if (command == 'L' || command == 'l') return new LPath();
	else if (command == 'H') return new HPath();
	else if (command == 'h') return new hPath();
	else if (command == 'V') return new VPath();
	else if (command == 'v') return new vPath();
	else if (command == 'C' || command == 'c') return new CPath();
	else if (command == 'S' || command == 's') return new SPath();
	else if (command == 'Q' || command == 'q') return new QPath();
	else if (command == 'T' || command == 't') return new TPath();
	else if (command == 'A' || command == 'a') return new APath();
	else if (command == 'Z' || command == 'z') return new ZPath();
	return NULL;
}

void SubPathFactory::deleteInstance() {
	if (Instance != NULL)
		delete Instance;
	Instance = NULL;
}

// class Path
// Set attribute
void Path::setPath(const string& line) {
	stringstream ss(line);
	vector <string> v; string value;
	size_t getM = line.find('M');
	if (getM == string::npos) getM = line.find('m');
	for (size_t i = getM + 1; i < line.size(); i++) {
		if (isalpha(line[i])) {
			getline(ss, value, line[i]);
			v.push_back(value);
			ss.seekg(-1, ios::cur);
		}
	}

	char command;
	float x, y;
	Point savedInitialSubpath; // Initial point begin with M or m. 
	Point previousSubPath; // Previous subpath end point
	char previousCommand; // Previous command 

	SubPathFactory* subPathFactory = SubPathFactory::getInstance();
	for (int i = 0; i < v.size(); i++) {
		stringstream sss(v[i]);
		sss >> command;
		getline(sss, value);
		SubPath* newSubPath = subPathFactory->getSubPath(command);
		newSubPath->setCommand(command);
		
		if (command == 'm' || command == 'M') {
			newSubPath->setAttribute(value, { 0, 0 });
			previousSubPath = newSubPath->getEndPoint();
		}
		else {
			if ((previousCommand == 'z' || previousCommand == 'Z')) {
				newSubPath->setAttribute(value, savedInitialSubpath);
				previousSubPath = newSubPath->getEndPoint();
			}
			else {
				newSubPath->setAttribute(value, previousSubPath);
				previousSubPath = newSubPath->getEndPoint();
			}
		}
		
		path.push_back(newSubPath);
	}
	subPathFactory->deleteInstance();
}

// Virtual method
void Path::setAttribute(const string& attribute, const string& value) {
	if (attribute == "d") setPath(value);
}

void Path::draw(sf::RenderWindow& window, sf::Transform& transform) {
	for (SubPath* p : path)
		p->draw(window, transform);
}

Path::~Path() {
	for (int i = 0; i < path.size(); i++) {
		delete path[i];
	}
}

// class SubPath
// Constructor
SubPath::SubPath() {
	command = ' ';
}

// Set attribute
void SubPath::setCommand(const char& command) {
	this->command = command;
	//cout << ++n << " " << this->command << '\n';
	//cout << (char) this->command << endl;
}

// Virtual method

// class MPath
MPath::MPath() {}
MPath::MPath(const float& x, const float& y) {
	move.x = x;
	move.y = y;
}

void MPath::setAttribute(const string& value, Point initialPoint) {
	stringstream ss(value);
	ss >> move.x >> move.y;
}

void MPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

Point MPath::getEndPoint() {
	return this->move; 
}

// class LPath
void LPath::setAttribute(const string& value, Point initialPoint) {
	stringstream ss(value);
	float x, y;
	ss >> x >> y;
	lineTo = Point(x, y);
	this->initialPoint = initialPoint; 
}

void LPath::draw(sf::RenderWindow& window, sf::Transform& transform) {
	Line* line = new Line(initialPoint, lineTo);
	line->draw(window, transform);
}

Point LPath::getEndPoint() {
	return this->lineTo; 
}

// class HPath
void HPath::setAttribute(const string& value, Point initialPoint) {
	px = stof(value);
	this->initialPoint = initialPoint;
}

void HPath::draw(sf::RenderWindow& window, sf::Transform& transform) {
	Line* line = new Line(initialPoint, Point(px, initialPoint.y));
	line->draw(window, transform);
}

Point HPath::getEndPoint() {
	return Point(this->px, this->initialPoint.y);
}

// class hPath
void hPath::setAttribute(const string& value, Point initialPoint) {
	px = stof(value);
	this->initialPoint = initialPoint;
}

void hPath::draw(sf::RenderWindow& window, sf::Transform& transform) {
	Line* line = new Line(initialPoint, Point(initialPoint.x + px, initialPoint.y));
	line->draw(window, transform);
}

Point hPath::getEndPoint() {
	return Point(this->px, this->initialPoint.y);
}

// class VPath
void VPath::setAttribute(const string& value, Point initialPoint) {
	py = stof(value);
	this->initialPoint = initialPoint;
}

void VPath::draw(sf::RenderWindow& window, sf::Transform& transform) {
	Line* line = new Line(initialPoint, Point(initialPoint.x, py)); 
	line->draw(window, transform);
}

Point VPath::getEndPoint() {
	return Point(this->initialPoint.x, this->py);
}

// class vPath
void vPath::setAttribute(const string& value, Point initialPoint) {
	py = stof(value);
	this->initialPoint = initialPoint;
}

void vPath::draw(sf::RenderWindow& window, sf::Transform& transform) {
	Line* line = new Line(initialPoint, Point(initialPoint.x, initialPoint.y + py));
	line->draw(window, transform);
}

Point vPath::getEndPoint() {
	return Point(this->initialPoint.x, this->py);
}

// class CPath
void CPath::setAttribute(const string& value, Point initialPoint) {
	stringstream ss(value);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x, y));
	}
	this->initialPoint = initialPoint;
}

void CPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

Point CPath::getEndPoint() {
	return point[point.size() - 1]; 
}

// class SPath
void SPath::setAttribute(const string& value, Point initialPoint) {
	stringstream ss(value);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x, y));
	}
	this->initialPoint = initialPoint;
}
void SPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

Point SPath::getEndPoint() {
	return point[point.size() - 1];
}

// class QPath
void QPath::setAttribute(const string& value, Point initialPoint) {
	stringstream ss(value);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x, y));
	}
	this->initialPoint = initialPoint;
}
void QPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

Point QPath::getEndPoint() {
	return point[point.size() - 1];
}

// class TPath
void TPath::setAttribute(const string& value, Point initialPoint) {
	stringstream ss(value);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x, y));
	}
	this->initialPoint = initialPoint;
}

void TPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

Point TPath::getEndPoint() {
	return point[point.size() - 1];
}

// class APath
void APath::setAttribute(const string& value, Point initialPoint) {
	stringstream ss(value);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x, y));
	}
	this->initialPoint = initialPoint;
}

void APath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

Point APath::getEndPoint() {
	return point[point.size() - 1];  // check this again 
}

// class ZPath
void ZPath::setAttribute(const string& value, Point initialPoint) {}
void ZPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}
Point ZPath::getEndPoint() {};