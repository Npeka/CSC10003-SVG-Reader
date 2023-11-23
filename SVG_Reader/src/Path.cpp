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
	else if (command == 'L') return new LPath();
	else if (command == 'l') return new lPath();
	else if (command == 'H') return new HPath();
	else if (command == 'h') return new hPath();
	else if (command == 'V') return new VPath();
	else if (command == 'v') return new vPath();
	else if (command == 'C') return new CPath();
	else if (command == 'c') return new cPath();
	else if (command == 'z' || command == 'Z') return new ZPath();
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
	//cout << "line: " << line << endl;
	vector<int> positions; 
	vector<string> substrings; 

	for (int i = 0; i < line.length(); i++) {
		if (isalpha(line[i])) 
			positions.push_back(i);
		if (i == line.length() - 1)
			positions.push_back(i + 1); 
	}

	for (int i = 0; i < positions.size() - 1; i++) {
		string substring = line.substr(positions[i], positions[i + 1] - positions[i]);
		substrings.push_back(substring);
	}
	 
	//for (auto x : substrings) cout << x << endl; 

	char command;
	float x, y;
	Point InitialSubpath; // Initial point begin with M or m. 
	Point previousSubPath; // Previous subpath end point
	char previousCommand; // Previous command 

	SubPathFactory* subPathFactory = SubPathFactory::getInstance();
	for (int i = 0; i < substrings.size(); i++) {
		stringstream ss(substrings[i]); string value;
		ss >> command;
		getline(ss, value);

		// Transform into space form 
		for (int i = 0; i < value.size(); i++) {
			if (value[i] == ',') {
				value[i] = ' ';
			}
		}

		cout << command << endl << value << endl;

		SubPath* newSubPath = subPathFactory->getSubPath(command);
		newSubPath->setCommand(command);

		if (command == 'm' || command == 'M') {
			newSubPath->setAttribute(value, { 0, 0 });
			InitialSubpath = newSubPath->getEndPoint();
		}
		else if (command == 'z' || command == 'Z') {
			value = to_string(InitialSubpath.x) + " " + to_string(InitialSubpath.y);
			newSubPath->setAttribute(value, previousSubPath);
		}
		else if (previousCommand == 'z' || previousCommand == 'Z') {
			newSubPath->setAttribute(value, InitialSubpath);
		}
		else {
			newSubPath->setAttribute(value, previousSubPath);
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
	for (SubPath* p : path) {
		//cout << p->getEndPoint().x << " " << p->getEndPoint().y << endl;
		p->draw(window, transform);
	}		
	//exit(1);
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

void MPath::setAttribute(const string& value, Point initialPoint) {
	stringstream ss(value);
	ss >> move.x >> move.y;

	cout << "Move: ";
	cout << move.x << " " << move.y << endl; 
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
	cout << "Line: ";
	cout << initialPoint.x << " " << initialPoint.y << endl;
}

void LPath::draw(sf::RenderWindow& window, sf::Transform& transform) {
	Line* line = new Line(initialPoint, lineTo);
	line->setStroke("black"); 
	line->setFill("black");
	line->setStrokeWidth("10");
	line->draw(window, transform);
}

Point LPath::getEndPoint() {
	return this->lineTo; 
}

// class lPath
void lPath::setAttribute(const string& value, Point initialPoint) {
	this->initialPoint = initialPoint;
	stringstream ss(value);
	float x, y;
	ss >> x >> y;
	lineTo = Point(x + initialPoint.x, y + initialPoint.y);
}

void lPath::draw(sf::RenderWindow& window, sf::Transform& transform) {
	Line* line = new Line(initialPoint, lineTo);
	line->setStroke("black");
	line->setFill("black");
	line->setStrokeWidth("10");
	line->draw(window, transform);
}

Point lPath::getEndPoint() {
	return this->lineTo;
}

// class HPath
void HPath::setAttribute(const string& value, Point initialPoint) {
	px = stof(value);
	this->initialPoint = initialPoint;
}

void HPath::draw(sf::RenderWindow& window, sf::Transform& transform) {
	Line* line = new Line(initialPoint, Point(px, initialPoint.y));
	line->setStroke("black"); line->setFill("black");
	line->setStrokeWidth("10");
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
	line->setStroke("black"); line->setFill("black");
	line->setStrokeWidth("10");
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
	line->setStroke("black"); line->setFill("black");
	line->setStrokeWidth("10");
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
	line->setStroke("black"); line->setFill("black");
	line->setStrokeWidth("10");
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

void CPath::draw(sf::RenderWindow& window, sf::Transform& transform) {
	reverse(point.begin(), point.end());  //
	point.push_back(initialPoint);		  // -> add initial point into first place.
	reverse(point.begin(), point.end());  //

	vector<Point> vertices = BezierCurveVertices(point);

	for (int i = 0; i < vertices.size() - 1; i++) {
		Line* line = new Line(vertices[i], vertices[i + 1]);
		line->setStroke("black"); line->setFill("black");
		line->setStrokeWidth("10");
		line->draw(window, transform);
	}
}

Point CPath::getEndPoint() {
	return point[point.size() - 1]; 
}

// class cPath
void cPath::setAttribute(const string& value, Point initialPoint) {
	this->initialPoint = initialPoint;
	stringstream ss(value);
	float x, y;
	while (ss >> x >> y) {
		point.push_back(Point(x + initialPoint.x, y + initialPoint.y));
	}
}

void cPath::draw(sf::RenderWindow& window, sf::Transform& transform) {
	reverse(point.begin(), point.end());  //
	point.push_back(initialPoint);		  // -> add initial point into first place.
	reverse(point.begin(), point.end());  //

	vector<Point> vertices = BezierCurveVertices(point);

	for (int i = 0; i < vertices.size() - 1; i++) {
		Line* line = new Line(vertices[i], vertices[i + 1]);
		line->setStroke("black"); line->setFill("black");
		line->setStrokeWidth("10");
		line->draw(window, transform);
	}
}

Point cPath::getEndPoint() {
	return point[point.size() - 1];
}

// class ZPath
void ZPath::setAttribute(const string& value, Point initialPoint) {
	this->initialPoint = initialPoint; 
	stringstream ss(value);
	float x, y; 
	ss >> x >> y; 
	this->initialSubpath = Point(x, y);
}

void ZPath::draw(sf::RenderWindow& window, sf::Transform& transform) {
	Line* line = new Line(initialPoint, initialSubpath);
	line->setStroke("black");
	line->setFill("black");
	line->setStrokeWidth("10");
	line->draw(window, transform);
}

Point ZPath::getEndPoint() {
	return initialSubpath; 
};