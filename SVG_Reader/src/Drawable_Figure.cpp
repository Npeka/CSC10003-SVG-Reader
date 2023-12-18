#include "Drawable_Figure.h"

// class Drawable_Rectangle
void Drawable_Rectangle::setDrawableAtrributes() {
	rect = Gdiplus::Rect(x, y, width, height);
	brush = GDI_Brush(fill);
	pen = new Gdiplus::Pen(GDI_Brush(stroke), stroke_width);
	std::cout << dynamic_cast<RGB_Color*>(fill)->opacity << std::endl;
	std::cout << dynamic_cast<RGB_Color*>(stroke)->opacity << std::endl;
}

// Virtual method
void Drawable_Rectangle::draw(Render_Window) {
	Transform_First(transform, graphics);
	if (fill->opacity) graphics.FillRectangle(brush, rect);
	if (stroke->opacity) graphics.DrawRectangle(pen, rect);
	Transform_Second(transform, graphics);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class Drawable_Ellipse
void Drawable_Ellipse::setDrawableAtrributes() {
	ellipseRect = Gdiplus::Rect(cx - rx, cy - ry, 2 * rx, 2 * ry);
	brush = GDI_Brush(fill);
	pen = new Gdiplus::Pen(GDI_Brush(stroke), stroke_width);
}

// Virtual method
void Drawable_Ellipse::draw(Render_Window) {
	Transform_First(transform, graphics);
	if (fill->opacity) graphics.FillEllipse(brush, ellipseRect);
	if (stroke->opacity) graphics.DrawEllipse(pen, ellipseRect);
	Transform_Second(transform, graphics);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class Drawable_Circle
void Drawable_Circle::setDrawableAtrributes() {
	circleRect = Gdiplus::Rect(cx - r, cy - r, 2 * r, 2 * r);
	brush = GDI_Brush(fill);
	pen = new Gdiplus::Pen(GDI_Brush(stroke), stroke_width);
}

// Virtual method
void Drawable_Circle::draw(Render_Window) {
	Transform_First(transform, graphics);
	if (fill->opacity) graphics.FillEllipse(brush, circleRect);
	if (stroke->opacity) graphics.DrawEllipse(pen, circleRect);
	Transform_Second(transform, graphics);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class Drawable_Line
void Drawable_Line::setDrawableAtrributes() {
	pen = new Gdiplus::Pen(GDI_Brush(stroke), stroke_width);
}

// Virtual method
void Drawable_Line::draw(Render_Window) {
	Transform_First(transform, graphics);
	graphics.DrawLine(pen, p1.x, p1.y, p2.x, p2.y);
	Transform_Second(transform, graphics);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class Drawable_Polyline
Drawable_Polyline::Drawable_Polyline() :
	gdiPoints(nullptr)
{}

void Drawable_Polyline::setDrawableAtrributes() {
	gdiPoints = new Gdiplus::PointF[points.size()];
	if (gdiPoints != nullptr) {
		for (int i = 0; i < points.size(); i++) {
			gdiPoints[i].X = points[i].x;
			gdiPoints[i].Y = points[i].y;
		}
	}
	brush = GDI_Brush(fill);
	pen = new Gdiplus::Pen(GDI_Brush(stroke), stroke_width);
}

// Virtual method
void Drawable_Polyline::draw(Render_Window) {
	Transform_First(transform, graphics);
	if (gdiPoints != nullptr) {
		if (fill->opacity) graphics.FillPolygon(brush, gdiPoints, points.size());
		if (stroke->opacity) graphics.DrawLines(pen, gdiPoints, points.size());
	}
	Transform_Second(transform, graphics);
}

Drawable_Polyline::~Drawable_Polyline() {
	if (gdiPoints != nullptr) delete[] gdiPoints;
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class Drawable_Polygon
// Constructor
Drawable_Polygon::Drawable_Polygon() :
	gdiPoints(nullptr)
{}

void Drawable_Polygon::setDrawableAtrributes() {
	gdiPoints = new Gdiplus::PointF[points.size()];
	if (gdiPoints != nullptr) {
		for (int i = 0; i < points.size(); ++i) {
			gdiPoints[i].X = points[i].x;
			gdiPoints[i].Y = points[i].y;
		}
	}
	brush = GDI_Brush(fill);
	pen = new Gdiplus::Pen(GDI_Brush(stroke), stroke_width);
}

// Virtual method
void Drawable_Polygon::draw(Render_Window) {
	Transform_First(transform, graphics);
	if (gdiPoints != nullptr) {
		if (fill->opacity) graphics.FillPolygon(brush, gdiPoints, points.size());
		if (stroke->opacity) graphics.DrawPolygon(pen, gdiPoints, points.size());
	}
	Transform_Second(transform, graphics);
}

Drawable_Polygon::~Drawable_Polygon() {
	if (gdiPoints != nullptr) delete[] gdiPoints;
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class Drawable_Text
void Drawable_Text::setDrawableAtrributes() {
	brush = GDI_Brush(fill);
	pen = new Gdiplus::Pen(GDI_Brush(stroke), stroke_width);

	// Init parameters for TextPath
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	// Check font family
	Gdiplus::InstalledFontCollection installedFontCollection;
	INT count = installedFontCollection.GetFamilyCount(), found = 0;
	WCHAR* familyList = new WCHAR[count * (LF_FACESIZE + 3)]; familyList[0] = L'\0';
	Gdiplus::FontFamily* pFontFamily = new Gdiplus::FontFamily[count];
	installedFontCollection.GetFamilies(count, pFontFamily, &found);

	for (INT i = 0; i < count; i++) {
		WCHAR familyName[LF_FACESIZE];
		pFontFamily[i].GetFamilyName(familyName);
		wcscat_s(familyList, count * (LF_FACESIZE + 3), familyName);
		wcscat_s(familyList, count * (LF_FACESIZE + 3), L", ");
		bool isFontInstalled = (wcsstr(familyList, converter.from_bytes(font_family).c_str()) != nullptr);
		if (isFontInstalled) {
			goto Continue;
		}
	}
	font_family = "Times New Roman";

Continue:
	delete[] pFontFamily;
	delete[] familyList;

	std::wstring			wideData = converter.from_bytes(data);
	INT						DataSize = wideData.size();
	Gdiplus::FontFamily		fontFamily = converter.from_bytes(font_family).c_str();
	Gdiplus::FontStyle		fontStyle = Gdiplus::FontStyle::FontStyleRegular;
	Gdiplus::REAL			fontSize = font_size;
	Gdiplus::PointF			position = { x + dx - font_size / 6, y + dy - font_size * (float)0.895 };
	Gdiplus::Unit			unit = Gdiplus::UnitPixel;
	Gdiplus::StringFormat	stringFormat;

	// Set font style
	if (font_style == "bold") fontStyle = Gdiplus::FontStyle::FontStyleBold;
	else if (font_style == "italic") {
		fontStyle = Gdiplus::FontStyle::FontStyleItalic;
	}

	// Set string format
	stringFormat.SetAlignment(Gdiplus::StringAlignmentNear);
	stringFormat.SetLineAlignment(Gdiplus::StringAlignmentNear);
	if (text_anchor == "middle") {
		stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
		stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
		position.X += 7;
		position.Y += font_size / 2 * 1.3;
	}
	else if (text_anchor == "end") {
		stringFormat.SetAlignment(Gdiplus::StringAlignmentFar);
		stringFormat.SetLineAlignment(Gdiplus::StringAlignmentFar);
		position.X += 14;
		position.Y += font_size * 1.28; //+ 11.5;
	}

	// Add string to TextPath
	TextPath.AddString(
		wideData.c_str(),	// Data wstring -> wchar
		DataSize,			// Data size
		&fontFamily,		// Font family
		fontStyle,			// Font style	
		fontSize, 			// Font size
		position,			// Position
		&stringFormat		// String format
	);
}

// Virtual method
void Drawable_Text::draw(Render_Window) {
	// Set text graphics
	graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
	graphics.SetTextContrast(200);
	// Draw text
	Transform_First(transform, graphics);
	if (fill->opacity) graphics.FillPath(brush, &TextPath);
	if (stroke->opacity) graphics.DrawPath(pen, &TextPath);
	Transform_Second(transform, graphics);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class Drawable_Path
void Drawable_Path::setDrawableAtrributes() {
	brush = GDI_Brush(fill);
	pen = new Gdiplus::Pen(GDI_Brush(stroke), stroke_width);

	countSubpath = 0;
	for (auto x : path) {
		if (x.first == 'z' || x.first == 'Z') countSubpath++;
	}
	if (countSubpath == 0) countSubpath = 1;

	Gdiplus::GraphicsPath* subpath = new Gdiplus::GraphicsPath[countSubpath + path.size()];

	int idx = 0;

	for (auto x : path) {
		char cmd = x.first;

		if (cmd == 'c' || cmd == 'C' || cmd == 's' || cmd == 'S') {
			subpath[idx].AddBezier(x.second[0].x, x.second[0].y, x.second[1].x, x.second[1].y, x.second[2].x, x.second[2].y, x.second[3].x, x.second[3].y); // add 4 points
		}

		else if (cmd == 'L' || cmd == 'l' || cmd == 'h' || cmd == 'v' || cmd == 'H' || cmd == 'V') {
			subpath[idx].AddLine(x.second[0].x, x.second[0].y, x.second[1].x, x.second[1].y);
		}
		else if (cmd == 'z' || cmd == 'Z') {
			subpath[idx].AddLine(x.second[1].x, x.second[1].y, x.second[0].x, x.second[0].y);
			idx++;
		}

		else if (cmd == 't' || cmd == 'T' || cmd == 'q' || cmd == 'Q') {
			Gdiplus::Point* points = new Gdiplus::Point[3];
			for (int i = 0; i < 3; i++) {
				points[i].X = x.second[i].x;
				points[i].Y = x.second[i].y;
			}
			subpath[idx].AddCurve(points, 3);
		}

		else if (cmd == 'a' || cmd == 'A') {

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

	if (subpath != nullptr) delete[] subpath;
}

// Virtual method
void Drawable_Path::draw(Render_Window) {
	Transform_First(transform, graphics);
	if (fill->opacity) graphics.FillPath(brush, &Gpath);
	if (stroke->opacity) graphics.DrawPath(pen, &Gpath);
	Transform_Second(transform, graphics);
}
//-----------END-OF-IMPLEMENTATION-----------//