#include "SVGImage.h"
#include "stack"

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
//-----------end-of-implementation-----------//

// class SVGImage
// Private
// Method
void SVGImage::standardizeTag(string& line) {
	for (int i = 0; i < line.size(); ++i) {	
		if (line[i] == '=') line[i] = ' ';
		else if (line[i] == '|') return;
	}
}

void SVGImage::parse() {
	ifstream inFile(nameFile);
	string line;
	FigureFactory* figureFactory = FigureFactory::getInstance();
	stack<Figure*> g; g.push(NULL);
	while (getline(inFile, line, '>')) {
		stringstream ss(line);
		string word, info;
		getline(ss, word, '<');
		getline(ss, word, ' ');
		getline(ss, info, '\0');

		if (word == "text") {
			string dataText, ignore;
			getline(inFile, dataText, '<');
			getline(inFile, ignore, '>');
			info += "| <" + dataText + "<";
		}

		standardizeTag(info);
		if (word == "svg") setAttribute(info);
		else if (word == "g") {
			Figure* prev = g.top();
			g.push(new Figure());
			if (prev != NULL) {
				g.top()->setAttribute(prev);
			}
			g.top()->setAttribute(info);
		}
		else if (word == "/g") {
			delete g.top();
			g.top() = NULL;
			g.pop();
		}
		else {
			Figure* newFigure = figureFactory->getFigure(word);
			if (newFigure != NULL) {
				if (g.top() != NULL) {
					newFigure->setAttribute(g.top());
				}
				newFigure->setAttribute(info);
				figure.push_back(newFigure);
			}
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

SVGImage::SVGImage(const SVGImage& svgImage) {
	nameFile = svgImage.nameFile;
	viewbox = svgImage.viewbox;
	background = svgImage.background;
	width = svgImage.width;
	height = svgImage.height;
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
	check_exception("SVGImage", "width", this->width = stof(width));
}

void SVGImage::setHeight(const string& height) {
	check_exception("SVGImage", "height", this->height = stof(height));
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

const vector<Figure*>& SVGImage::getFigure() const {
	return figure;
}
//-----------end-of-implementation-----------//