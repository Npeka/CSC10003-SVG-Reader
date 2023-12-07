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
	figures.clear();
}

void Group::setParent(Group* parent) {
	this->parent = parent;
}

void Group::setParentAttributes() {
	if (parent != nullptr) {
		fill = parent->fill;
		stroke = parent->stroke;
		stroke_width = parent->stroke_width;
		//transform = parent->transform;
	}
}

Group* Group::getParent() {
	return parent;
}

const std::vector<Drawable*>& Group::getFigures() const {
	return figures;
}

void Group::addDrawable(Drawable* drawable) {
	if (drawable != nullptr) {
		this->figures.push_back(drawable);
	}
}

void Group::draw(Render_Window) {
	Transform_First(transform, Render_Parameters);
	for (auto& figure : figures) {
		figure->draw(Render_Parameters);
	}
	Transform_Second(transform, Render_Parameters);
}