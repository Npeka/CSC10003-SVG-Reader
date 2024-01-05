#include "SVG_Element.h"

SVG_Element::SVG_Element() :
	id(""),
	id_map(nullptr)
{}

SVG_Element::SVG_Element(const SVG_Element& other) :
	id(other.id),
	id_map(other.id_map)
{}

void SVG_Element::setID(const string& id, Defs_Type* id_map) {
	if (id == "") return;
	if (id_map == nullptr) return;
	this->id = id;
	this->id_map = id_map;
	auto it = id_map->find(id);
	if (it == id_map->end()) {
		(*id_map)[id] = this;
	}
}

void SVG_Element::setID_Map(Defs_Type* id_map) {
	this->id_map = id_map;
}

string SVG_Element::getID() const {
	return id;
}

SVG_Element* findGlobalElement(const string& id, const Defs_Type* id_map) {
	if (id_map == nullptr) return nullptr;
	// parse id
	std::stringstream ss(id);
	string name;
	getline(ss, name, '#');
	if (name == id) return nullptr;
	getline(ss, name, ')');
	if (name.size() != 0 && name[name.size() - 1] == '\'') name.pop_back();

	// find element
	auto it = id_map->find(name);
	if (it != id_map->end())
		return it->second;
	return nullptr;
}