#include "Group.h"

Group::Group() {
	parent = nullptr;
}

Group::~Group() {
	for (auto& figure : figures) {
		if (figure != nullptr) {
			delete figure;
			figure = nullptr;
		}
	}
	figures.resize(0);
}

void Group::setParent(Group* parent) {
	this->parent = parent;
}

void Group::addDrawable(Drawable* drawable) {
	this->figures.push_back(drawable);
}

Group* Group::getParent() {
	return parent;
}

const std::vector<Drawable*>& Group::getFigures() const {
	return figures;
}

void Group::draw(Render_Window) {
	for (auto& figure : figures) {
		figure->draw(Render_Parameters);
	}
}