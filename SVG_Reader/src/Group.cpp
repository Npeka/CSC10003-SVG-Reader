#include "Group.h"

Group::Group() :
	parent(nullptr)
{}

Group::~Group() {
	for (auto& figure : figures) {
		dealocate(figure);
	}
	parent = nullptr;
	figures.clear();
	childAttributes.clear();
}

void Group::setParent(Group* parent) {
	this->parent = parent;
}

void Group::setParentAttributes() {
	if (parent != nullptr) {
		copyColor(fill, parent->fill);
		copyColor(stroke, parent->stroke);
		stroke_width = parent->stroke_width;
	}
}

void Group::setFigureAttributes(const string& attribute, string& value) {
	childAttributes.push_back({ attribute, value });
}

void Group::setChildAttributes(Figure* figure) {
	for (auto& attribute : childAttributes) {
		figure->setFigureAttributes(attribute.first, attribute.second);
	}
}

Group* Group::getParent() {
	return parent;
}

const vector<Drawable*>& Group::getFigures() const {
	return figures;
}

void Group::addDrawable(Drawable* drawable) {
	if (drawable != nullptr) {
		this->figures.push_back(drawable);
	}
}

void Group::draw(Render_Window) {
	Transform_First(transforms, Render_Parameters);
	for (auto& figure : figures) {
		figure->draw(Render_Parameters);
	}
	Transform_Second(transforms, Render_Parameters);
}