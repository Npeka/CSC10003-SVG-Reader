#include "Transform.h"

Transform::Transform(const Transform& other) :
	transforms(other.transforms)
{}

Transform::~Transform() {
	for (auto& transform : transforms) 
		transform.second.clear();
	transforms.clear();
}

void Transform::setTranslate(string& translate) {
	std::stringstream ss(translate);
	float x, y;
	ss >> x >> y;
	vector<float> value = { x, y };
	transforms.push_back({ SVG_Translate, value });
}

void Transform::setRotate(string& rotate) {
	std::stringstream ss(rotate);
	float r;
	ss >> r;
	vector<float> value = { r };
	transforms.push_back({ SVG_Rotate, value });
}

void Transform::setScale(string& scale) {
	std::stringstream ss(scale);
	float x, y(0);
	ss >> x >> y;
	if (y == 0) y = x;
	vector<float> value = { x, y };
	transforms.push_back({ SVG_Scale, value });
}

void Transform::setMatrix(string& matrix) {
	std::stringstream ss(matrix);
	float m;
	vector<float> value;
	for (int i = 0; i < 6; i++) {
		ss >> m;
		value.push_back(m);
	}
	transforms.push_back({ SVG_Matrix, value });
}

void Transform::setTransform(string& transform) {
	for (char& c : transform) if (c == '(' || c == ',') c = ' ';
	std::stringstream ss(transform);
	string attribute, value;
	while (ss >> attribute) {
		getline(ss, value, ')');
		if (attribute == "translate") setTranslate(value);
		else if (attribute == "rotate") setRotate(value);
		else if (attribute == "scale") setScale(value);
		else if (attribute == "matrix") setMatrix(value);
	}
}

Transform_Type Transform::getTransform() const {
	return transforms;
}