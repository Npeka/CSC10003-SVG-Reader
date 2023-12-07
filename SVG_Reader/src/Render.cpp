#include "Render.h"

Gdiplus::Color GDI_Color(const Color& color) {
	return Gdiplus::Color(color.a, color.r, color.g, color.b);
}

void Transform_First(const std::vector <std::pair <int, Point>>& t, Render_Window) {
	for (int i = 0; i < t.size(); ++i) {
		if (t[i].first == SVG_Translate) {
			graphics.TranslateTransform(t[i].second.x, t[i].second.y);
		}
		else if (t[i].first == SVG_Rotate) {
			graphics.RotateTransform(t[i].second.x);
		}
		else if (t[i].first == SVG_Scale) {
			graphics.ScaleTransform(t[i].second.x, t[i].second.y);
		}
	}
}

void Transform_Second(const std::vector <std::pair <int, Point>>& t, Render_Window) {
	for (int i = t.size() - 1; i >= 0; --i) {
		if (t[i].first == SVG_Translate) {
			graphics.TranslateTransform(-t[i].second.x, -t[i].second.y);
		}
		else if (t[i].first == SVG_Rotate) {
			graphics.RotateTransform(-t[i].second.x);
		}
		else if (t[i].first == SVG_Scale) {
			graphics.ScaleTransform(1 / t[i].second.x, 1 / t[i].second.y);
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
	Transform_First(transform, graphics);
	graphics.FillRectangle(&brush, rect);
	graphics.DrawRectangle(&pen, rect);
	Transform_Second(transform, graphics);
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
	Transform_First(transform, graphics);
	graphics.FillEllipse(&brush, ellipseRect);
	graphics.DrawEllipse(&pen, ellipseRect);
	Transform_Second(transform, graphics);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawableCircle
// Constructor
void Drawable_Circle::setAtrribute() {
	brush.SetColor(GDI_Color(fill));
	pen.SetColor(GDI_Color(stroke));
	pen.SetWidth(stroke_width);
}

// Virtual method
void Drawable_Circle::draw(Render_Window) {
	Transform_First(transform, graphics);
	graphics.DrawEllipse(&pen, cx - r, cy - r, r * 2, r * 2);
	graphics.FillEllipse(&brush, cx - r, cy - r, r * 2, r * 2);
	Transform_Second(transform, graphics);
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
	Transform_First(transform, graphics);
	graphics.DrawLine(&pen, p1.x, p1.y, p2.x, p2.y);
	Transform_Second(transform, graphics);
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
	Transform_First(transform, graphics);
	graphics.FillPolygon(&brush, points, fpoint.size());
	graphics.DrawLines(&pen, points, fpoint.size());
	Transform_Second(transform, graphics);
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
	Transform_First(transform, graphics);
	if (gdiPoints) {
		graphics.FillPolygon(&brush, gdiPoints, static_cast<int>(point.size()));
		graphics.DrawPolygon(&pen, gdiPoints, static_cast<int>(point.size()));
		delete[] gdiPoints;
	}
	Transform_Second(transform, graphics);
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
	this->font_style = font_style;
	this->font_family = font_family;
	this->data = data;

	brush.SetColor(GDI_Color(fill));

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring wideString = converter.from_bytes(font_family);

	Gdiplus::FontFamily fontFamily(wideString.c_str());

	// Create a FontStyle variable 
	Gdiplus::FontStyle fontStyle = Gdiplus::FontStyle::FontStyleRegular;

	if (font_style == "bold") {
		fontStyle = Gdiplus::FontStyle::FontStyleBold;
	}
	else if (font_style == "italic") fontStyle = Gdiplus::FontStyle::FontStyleItalic;

	Gdiplus::REAL fontSize = static_cast<Gdiplus::REAL>(font_size);

	Gdiplus::Unit unit = Gdiplus::UnitPixel;

	auto tempFont = std::make_unique<Gdiplus::Font>(&fontFamily, fontSize, fontStyle, unit);

	if (font)
		delete font;
	font = new Gdiplus::Font(&fontFamily, fontSize, fontStyle, unit);
}

// Virtual method
void Drawable_Text::draw(Render_Window) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring wideStringData = converter.from_bytes(data);	

	
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converterFontFamily;
	std::wstring wideString = converterFontFamily.from_bytes(font_family);
	Gdiplus::FontFamily fontFamily(wideString.c_str());

	Gdiplus::StringFormat stringFormat;
	stringFormat.SetAlignment(Gdiplus::StringAlignmentNear);
	stringFormat.SetLineAlignment(Gdiplus::StringAlignmentNear);
	if (text_anchor == "middle" || text_anchor == "end") {
		Gdiplus::RectF layoutRect;
		Gdiplus::PointF origin(x, y); // Adjust the origin based on your requirements

		graphics.MeasureString(wideStringData.c_str(), static_cast<INT>(wideStringData.length()), font, origin, &stringFormat, &layoutRect);

		float textHeight = layoutRect.Height;

		if (text_anchor == "middle") {
			stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
			stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
			y += 1.1 * textHeight / 2;
		}
		else if (text_anchor == "end") {
			stringFormat.SetAlignment(Gdiplus::StringAlignmentFar);
			stringFormat.SetLineAlignment(Gdiplus::StringAlignmentFar);
			y += 1.1 * textHeight;
		}
	}

	Gdiplus::PointF position(x, y - font_size);

	graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
	Gdiplus::FontStyle fontStyle = Gdiplus::FontStyle::FontStyleRegular;
	if (font_style == "bold") {
		fontStyle = Gdiplus::FontStyle::FontStyleBold;
	}
	else if (font_style == "italic") fontStyle = Gdiplus::FontStyle::FontStyleItalic;
	Gdiplus::GraphicsPath path;
	path.AddString(
		wideStringData.c_str(),
		static_cast<INT>(wideStringData.length()),
		&fontFamily,
		static_cast<INT>(fontStyle),
		static_cast<Gdiplus::REAL>(font_size),
		position,
		&stringFormat
	);
	// Create a pen for the outline
	Gdiplus::Pen pen(GDI_Color(stroke), stroke_width);
	// Draw the outline
	Transform_First(transform, graphics);
	
	graphics.DrawString(wideStringData.c_str(), static_cast<INT>(wideStringData.length()), font, position, &stringFormat, &brush);
	graphics.DrawPath(&pen, &path);	
		
	Transform_Second(transform, graphics);

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

	countSubpath = 0; 
	for (auto x : path) {
		if (x.first == 'z' || x.first == 'Z') countSubpath++;
	}

	Gdiplus::GraphicsPath* subpath;
	subpath = new Gdiplus::GraphicsPath[countSubpath];
	
	int idx = 0; 

	for (auto x : path) {
		char cmd = x.first; 

		if (cmd == 'c' || cmd == 'C') {
			subpath[idx].AddBezier(x.second[0].x, x.second[0].y, x.second[1].x, x.second[1].y, x.second[2].x, x.second[2].y, x.second[3].x, x.second[3].y); // add 4 points
		}

		else if (cmd == 'L' || cmd == 'l' || cmd == 'h' || cmd == 'v' || cmd == 'H' || cmd == 'V') {
			subpath[idx].AddLine(x.second[0].x, x.second[0].y, x.second[1].x, x.second[1].y);
		}
		else if (cmd == 'z' || cmd == 'Z') {
			subpath[idx].AddLine(x.second[1].x, x.second[1].y, x.second[0].x, x.second[0].y);
			idx++;
		}

		else if (cmd == 'M' || cmd == 'm') {
			for (int i = 0; i < x.second.size() - 1; i++) {
				subpath[idx].AddLine(x.second[i].x, x.second[i].y, x.second[i + 1].x, x.second[i + 1].y);
			}
		}
	}

	for (int i = 0; i < countSubpath; i++) {
		Gpath.AddPath(&subpath[i], FALSE);
	}
}

// Virtual method
void Drawable_Path::draw(Render_Window) {
	Transform_First(transform, graphics);
	graphics.DrawPath(&pen, &Gpath);
	graphics.FillPath(&brush, &Gpath);
	Transform_Second(transform, graphics);
}
//-----------END-OF-IMPLEMENTATION-----------//