#include "SVG_Image.h"

// class ViewBox
// Constructor
ViewBox::ViewBox() :
	min_x(0),
	min_y(0),
	width(0),
	height(0)
{}

// Set attribute
void ViewBox::setViewBox(string& viewbox) {
	std::stringstream ss(viewbox);
	check_exception("viewbox", "value", ss >> min_x >> min_y >> width >> height);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class SVG_Image
// Private
	// Methods

void SVG_Image::standardizeTag(string& line) {
	for (int i = 0; i < line.size(); ++i) {	
		if (line[i] == '=') line[i] = ' ';
		else if (line[i] == '|') return;
	}
}

// Public
	// Constructors
SVG_Image::SVG_Image() :
	root(nullptr),
	width(0),
	height(0),
	viewbox(),
	background(new RGB_Color(255,255,255)),
	namefile("")
{}

SVG_Image::SVG_Image(const string& nameFile) : SVG_Image() {
	if (nameFile != "") {
		parseImage(nameFile);
	}
}

// Destructor
SVG_Image::~SVG_Image() {
	dealocate(root);
	dealocate(background);
	id_map.clear();
}

void SVG_Image::renewImage() {
	dealocate(root);
	dealocate(background);

	width = height = 0;
	viewbox = ViewBox();
	root = new Group(); root->setParent(root);
	background = new RGB_Color(255, 255, 255);
}

// Set attribute
void SVG_Image::setWidth(string& width) {
	check_exception("SVG_Image", "width", this->width = std::stof(width));
	if (width.find("pt") != string::npos) this->width *= 96.f / 72.f; else 
	if (width.find("cm") != string::npos) this->width *= 96.f / 2.54f;
}

void SVG_Image::setHeight(string& height) {
	check_exception("SVG_Image", "height", this->height = std::stof(height));
	if (height.find("pt") != string::npos) this->height *= 96.f / 72.f; else
	if (height.find("cm") != string::npos) this->height *= 96.f / 2.54f;
}

void SVG_Image::setStyleImage(string& style) {
	std::stringstream ss(style);
	string attribute, value;
	while (getline(ss, attribute, ':')) {
		getline(ss, value, ';');
		if (attribute == "background-color") 
			background->setElementAttributes("",value);
		else setImageAttributes(value);
	}
}

void SVG_Image::setStyleElement(SVG_Element* element, string& style) {
	std::stringstream ss(style);
	string attribute, value;
	while (getline(ss, attribute, ':')) {
		getline(ss, value, ';');
		element->setElementAttributes(attribute, value);
	}
}

void SVG_Image::setImageAttributes(string& line) {
	std::stringstream ss(line);
	string attribute, value;
	while (ss >> attribute) {
		char end; ss >> end;
		getline(ss, value, end);
		if (attribute == "width") setWidth(value);
		else if (attribute == "height") setHeight(value);
		else if (attribute == "style") setStyleImage(value);
		else if (attribute == "viewBox") viewbox.setViewBox(value);
	}
}

void SVG_Image::parseElementAttributes(SVG_Element* element, string& line) {
	element->setID_Map(&id_map);
	std::stringstream ss(line);
	string attribute, value;
	while (ss >> attribute) {
		char end; ss >> end;
		getline(ss, value, end);
		if (attribute == "id") element->setID(value, &id_map);
		else if (attribute == "style") setStyleElement(element, value);
		else element->setElementAttributes(attribute, value);
	}
}

void SVG_Image::parseImage(const string& nameFile) {
	if (nameFile == "" || nameFile == namefile) return;
	
	// Init new SVG_Image
	namefile = nameFile;
	renewImage();

	// Parse file
	std::ifstream inFile(nameFile);
	if (!inFile.is_open()) {
		std::cout << "Can't open file " << nameFile << '\n';
		return;
	}

	FigureFactory* figureFactory = FigureFactory::getInstance();
	Group* curGroup = root;
	string line;

	while (getline(inFile, line, '>')) {
		std::stringstream ss(line);
		string word, info;
		getline(ss, word, '<');
		ss >> word;
		getline(ss, info, '\0');

		if (word == "text") {
			std::string dataText, ignore;
			getline(inFile, dataText, '<');
			getline(inFile, ignore, '>');
			info += "| <" + dataText + "<";
		}

		standardizeTag(info);
		// Parse the node
		if (word == "svg") setImageAttributes(info);
		else 
		if (word == "linearGradient" || 
			word == "radialGradient") {
			Gradient* newGradient = getGradient(word);
			parseElementAttributes(newGradient, info);	// Element
			if (info.find("/") == string::npos) {
				while (getline(inFile, line, '>')) {
					std::stringstream ss(line);
					getline(ss, word, '<'); 
					ss >> word;
					getline(ss, info, '\0');
					standardizeTag(info);
					if (word == "stop") newGradient->addStop(info); else 
					if (word == "/linearGradient" ||
						word == "/radialGradient" || 
						word == "/defs") break;
				}
			}
		}
		else 
		if (word == "g") {
			Group* newGroup = new Group();
			newGroup->setParent(curGroup);			// Group
			newGroup->setParentAttributes();		// Group parent
			parseElementAttributes(newGroup, info);	// Element
			curGroup->addDrawable(newGroup);		// Group parent
			curGroup = newGroup;
		}
		else 
		if (word == "/g") {
			curGroup = curGroup->getParent();
		}
		else {
			Figure* newFigure = figureFactory->getFigure(word);
			if (newFigure != nullptr) {
				curGroup->setChildAttributes(newFigure);
				newFigure->setGroupAttributes(curGroup);
				parseElementAttributes(newFigure, info);	// Element
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

// Getter
const Group* SVG_Image::getRoot() const {
	return root;
}

float SVG_Image::getWidth() const {
	return width;
}

float SVG_Image::getHeight() const {
	return height;
}

ViewBox SVG_Image::getViewBox() const {
	return viewbox;
}

Defs_Type SVG_Image::getDefs() const {
	return id_map;
}

void SVG_Render(const SVG_Image& svgImage, Render_Window) {
	const vector<Drawable*>& figures = svgImage.getRoot()->getFigures();
	for (auto& figure : figures) {
		figure->draw(Render_Parameters);
	}
}
//-----------END-OF-IMPLEMENTATION-----------//