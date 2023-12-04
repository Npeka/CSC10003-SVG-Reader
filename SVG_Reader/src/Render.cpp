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

// class DrawableRectangle
// Constructor
void Drawable_Rectangle::setAtrribute() {
	rect = Gdiplus::Rect(x, y, width, height);
	brush.SetColor(GDI_Color(fill));
	pen.SetColor(GDI_Color(stroke));
	pen.SetWidth(stroke_width);
}

// Virtual method
void Drawable_Rectangle::draw(Render_Window) {
	graphics.FillRectangle(&brush, rect);
	graphics.DrawRectangle(&pen, rect);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawableEllipse
// Constructor
void Drawable_Ellipse::setAtrribute() {
	
}

// Virtual method
void Drawable_Ellipse::draw(Render_Window) {
	
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawableCircle
// Constructor
void Drawable_Circle::setAtrribute() {
	brush.SetColor(GDI_Color(fill));
	std::cout << fill.r << fill.g << fill.b << std::endl; 
	pen.SetColor(GDI_Color(stroke));
	pen.SetWidth(stroke_width);
}

// Virtual method
void Drawable_Circle::draw(Render_Window) {
	graphics.DrawEllipse(&pen, cx, cy, r, r);
	graphics.FillEllipse(&brush, cx, cy, r, r);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawableLine

// Constructor
Drawable_Line::Drawable_Line(const Line* other) : Line(*other) {
	
}

void Drawable_Line::setAtrribute() {
	
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
void Drawable_Polyline::setAtrribute() {
	
}

// Virtual method
void Drawable_Polyline::draw(Render_Window) {
	
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawablePolygon
// Constructor
void Drawable_Polygon::setAtrribute() {
	
}

// Virtual method
void Drawable_Polygon::draw(Render_Window) {
	
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawableText
// Constructor
void Drawable_Text::setAtrribute() {
	
}

// Virtual method
void Drawable_Text::draw(Render_Window) {
	
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/

// class SF_Path

// Constructor
void Drawable_Path::setAtrribute() {

	brush.SetColor(GDI_Color(fill));
	pen.SetColor(GDI_Color(stroke));
	pen.SetWidth(stroke_width);

	for (auto x : path) {
		char cmd = x.first; 
		if (cmd == 'V' || cmd == 'H') {
			Gpath.AddLine(x.second[0].x, x.second[0].y, x.second[1].x, x.second[1].y);
			Gpath.AddLine(x.second[2].x, x.second[2].y, x.second[1].x, x.second[1].y);
		}

		else if (cmd == 'c' || cmd == 'C') {
			Gpath.AddBezier(x.second[0].x, x.second[0].y, x.second[1].x, x.second[1].y, x.second[2].x, x.second[2].y, x.second[3].x, x.second[3].y); // add 4 points
		}

		else if (cmd == 'L' || cmd == 'l' || cmd == 'h' || cmd == 'v' || cmd == 'z' || cmd == 'Z') {
			Gpath.AddLine(x.second[0].x, x.second[0].y, x.second[1].x, x.second[1].y); // add 2 points  
		}
	}

}

// Virtual method
void Drawable_Path::draw(Render_Window) {
	graphics.DrawPath(&pen, &Gpath);
	graphics.FillPath(&brush, &Gpath);
}
//-----------END-OF-IMPLEMENTATION-----------//