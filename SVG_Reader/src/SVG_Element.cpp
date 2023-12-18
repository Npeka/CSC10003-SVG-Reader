#include "SVG_Element.h"

std::unordered_map<string, SVG_Element*> SVG_Element::id_map;

SVG_Element::SVG_Element() :
	id("")
{}

void SVG_Element::setID(const string& id) {
	this->id = id;
	id_map[id] = this;
}

SVG_Element* SVG_Element::findGlobalElement(const string& id) {
	// parse id
	std::stringstream ss(id);
	string name;
	getline(ss, name, '#');
	if (name == id) return nullptr;
	getline(ss, name, ')');
	if (name[name.size() - 1] == '\'') name.pop_back();

	// find element
	auto it = id_map.find(name);
	if (it != id_map.end())
		return it->second;
	return nullptr;
}

void SVG_Element::parseElementAttributes(string& line) {
	std::stringstream ss(line);
	string attribute, value;
	while (ss >> attribute) {
		char end;
		ss >> end;
		getline(ss, value, end);
		if (attribute == "id") setID(value);
		else setElementAttributes(attribute, value);
	}
}

string SVG_Element::getID() const {
	return id;
}