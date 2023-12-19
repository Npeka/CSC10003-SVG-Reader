#include "SVG_Image.h"

// class ViewBox
// Constructor
ViewBox::ViewBox() {
	min_x = min_y = 0;
	width = 1024;
	height = 720;
}

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

void SVG_Image::standardizeTag(std::string& line) {
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
		parse(nameFile);
	}
}

// Destructor
SVG_Image::~SVG_Image() {
	dealocate(root);
	dealocate(background);
}

// Getter
const Group* SVG_Image::getRoot() const {
	return root;
}

// Set attribute
void SVG_Image::setWidth(string& width) {
	check_exception("SVG_Image", "width", this->width = std::stof(width));
}

void SVG_Image::setHeight(string& height) {
	check_exception("SVG_Image", "height", this->height = std::stof(height));
}

void SVG_Image::setStyle(string& style) {
	std::stringstream ss(style);
	string attribute, value;
	while (getline(ss, attribute, ':')) {
		getline(ss, value, ';');
		if (attribute == "background-color") 
			background->setElementAttributes("",value);
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
		else if (attribute == "style") setStyle(value);
		else if (attribute == "viewBox") viewbox.setViewBox(value);
	}
}
void SVG_Image::renewImage() {
	dealocate(root);
	dealocate(background);

	width = 0;
	height = 0;
	viewbox = ViewBox();
	root = new Group(); root->setParent(root);
	background = new RGB_Color(255, 255, 255);
}

void SVG_Image::parse(const string& nameFile) {
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
		getline(ss, word, ' ');
		getline(ss, info, '\0');

		if (word == "text") {
			std::string dataText, ignore;
			getline(inFile, dataText, '<');
			getline(inFile, ignore, '>');
			info += "| <" + dataText + "<";
		}

		standardizeTag(info);
		//std::cout << word << " | " << info << '\n';
		// Parse the node
		if (word == "svg") setImageAttributes(info);
		else if (isGradient(word)) {
			Gradient* newGradient = getGradient(word);
			newGradient->parseElementAttributes(info);	// Element
			if (info.find("/") == string::npos) {
				while (getline(inFile, line, '>')) {
					std::stringstream ss(line);
					getline(ss, word, '<');
					getline(ss, word, ' ');
					getline(ss, info, '\0');
					standardizeTag(info);
					if (word == "stop") newGradient->addStop(info);
					else if (isGradient(word.substr(1)) || word == "/defs") break;
					//std::cout << line << '\n';
				}
			} continue;
		}
		else if (word == "g") {
			Group* newGroup = new Group();
			newGroup->setParent(curGroup);			// Group
			newGroup->setParentAttributes();		// Group parent
			newGroup->parseElementAttributes(info);	// Element
			curGroup->addDrawable(newGroup);		// Group parent
			curGroup = newGroup;
		}
		else if (word == "/g") {
			curGroup = curGroup->getParent();
		}
		else {
			Figure* newFigure = figureFactory->getFigure(word);
			if (newFigure != nullptr) {
				curGroup->setChildAttributes(newFigure);
				newFigure->setGroupAttributes(curGroup);
				newFigure->parseElementAttributes(info);	// virtual Figure
				Drawable* newDrawable = dynamic_cast<Drawable*>(newFigure);
				if (newDrawable != nullptr) {
					newDrawable->setDrawableAtrributes();
					curGroup->addDrawable(newDrawable);
				}
			}
		}
	}
	std::cout << line << '\n';
	
	figureFactory->deleteInstance();
	inFile.close();
}

void SVG_Render(const SVG_Image& svgImage, Render_Window) {
	const vector<Drawable*>& figures = svgImage.getRoot()->getFigures();
	for (auto& figure : figures) {
		figure->draw(Render_Parameters);
	}
}
//-----------END-OF-IMPLEMENTATION-----------//