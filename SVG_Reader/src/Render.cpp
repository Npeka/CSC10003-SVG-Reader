#include "Render.h"

Gdiplus::Color GDI_Color(const Color& color) {
	return Gdiplus::Color(color.a, color.r, color.g, color.b);
}

void Transform_First(const std::vector <std::pair <int, Point>>& t, Render_Window) {
	for (int i = 0; i < t.size(); ++i) {
		if (t[i].first == SVG_Translate) {

		}
		else if (t[i].first == SVG_Rotate) {

		}
		else if (t[i].first == SVG_Scale) {

		}
	}
}

void Transform_Second(const std::vector <std::pair <int, Point>>& t, Render_Window) {
	for (int i = t.size() - 1; i >= 0; --i) {
		if (t[i].first == SVG_Translate) {

		}
		else if (t[i].first == SVG_Rotate) {

		}
		else if (t[i].first == SVG_Scale) {

		}
	}
}
// class Drawable
Drawable::Drawable() : pen(Gdiplus::Color(0, 0, 0)), brush(Gdiplus::Color(0, 0, 0)) {};
/*



*/
// class DrawableRectangle
// Constructor
void Drawable_Rectangle::setDrawableAtrributes() {
	
}

// Virtual method
void Drawable_Rectangle::draw(Render_Window) {
	
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawableEllipse
// Constructor
void Drawable_Ellipse::setDrawableAtrributes() {
	

}

// Virtual method
void Drawable_Ellipse::draw(Render_Window) {
	
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawableCircle
// Constructor
void Drawable_Circle::setDrawableAtrributes() {
	
}

// Virtual method
void Drawable_Circle::draw(Render_Window) {

}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawableLine

// Constructor
Drawable_Line::Drawable_Line(const Line* other) : Line(*other) {
	
}

void Drawable_Line::setDrawableAtrributes() {
	
}

void Drawable_Line::setLine(Color stroke) {
	
}

// Virtual method
void Drawable_Line::draw(Render_Window) {
	
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawablePolyline
// Private
	// Methods
void Drawable_Polyline::drawPolyline(Render_Window) {
	
}

void Drawable_Polyline::drawPolyline2(Render_Window) {
	
}
// Public
// Constructor
void Drawable_Polyline::setDrawableAtrributes() {
	
}

// Virtual method
void Drawable_Polyline::draw(Render_Window) {
	
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawablePolygon
// Constructor
void Drawable_Polygon::setDrawableAtrributes() {
	
}

// Virtual method
void Drawable_Polygon::draw(Render_Window) {
	
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawableText
// Constructor
void Drawable_Text::setDrawableAtrributes() {
	
}

// Virtual method
void Drawable_Text::draw(Render_Window) {
	
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/

// class SF_Path

// Constructor
void Drawable_Path::setDrawableAtrributes() {

}

void Drawable_Path::drawPath(Render_Window) {
	
}

// Virtual method
void Drawable_Path::draw(Render_Window) {

}
//-----------END-OF-IMPLEMENTATION-----------//