#include "Path.h"

// class PathFactory
// Private
// Attribute
SubPathFactory* SubPathFactory::Instance = NULL;
// Method
SubPathFactory::SubPathFactory() {}

// Public
SubPathFactory* SubPathFactory::getInstance() {
	
	return Instance;
}

SubPath* SubPathFactory::getSubPath(const char& command) {
	
	return NULL;
}

void SubPathFactory::deleteInstance() {
	
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
	SubPathFactory* subPathFactory = SubPathFactory::getInstance();
	for (int i = 0; i < v.size(); i++) {
		stringstream sss(v[i]);
		sss >> command;
		getline(sss, value);
		SubPath* newSubPath = subPathFactory->getSubPath(command);
		newSubPath->setCommand(command);
		newSubPath->setAttribute(value);
		path.push_back(newSubPath);
	}
	subPathFactory->deleteInstance();
}

// Virtual method
void Path::setAttribute(const string& attribute, const string& value) {
	
}

void Path::draw(sf::RenderWindow& window, sf::Transform& transform) {
	
}

Path::~Path() {
	for (int i = 0; i < path.size(); i++) {
		delete path[i];
	}
}

// class SubPath
// Constructor
SubPath::SubPath() {
	
}

// Set attribute
void SubPath::setCommand(const char& command) {
	
}

// Virtual method

// class MPath
MPath::MPath() {}
MPath::MPath(const float& x, const float& y) {
	
}

void MPath::setAttribute(const string& value) {
	stringstream ss(value);
	ss >> move.x >> move.y;
}

void MPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

// class LPath
void LPath::setAttribute(const string& value) {
	stringstream ss(value);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x, y));
	}
}

void LPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

// class HPath
void HPath::setAttribute(const string& value) {
	px = stof(value);
}

void HPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

// class VPath
void VPath::setAttribute(const string& value) {
	px = stof(value);
}

void VPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

// class CPath
void CPath::setAttribute(const string& value) {
	stringstream ss(value);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x, y));
	}
}

void CPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

// class SPath
void SPath::setAttribute(const string& value) {
	stringstream ss(value);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x, y));
	}
}
void SPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

// class QPath
void QPath::setAttribute(const string& value) {
	stringstream ss(value);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x, y));
	}
}
void QPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

// class TPath
void TPath::setAttribute(const string& value) {
	stringstream ss(value);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x, y));
	}
}

void TPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

// class APath
void APath::setAttribute(const string& value) {
	stringstream ss(value);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x, y));
	}
}

void APath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

// class ZPath
void ZPath::setAttribute(const string& value) {}
void ZPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}