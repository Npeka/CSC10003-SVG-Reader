#include "SVGImage.h"

// class ViewBox
// Constructor
ViewBox::ViewBox() {
	min_x = min_y = 0;
	width = height = 0;
}

// Set attribute
void ViewBox::setAttribute(const string& viewbox) {
	stringstream ss(viewbox);
	ss >> min_x >> min_y >> width >> height;
}

// class SVGImage
// Private
// Method
void SVGImage::standardizeTag(string& line) {
	for (int i = 0; i < line.size(); ++i) {
		if (line[i] == '=') line[i] = ' ';
	}

	//int idx = 0; 
	//while (idx != line.size() - 1) {
	//	if (line[idx] == ' ') {
	//		if (line[idx + 1] == ' ') {
	//			line.erase(idx + 1, 1);
	//		}
	//		else idx++;
	//	}
	//	else idx++;
	//}

	 // Remove redundant spaces
	//line.erase(
	//	std::unique(line.begin(), line.end(),
	//		[](char a, char b) { return std::isspace(a) && std::isspace(b); }),
	//	line.end()
	//);

	//// Remove leading and trailing spaces
	//line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](int ch) {
	//	return !std::isspace(ch);
	//	}));
	//line.erase(std::find_if(line.rbegin(), line.rend(), [](int ch) {
	//	return !std::isspace(ch);
	//	}).base(), line.end());
}

void SVGImage::parse() {
	ifstream inFile(nameFile);
	string line;
	FigureFactory* figureFactory = FigureFactory::getInstance();
	while (getline(inFile, line, '>')) {
		//cout << "line: " << line << endl;
		stringstream ss(line);
		string word, info;
		getline(ss, word, '<');
		getline(ss, word, ' ');
		getline(ss, info, '/');

	/*	cout << "line: " << line << endl; 
		cout << "word: " << word << endl; 
		cout << "info: " << info << endl;*/

		if (word == "text") {
			string dataText, ignore;
			getline(inFile, dataText, '<');
			getline(inFile, ignore, '>');
			info += "| <" + dataText + "<";
		}

		standardizeTag(info);

		if (word == "svg") {
			setAttribute(info);
			continue;
		}
		Figure* newFigure = figureFactory->getFigure(word);
		if (newFigure != NULL) {
			newFigure->setAttribute(info);
			figure.push_back(newFigure);
		}
	}
	figureFactory->deleteInstance();
	inFile.close();
}

// Public
// Constructors
SVGImage::SVGImage(const string& nameFile) {
	this->nameFile = nameFile;	
	width = 0;
	height = 0;
	background.setRGB(255, 255, 255);
	parse();
}

// Destructor
SVGImage::~SVGImage() {
	for (Figure* f : figure) {
		delete f;
		f = NULL;
	}
	figure.resize(0);
}

// Method
void SVGImage::setWidth(const string& width) {
	this->width = stof(width);
}

void SVGImage::setHeight(const string& height) {
	this->height = stof(height);
}

void SVGImage::setStyle(const string& style) {
	stringstream ss(style);
	string attribute, value;
	while (getline(ss, attribute, ':')) {
		getline(ss, value, ';');
		if (attribute == "background-color") background.setRGB(value);
	}
}

void SVGImage::setViewBox(const string& viewbox) {
	this->viewbox.setAttribute(viewbox);
}

void SVGImage::setAttribute(const string& line) {
	stringstream ss(line);
	string attribute, value;
	while (ss >> attribute) {
		getline(ss, value, '"');
		getline(ss, value, '"');
		if (attribute == "width") setWidth(value);
		else if (attribute == "height") setHeight(value);
		else if (attribute == "style") setStyle(value);
		else if (attribute == "viewBox") setViewBox(value);
	}
}

void SVGImage::draw(sf::RenderWindow& window, sf::Transform& transform) {
	for (Figure* f : figure)
		f->draw(window, transform);
}