#include "SVGImage.h"

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

// Public
	// Constructors
SVGImage::SVGImage() {
	root = nullptr;
	width = 0;
	height = 0;
	background.setRGB(255, 255, 255);
	namefile = "";
}

SVGImage::SVGImage(const std::string& nameFile) : SVGImage() {
	if (nameFile != "") {
		parse(nameFile);
	}
}

SVGImage::SVGImage(const SVGImage& svgImage) {
	viewbox = svgImage.viewbox;
	background = svgImage.background;
	width = svgImage.width;
	height = svgImage.height;
}

	// Destructor
SVGImage::~SVGImage() {
	if (root != nullptr) {
		delete root;
		root = nullptr;
	}
}

	// Getter
const Group* SVGImage::getRoot() const {
	return root;
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

void SVGImage::setSVGAttributes(const std::string& line) {
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

void SVGImage::parse(const std::string& nameFile) {
	if (nameFile == "" || nameFile == namefile) return;
	namefile = nameFile;
	if (root != nullptr) {
		delete root;
	}

	root = new Group();
	root->setParent(root);
	width = 0;
	height = 0;
	viewbox = ViewBox();
	background.setRGB(255, 255, 255);

	std::ifstream inFile(nameFile);
	std::string line;
	FigureFactory* figureFactory = FigureFactory::getInstance();

	Group* curGroup = root;
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
		// Parse the node
		if (word == "svg") setSVGAttributes(info);
		else if (word == "defs") {

		}
		else if (word == "g") {
			Group* newGroup = new Group();
			newGroup->setParent(curGroup);		// Group
			newGroup->setParentAttributes();	// Group parent
			newGroup->setAttributes(info);		// Figure
			curGroup->addDrawable(newGroup);	// Group parent
			curGroup = newGroup;
		}
		else if (word == "/g") {
			curGroup = curGroup->getParent();
		}
		else {
			Figure* newFigure = figureFactory->getFigure(word);
			if (newFigure != nullptr) {
				newFigure->setGroupAttributes(curGroup);
				newFigure->setAttributes(info);	// virtual Figure
				Drawable* newDrawable = dynamic_cast<Drawable*>(newFigure);
				if (newDrawable != nullptr) {
					newDrawable->setDrawableAtrributes();
					curGroup->addDrawable(newDrawable);
				}
			}
		}
	}
	
	figureFactory->deleteInstance();
	inFile.close();
}

void SVG_Render(const SVGImage& svgImage, Render_Window) {
	const std::vector<Drawable*>& figures = svgImage.getRoot()->getFigures();
	for (auto& figure : figures) {
		figure->draw(Render_Parameters);
	}
}
//-----------END-OF-IMPLEMENTATION-----------//