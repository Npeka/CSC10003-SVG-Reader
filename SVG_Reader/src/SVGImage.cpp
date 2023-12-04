#include "SVGImage.h"
#include "stack"

// class ViewBox
// Constructor
ViewBox::ViewBox() {
	min_x = min_y = 0;
	width = 1024;
	height = 720;
}

// Set attribute
void ViewBox::setAttribute(const std::string& viewbox) {
	std::stringstream ss(viewbox);
	check_exception("viewbox", "value", ss >> min_x >> min_y >> width >> height);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class SVGImage
// Private
	// Methods

void SVGImage::standardizeTag(std::string& line) {
	for (int i = 0; i < line.size(); ++i) {	
		if (line[i] == '=') line[i] = ' ';
		else if (line[i] == '|') return;
	}
}

void SVGImage::parse(const std::string& nameFile) {
	std::ifstream inFile(nameFile);
	std::string line;
	FigureFactory* figureFactory = FigureFactory::getInstance();
	std::stack<Figure*> g; g.push(NULL);
	while (getline(inFile, line, '>')) {
		std::stringstream ss(line);
		std::string word, info;
		getline(ss, word, '<');
		getline(ss, word, ' ');
		getline(ss, info, '\0');

		if (word == "text") {
			std::string dataText, ignore;
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
				g.top()->setGroup(prev);
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
					newFigure->setGroup(g.top());
				}
				newFigure->setAttribute(info);
				Drawable* newDrawable = dynamic_cast<Drawable*>(newFigure);
				if (newDrawable != NULL) {
					newDrawable->setAtrribute();
					figure.push_back(newDrawable);
				}
			}
		}
	}
	figureFactory->deleteInstance();
	inFile.close();
}

// Public
	// Constructors
SVGImage::SVGImage(const std::string& nameFile) {
	width = 0;
	height = 0;
	background.setRGB(255, 255, 255);
	parse(nameFile);
}

SVGImage::SVGImage(const SVGImage& svgImage) {
	viewbox = svgImage.viewbox;
	background = svgImage.background;
	width = svgImage.width;
	height = svgImage.height;
}

	// Destructor
SVGImage::~SVGImage() {
	for (Drawable* f : figure) {
		delete f;
		f = NULL;
	}
	figure.resize(0);
}

	// Set attribute
void SVGImage::setWidth(const std::string& width) {
	check_exception("SVGImage", "width", this->width = std::stof(width));
}

void SVGImage::setHeight(const std::string& height) {
	check_exception("SVGImage", "height", this->height = std::stof(height));
}

void SVGImage::setStyle(const std::string& style) {
	std::stringstream ss(style);
	std::string attribute, value;
	while (getline(ss, attribute, ':')) {
		getline(ss, value, ';');
		if (attribute == "background-color") background.setRGB(value);
	}
}

void SVGImage::setViewBox(const std::string& viewbox) {
	this->viewbox.setAttribute(viewbox);
}

void SVGImage::setAttribute(const std::string& line) {
	std::stringstream ss(line);
	std::string attribute, value;
	while (ss >> attribute) {
		getline(ss, value, '"');
		getline(ss, value, '"');
		if (attribute == "width") setWidth(value);
		else if (attribute == "height") setHeight(value);
		else if (attribute == "style") setStyle(value);
		else if (attribute == "viewBox") setViewBox(value);
	}
}
//-----------END-OF-IMPLEMENTATION-----------//