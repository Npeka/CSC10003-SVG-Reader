#include "Drawable_Figure.h"

// class Drawable_Rectangle
void Drawable_Rectangle::setDrawableAtrributes() {
	rect = Gdiplus::RectF(x, y, width, height);
	brush = GDI_Brush(fill, rect);
	pen = GDI_Pen(stroke, stroke_width, rect);
}

// Virtual method
void Drawable_Rectangle::draw(Render_Window) {
	Transform_First(transforms, graphics);
	if (fill->opacity) graphics.FillRectangle(brush, rect);
	if (stroke->opacity) graphics.DrawRectangle(pen, rect);
	Transform_Second(transforms, graphics);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class Drawable_Ellipse
void Drawable_Ellipse::setDrawableAtrributes() {
	ellipseRect = Gdiplus::RectF(cx - rx, cy - ry, 2 * rx, 2 * ry);
	brush = GDI_Brush(fill, ellipseRect);
	pen = GDI_Pen(stroke, stroke_width, ellipseRect);
}

// Virtual method
void Drawable_Ellipse::draw(Render_Window) {
	Transform_First(transforms, graphics);
	if (fill->opacity) graphics.FillEllipse(brush, ellipseRect);
	if (stroke->opacity) graphics.DrawEllipse(pen, ellipseRect);
	Transform_Second(transforms, graphics);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class Drawable_Circle
void Drawable_Circle::setDrawableAtrributes() {
	circleRect = Gdiplus::RectF(cx - r, cy - r, 2 * r, 2 * r);
	brush = GDI_Brush(fill, circleRect);
	pen = GDI_Pen(stroke, stroke_width, circleRect);
}

// Virtual method
void Drawable_Circle::draw(Render_Window) {
	Transform_First(transforms, graphics);
	if (fill->opacity) graphics.FillEllipse(brush, circleRect);
	if (stroke->opacity) graphics.DrawEllipse(pen, circleRect);
	Transform_Second(transforms, graphics);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class Drawable_Line
void Drawable_Line::setDrawableAtrributes() {
	Gdiplus::GraphicsPath path; path.AddLine(p1.x, p1.y, p2.x, p2.y);
	Gdiplus::RectF rect; path.GetBounds(&rect);
	pen = GDI_Pen(stroke, stroke_width, rect);
}

// Virtual method
void Drawable_Line::draw(Render_Window) {
	Transform_First(transforms, graphics);
	graphics.DrawLine(pen, p1.x, p1.y, p2.x, p2.y);
	Transform_Second(transforms, graphics);
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

	Gdiplus::GraphicsPath path; path.AddPolygon(gdiPoints, points.size());
	Gdiplus::RectF rect; path.GetBounds(&rect);
	brush = GDI_Brush(fill, rect);
	pen = GDI_Pen(stroke, stroke_width, rect);
}

// Virtual method
void Drawable_Polyline::draw(Render_Window) {
	Transform_First(transforms, graphics);
	if (gdiPoints != nullptr) {
		if (fill->opacity) graphics.FillPolygon(brush, gdiPoints, points.size());
		if (stroke->opacity) graphics.DrawLines(pen, gdiPoints, points.size());
	}
	Transform_Second(transforms, graphics);
}

Drawable_Polyline::~Drawable_Polyline() {
	dealocate(gdiPoints);
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

	Gdiplus::GraphicsPath path; path.AddPolygon(gdiPoints, points.size());
	Gdiplus::RectF rect; path.GetBounds(&rect);
	brush = GDI_Brush(fill, rect);
	pen = GDI_Pen(stroke, stroke_width, rect);
}

// Virtual method
void Drawable_Polygon::draw(Render_Window) {
	Transform_First(transforms, graphics);
	if (gdiPoints != nullptr) {
		if (fill->opacity) graphics.FillPolygon(brush, gdiPoints, points.size());
		if (stroke->opacity) graphics.DrawPolygon(pen, gdiPoints, points.size());
	}
	Transform_Second(transforms, graphics);
}

Drawable_Polygon::~Drawable_Polygon() {
	dealocate(gdiPoints);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class Drawable_Text
void Drawable_Text::setDrawableAtrributes() {
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

	// Set graphics
	Gdiplus::RectF rect; TextPath.GetBounds(&rect);
	brush = GDI_Brush(fill, rect);
	pen = GDI_Pen(stroke, stroke_width, rect);
}

// Virtual method
void Drawable_Text::draw(Render_Window) {
	// Set text graphics
	graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
	graphics.SetTextContrast(200);
	// Draw text
	Transform_First(transforms, graphics);
	if (fill->opacity) graphics.FillPath(brush, &TextPath);
	if (stroke->opacity) graphics.DrawPath(pen, &TextPath);
	Transform_Second(transforms, graphics);
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class Drawable_Path

float Drawable_Path::computeBinominal(int n, int k) {
	float value = 1.0;

	for (float i = 1; i <= k; i++) {
		value = value * ((n + 1 - i) / i);
	}

	if (n == k) {
		value = 1;
	}

	return value;
}

vector<Point> Drawable_Path::BezierCurveVertices(vector<Point> Position, float smooth) {
	vector<Point> CurvePositions;

	int n = Position.size() - 1;

	for (float t = 0.0; t <= 1.0; t += smooth)
	{
		Point CurvePos = { 0.0, 0.0 };

		for (int i = 0; i <= n; ++i) {
			CurvePos.x += computeBinominal(n, i) * pow((1 - t), (n - i)) * pow(t, i) * Position[i].x;
			CurvePos.y += computeBinominal(n, i) * pow((1 - t), (n - i)) * pow(t, i) * Position[i].y;
		}

		CurvePositions.push_back(CurvePos);
	}

	return CurvePositions;
}

float Drawable_Path::radian(float ux, float uy, float vx, float vy) {
	float  dot = ux * vx + uy * vy;
	float  mod = sqrt((ux * ux + uy * uy) * (vx * vx + vy * vy));
	float  rad = acos(dot / mod);
	if (ux * vy - uy * vx < 0.0) {
		rad = -rad;
	}
	return rad;
}

void Drawable_Path::setDrawableAtrributes() {
	for (int i = 0; i < path.size(); i++) {
		char cmd = path[i].first;
		vector<float> point = path[i].second;
		
		if (cmd == 'M' || cmd == 'm') {
			Gpath.StartFigure();
		}

		else if (cmd == 'z' || cmd == 'Z') {
			Gpath.CloseFigure();
		}

		else if (string("CcSs").find(cmd) != string::npos) {
			Gpath.AddBezier(
				point[0], point[1], point[2], point[3],
				point[4], point[5], point[6], point[7]
			); // add 4 points
		}

		else if (string("LHVlhv").find(cmd) != string::npos) {
			Gpath.AddLine(
				point[0], point[1], point[2], point[3]
			);
		}

		else if (string("TQtq").find(cmd) != string::npos) {
			vector<Point> tmp;
			for (int i = 0; i < point.size(); i += 2) {
				tmp.push_back({ point[i], point[i + 1] });
			}
			tmp = BezierCurveVertices(tmp, 0.1);

			int tmpSize = tmp.size();
			Gdiplus::PointF* points = new Gdiplus::PointF[tmpSize];
			for (int j = 0; j < tmpSize; j++) {
				points[j] = { tmp[j].x, tmp[j].y };
				
			}
			Gpath.AddCurve(points, tmpSize);
		}

		else if (cmd == 'A' || cmd == 'a') {
			Point start_point{ point[0], point[1] };
			Point end_point{ point[7], point[8] };
			float rx = point[2];
			float ry = point[3];
			float x_axis_rotation = point[4];
			bool large_arc_flag = point[5];
			bool sweep_flag = point[6];

			float cx, cy, startAngle, deltaAngle, endAngle;
			float PIx2 = M_PI * 2.0;
			float phi = x_axis_rotation * M_PI / 180;

			if (rx < 0) {
				rx = -rx;
			}
			if (ry < 0) {
				ry = -ry;
			}

			// SVG use degrees, if your input is degree from svg,
			// you should convert degree to radian as following line.
			// phi = phi * Math.PI / 180;
			Point start = { point[0], point[1] };
			Point end = { point[7], point[8] };

			float s_phi = sin(phi);
			float c_phi = cos(phi);
			float hd_x = (start.x - end.x) / 2.0; // half diff of x
			float hd_y = (start.y - end.y) / 2.0; // half diff of y
			float hs_x = (start.x + end.x) / 2.0; // half sum of x
			float hs_y = (start.y + end.y) / 2.0; // half sum of y

			// F6.5.1
			float x1_ = c_phi * hd_x + s_phi * hd_y;
			float y1_ = c_phi * hd_y - s_phi * hd_x;

			// F.6.6 Correction of out-of-range radii
			//   Step 3: Ensure radii are large enough
			float lambda = (x1_ * x1_) / (rx * rx) + (y1_ * y1_) / (ry * ry);
			if (lambda > 1) {
				rx = rx * sqrt(lambda);
				ry = ry * sqrt(lambda);
			}

			float rxry = rx * ry;
			float rxy1_ = rx * y1_;
			float ryx1_ = ry * x1_;
			float sum_of_sq = rxy1_ * rxy1_ + ryx1_ * ryx1_; // sum of square
			float coe = sqrt(abs((rxry * rxry - sum_of_sq) / sum_of_sq));
			if (large_arc_flag == sweep_flag) { coe = -coe; }

			// F6.5.2
			float cx_ = coe * rxy1_ / ry;
			float cy_ = -coe * ryx1_ / rx;

			// F6.5.3
			cx = c_phi * cx_ - s_phi * cy_ + hs_x;
			cy = s_phi * cx_ + c_phi * cy_ + hs_y;
		
			float xcr1 = (x1_ - cx_) / rx;
			float xcr2 = (x1_ + cx_) / rx;
			float ycr1 = (y1_ - cy_) / ry;
			float ycr2 = (y1_ + cy_) / ry;

			// F6.5.5
			startAngle = radian(1.0, 0.0, xcr1, ycr1);

			// F6.5.6
			deltaAngle = radian(xcr1, ycr1, -xcr2, -ycr2);
			while (deltaAngle > PIx2) { deltaAngle -= PIx2; }
			while (deltaAngle < 0.0) { deltaAngle += PIx2; }
			if (sweep_flag == false || sweep_flag == 0) { deltaAngle -= PIx2; }
			endAngle = startAngle + deltaAngle;
			while (endAngle > PIx2) { endAngle -= PIx2; }
			while (endAngle < 0.0) { endAngle += PIx2; }

			Gdiplus::GraphicsPath arcPath;
			arcPath.AddArc(
				cx - rx,
				cy - ry,
				rx * 2,
				ry * 2,
				startAngle * 180 / M_PI - x_axis_rotation,
				deltaAngle * 180 / M_PI + x_axis_rotation
			);

			Gdiplus::Matrix matrix;
			matrix.RotateAt(x_axis_rotation, Gdiplus::PointF(cx, cy));
			arcPath.Transform(&matrix);
			Gpath.AddPath(&arcPath, true);	
		}
	}

	Gdiplus::RectF rect; Gpath.GetBounds(&rect); rect.X = 0, rect.Y = 0;
	brush = GDI_Brush(fill, rect);
	pen = GDI_Pen(stroke, stroke_width, rect);

	if (auto it = dynamic_cast<RadialGradient*>(fill)) {
		RGB_Color* color = new RGB_Color(
			it->getColorOffset()[it->getColorOffset().size() - 1].getColor()
		);
		solidBrush = GDI_Brush(color, rect);

		float cx = it->getCX();
		float cy = it->getCY();
		float r = it->getR();

		Transform_Type t = it->getTransform();
		Gdiplus::GraphicsPath path;
		path.AddEllipse(Gdiplus::RectF(cx - r, cy - r, r * 2, r * 2));
		for (int i = 0; i < t.size(); ++i) {
			if (t[i].first == SVG_Matrix) {
				Gdiplus::Matrix matrix(
					t[i].second[0], t[i].second[1], t[i].second[2],
					t[i].second[3], t[i].second[4], t[i].second[5]
				);
				path.Transform(&matrix);
			}
		}

		region = new Gdiplus::Region(&Gpath);
		region->Exclude(&path);
	}
}

// Virtual method
void Drawable_Path::draw(Render_Window) {
	Transform_First(transforms, graphics);
	if (fill->opacity) {
		if (solidBrush) graphics.FillRegion(solidBrush, region);
		graphics.FillPath(brush, &Gpath);
	}
	if (stroke->opacity) graphics.DrawPath(pen, &Gpath);
	Transform_Second(transforms, graphics);
}
//-----------END-OF-IMPLEMENTATION-----------//