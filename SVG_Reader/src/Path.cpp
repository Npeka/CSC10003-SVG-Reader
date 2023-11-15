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
	else if (command == 'Q' || command == 'q') return new CPath();
	else if (command == 'S' || command == 's') return new SPath();
	else if (command == 'T' || command == 't') return new SPath();
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
	Point controlPoint; // Save C control point using for S subpath.
	char previousCommand; // Previous command 

	SubPathFactory* subPathFactory = SubPathFactory::getInstance();
	for (int i = 0; i < v.size(); i++) {
		stringstream sss(v[i]);
		sss >> command;
		getline(sss, value);
		SubPath* newSubPath = subPathFactory->getSubPath(command);
		newSubPath->setCommand(command);
		
		if (command == 'm' || command == 'M') {
			newSubPath->setAttribute(value, { 0, 0 }, { 0 ,0 });
		}
		else if (command == 'C' || command == 'c' || command == 'Q' || command == 'q') {
			newSubPath->setAttribute(value, previousSubPath, { 0 ,0 });
			controlPoint = newSubPath->getControlPoint();
		}
		else {
			if ((previousCommand == 'z' || previousCommand == 'Z')) {
				newSubPath->setAttribute(value, savedInitialSubpath, { 0 ,0 });
			}
			else {
				if ((command == 's' || command == 'S') && (previousCommand == 'c' || previousCommand == 'C')) {
					newSubPath->setAttribute(value, savedInitialSubpath, controlPoint);
				}
				else if ((command == 'T' || command == 't') && (previousCommand == 'Q' || previousCommand == 'q')) {
					newSubPath->setAttribute(value, savedInitialSubpath, controlPoint);
				}
				else {
					newSubPath->setAttribute(value, previousSubPath, { 0 ,0 });
				}
			}
		}
		previousSubPath = newSubPath->getEndPoint();
		previousCommand = command;
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

// Calculate method 
float SubPath::computeBinominal(int n, int k) {
	float value = 1.0;

	for (int i = 1; i <= k; i++) {
		value = value * ((n + 1 - i) / i);
	}

	if (n == k) {
		value = 1;
	}
	return value;
}

vector<Point> SubPath::BezierCurveVertices(vector<Point> Position) {
	vector<Point> CurvePositions;

	int n = Position.size() - 1;
	for (float t = 0.0; t <= 1.0; t += 0.001) {
		Point CurvePos = { 0.0, 0.0 };
		for (int i = 0; i <= n; ++i) {
			CurvePos.x += computeBinominal(n, i) * pow((1 - t), (n - i)) * pow(t, i) * Position[i].x;
			CurvePos.y += computeBinominal(n, i) * pow((1 - t), (n - i)) * pow(t, i) * Position[i].y;
		}
		CurvePositions.push_back(CurvePos);
	}

	return CurvePositions;
}

// Virtual method

// class MPath
MPath::MPath() {}
MPath::MPath(const float& x, const float& y) {
	move.x = x;
	move.y = y;
}

void MPath::setAttribute(const string& value, Point initialPoint, Point controlPoint) {
	stringstream ss(value);
	ss >> move.x >> move.y;
}

void MPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}

Point MPath::getEndPoint() {
	return this->move; 
}

Point MPath::getControlPoint() {
	return { 0, 0 };
}

// class LPath
void LPath::setAttribute(const string& value, Point initialPoint, Point controlPoint) {
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

Point LPath::getControlPoint() {
	return { 0, 0 };
}

// class HPath
void HPath::setAttribute(const string& value, Point initialPoint, Point controlPoint) {
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

Point HPath::getControlPoint() {
	return { 0, 0 };
}

// class hPath
void hPath::setAttribute(const string& value, Point initialPoint, Point controlPoint) {
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

Point hPath::getControlPoint() {
	return { 0, 0 }; 
}

// class VPath
void VPath::setAttribute(const string& value, Point initialPoint, Point controlPoint) {
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

Point VPath::getControlPoint() {
	return { 0, 0 };
}

// class vPath
void vPath::setAttribute(const string& value, Point initialPoint, Point controlPoint) {
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

Point vPath::getControlPoint() {
	return { 0, 0 };
}

// class CPath
void CPath::setAttribute(const string& value, Point initialPoint, Point controlPoint) {
	stringstream ss(value);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x, y));
	}
	this->initialPoint = initialPoint;
}

void CPath::draw(sf::RenderWindow& window, sf::Transform& transform) {
	reverse(point.begin(), point.end());  //
	point.push_back(initialPoint);		  // -> add initial point into first place.
	reverse(point.begin(), point.end());  //

	vector<Point> vertices = BezierCurveVertices(point);

	for (int i = 0; i < vertices.size() - 1; i++) {
		Line* line = new Line(vertices[i], vertices[i + 1]);
		line->draw(window, transform);
	}
}

Point CPath::getEndPoint() {
	return point[point.size() - 1]; 
}

Point CPath::getControlPoint() {
	return point[point.size() - 2];
}


// class SPath

void SPath::setAttribute(const string& value, Point initialPoint, Point controlPoint) {
	stringstream ss(value);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x, y));
	}
	this->initialPoint = initialPoint;
	this->controlPoint = controlPoint; 
}

void SPath::draw(sf::RenderWindow& window, sf::Transform& transform) {

	Point controlPointOfS; 
	controlPointOfS.x = initialPoint.x * 2 - controlPoint.x;  // -> Calculate control point
	controlPointOfS.y = initialPoint.y * 2 - controlPoint.y;  // 

	reverse(point.begin(), point.end());   //
	point.push_back(controlPointOfS);	   // -> add control point and initial point into vector point
	point.push_back(initialPoint);         // 
	reverse(point.begin(), point.end());   // 

	vector<Point> vertices = BezierCurveVertices(point);

	for (int i = 0; i < vertices.size() - 1; i++) {
		Line* line = new Line(vertices[i], vertices[i + 1]);
		line->draw(window, transform);
	}
}

Point SPath::getEndPoint() {
	return point[point.size() - 1];
}

Point SPath::getControlPoint() {
	return { 0, 0 };
}

// class APath
void APath::setAttribute(const string& value, Point initialPoint, Point controlPoint) {
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

Point APath::getControlPoint() {
	return { 0, 0 };
}

// class ZPath
void ZPath::setAttribute(const string& value, Point initialPoint, Point controlPoint) {}
void ZPath::draw(sf::RenderWindow& window, sf::Transform& transform) {}
Point ZPath::getEndPoint() {
	return { 0, 0 };
};
Point ZPath::getControlPoint() {
	return { 0, 0 };
}