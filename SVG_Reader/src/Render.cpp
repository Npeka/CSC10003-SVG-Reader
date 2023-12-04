﻿#include "Render.h"

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
	ellipseRect = Gdiplus::Rect(cx - rx, cy - ry, 2 * rx, 2 * ry);
	brush.SetColor(GDI_Color(fill));
	pen.SetColor(GDI_Color(stroke));
	pen.SetWidth(stroke_width);
}

// Virtual method
void Drawable_Ellipse::draw(Render_Window) {
	graphics.FillEllipse(&brush, ellipseRect);
	graphics.DrawEllipse(&pen, ellipseRect);
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
	pen.SetColor(GDI_Color(stroke));
	pen.SetWidth(stroke_width);
}

// Virtual method
void Drawable_Line::draw(Render_Window) {
	graphics.DrawLine(&pen, p1.x, p1.y, p2.x, p2.y);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawablePolyline
// Private
	// Methods

// Public
// Constructor
void Drawable_Polyline::setAtrribute() {
	points = new Gdiplus::PointF[fpoint.size()];
	for (int i = 0; i < fpoint.size(); i++) {
		points[i].X = fpoint[i].x;
		points[i].Y = fpoint[i].y;
	}
	pen.SetWidth(stroke_width);
	pen.SetColor(GDI_Color(stroke));
	brush.SetColor(GDI_Color(fill));
}

// Virtual method
void Drawable_Polyline::draw(Render_Window) {
	graphics.FillPolygon(&brush, points, fpoint.size());
	graphics.DrawLines(&pen, points, fpoint.size());
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawablePolygon
// Constructor
void Drawable_Polygon::setAtrribute() {
	gdiPoints = new Gdiplus::PointF[point.size()];
	for (size_t i = 0; i < point.size(); ++i) {
		gdiPoints[i] = Gdiplus::PointF((point[i].x), (point[i].y));
	}
	brush.SetColor(GDI_Color(fill));
	pen.SetColor(GDI_Color(stroke));
	pen.SetWidth(stroke_width);
}

// Virtual method
void Drawable_Polygon::draw(Render_Window) {
	if (gdiPoints) {
		graphics.FillPolygon(&brush, gdiPoints, static_cast<int>(point.size()));
		graphics.DrawPolygon(&pen, gdiPoints, static_cast<int>(point.size()));
		delete[] gdiPoints;
	}
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawableText
// Constructor
void Drawable_Text::setAtrribute() {
	this->x = x;
	this->y = y;
	this->font_size = font_size;
	this->font_weight = font_weight;
	this->font_family = font_family;
	this->data = data;

	brush.SetColor(GDI_Color(fill));

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring wideString = converter.from_bytes(font_family);

	Gdiplus::FontFamily fontFamily(wideString.c_str());

	// Create a FontStyle variable 
	Gdiplus::FontStyle fontStyle = Gdiplus::FontStyle::FontStyleRegular;

	if (font_weight == "bold") {
		fontStyle = Gdiplus::FontStyle::FontStyleBold;
	}
	else if (font_weight == "bold") fontStyle = Gdiplus::FontStyle::FontStyleItalic;

	Gdiplus::REAL fontSize = static_cast<Gdiplus::REAL>(font_size);

	Gdiplus::Unit unit = Gdiplus::UnitPoint;

	auto tempFont = std::make_unique<Gdiplus::Font>(&fontFamily, fontSize, fontStyle, unit);

	if (font)
		delete font;
	font = new Gdiplus::Font(&fontFamily, fontSize, fontStyle, unit);
}

// Virtual method
void Drawable_Text::draw(Render_Window) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring wideStringData = converter.from_bytes(data);	
	Gdiplus::PointF position(x, y);
	Gdiplus::FontFamily fontFamily();
	Gdiplus::StringFormat stringFormat;
	
	graphics.DrawString(wideStringData.c_str(), static_cast<INT>(wideStringData.length()), font, position, &brush);
	if (font)
		delete font;
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