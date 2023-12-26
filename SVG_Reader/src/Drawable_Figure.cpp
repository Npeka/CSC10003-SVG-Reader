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
Point Drawable_Path::mapToEllipse(const Point& point, float rx, float ry, float cosphi, float sinphi, float centerx, float centery) {
	float x = point.x * rx;
	float y = point.y * ry;

	float xp = cosphi * x - sinphi * y;
	float yp = sinphi * x + cosphi * y;

	return { xp + centerx, yp + centery };
}

vector<Point> Drawable_Path::approxUnitArc(float ang1, float ang2) {
	float a;
	if (fabs(ang2) - 1.5707963267948966 < 0.001) {
		a = 0.551915024494;
	}
	else if (fabs(ang2) - 1.5707963267948966 < 0.001) {
		a = -0.551915024494;
	}
	else {
		a = 4.0 / 3.0 * tanf(ang2 / 4.0);
	}

	float x1 = cosf(ang1);
	float y1 = sinf(ang1);
	float x2 = cosf(ang1 + ang2);
	float y2 = sinf(ang1 + ang2);

	return {
		{x1 - y1 * a, y1 + x1 * a},
		{x2 + y2 * a, y2 - x2 * a},
		{x2, y2}
	};
}

float Drawable_Path::vectorAngle(float ux, float uy, float vx, float vy) {
	float sign = (ux * vy - uy * vx < 0.0) ? -1.0 : 1.0;

	float dot = ux * vx + uy * vy;

	if (dot > 1) {
		dot = 1;
	}

	if (dot < -1) {
		dot = -1;
	}

	return sign * acos(dot);
}

std::tuple<float, float, float, float> Drawable_Path::getArcCenter(
	float px, float py,
	float cx, float cy,
	float rx, float ry,
	int largeArcFlag, int sweepFlag,
	float sinphi, float cosphi,
	float pxp, float pyp
) {
	float rxsq = powf(rx, 2);
	float rysq = powf(ry, 2);
	float pxpsq = powf(pxp, 2);
	float pypsq = powf(pyp, 2);

	float radicant = (rxsq * rysq) - (rxsq * pypsq) - (rysq * pxpsq);

	if (radicant < 0) {
		radicant = 0;
	}

	radicant /= (rxsq * pypsq) + (rysq * pxpsq);
	radicant = sqrt(radicant) * (largeArcFlag == sweepFlag ? -1 : 1);

	float centerxp = radicant * rx / ry * pyp;
	float centeryp = radicant * -ry / rx * pxp;

	float centerx = cosphi * centerxp - sinphi * centeryp + (px + cx) / 2;
	float centery = sinphi * centerxp + cosphi * centeryp + (py + cy) / 2;

	float vx1 = (pxp - centerxp) / rx;
	float vy1 = (pyp - centeryp) / ry;
	float vx2 = (-pxp - centerxp) / rx;
	float vy2 = (-pyp - centeryp) / ry;

	float ang1 = vectorAngle(1.0f, 0.0f, vx1, vy1);
	float ang2 = vectorAngle(vx1, vy1, vx2, vy2);

	if (sweepFlag == 0 && ang2 > 0) {
		ang2 -= TAU;
	}

	if (sweepFlag == 1 && ang2 < 0) {
		ang2 += TAU;
	}

	return { centerx, centery, ang1, ang2 };
}


vector<BezierCurve> Drawable_Path::arcToBezier(
	float px, float py,
	float cx, float cy,
	float rx, float ry,
	float xAxisRotation = 0,
	int largeArcFlag = 0,
	int sweepFlag = 0
) {
	vector<BezierCurve> curves;

	if (rx == 0 || ry == 0) {
		return curves;
	}

	float sinphi = sin(xAxisRotation * TAU / 360.0f);
	float cosphi = cos(xAxisRotation * TAU / 360.0f);

	float pxp = cosphi * (px - cx) / 2 + sinphi * (py - cy) / 2;
	float pyp = -sinphi * (px - cx) / 2 + cosphi * (py - cy) / 2;

	if (pxp == 0 && pyp == 0) {
		return curves;
	}

	rx = fabs(rx);
	ry = fabs(ry);

	float lambda = (pxp * pxp) / (rx * rx) + (pyp * pyp) / (ry * ry);

	if (lambda > 1) {
		rx *= sqrt(lambda);
		ry *= sqrt(lambda);
	}

	float centerx, centery, ang1, ang2;
	// Here, you'd need to implement or integrate the getArcCenter function to compute these values.
	std::tie(centerx, centery, ang1, ang2) = getArcCenter(
		px, py, cx, cy, rx, ry, largeArcFlag, sweepFlag, sinphi, cosphi, pxp, pyp
	);

	float ratio = fabs(ang2) / (TAU / 4.0f);
	if (fabs(1.0f - ratio) < 0.0000001f) {
		ratio = 1.0f;
	}

	int segments = max(static_cast<int>(ceil(ratio)), 1);
	ang2 /= segments;

	for (int i = 0; i < segments; i++) {
		std::vector<Point> arcSegmentPoints = approxUnitArc(ang1, ang2);

		// Convert these points to Bezier curves using the mapToEllipse function.
		Point p1 = mapToEllipse(arcSegmentPoints[0], rx, ry, cosphi, sinphi, centerx, centery);
		Point p2 = mapToEllipse(arcSegmentPoints[1], rx, ry, cosphi, sinphi, centerx, centery);
		Point p3 = mapToEllipse(arcSegmentPoints[2], rx, ry, cosphi, sinphi, centerx, centery);

		BezierCurve bezierCurve = { p1, p2, p3 };

		curves.push_back(bezierCurve);
		ang1 += ang2;
	}

	return curves;
}


Point Drawable_Path::EllipticArcControlPoint2(Point c, Point r, float xAngle, float t) {
	Point p0 = EllipticArcPoint(c, r, xAngle, 0.0f);       // P0
	Point p2 = EllipticArcPoint(c, r, xAngle, 2.0 * M_PI);  // P2
	Point derivative = EllipticArcDerivative(c, r, xAngle, t);
	Point midpoint = EllipticArcPoint(c, r, xAngle, t);
	return Point(2 * midpoint.x - 0.5f * (p0.x + p2.x),
		2 * midpoint.y - 0.5f * (p0.y + p2.y));
}


Point Drawable_Path::EllipticArcControlPoint(Point c, Point r, float xAngle, float t) {
	Point p0 = EllipticArcPoint(c, r, xAngle, 0.0f);       // P0
	Point p2 = EllipticArcPoint(c, r, xAngle, 2.0 * M_PI);  // P2
	Point derivative = EllipticArcDerivative(c, r, xAngle, t);
	Point midpoint = EllipticArcPoint(c, r, xAngle, t);
	return Point(2 * midpoint.x - 0.5f * (p0.x + p2.x),
		2 * midpoint.y - 0.5f * (p0.y + p2.y));
}


Point Drawable_Path::EllipticArcPoint(Point c, Point r, float xAngle, float t) {
	return Point(
		c.x + r.x * cos(xAngle) * cos(t) - r.y * sin(xAngle) * sin(t),
		c.y + r.x * sin(xAngle) * cos(t) + r.y * cos(xAngle) * sin(t)
	);
}

Point Drawable_Path::EllipticArcDerivative(Point c, Point r, float xAngle, float t) {
	return Point(
		-r.x * cos(xAngle) * sin(t) - r.y * sin(xAngle) * cos(t),
		-r.x * sin(xAngle) * sin(t) + r.y * cos(xAngle) * cos(t)
	);
}

float Drawable_Path::computeBinominal(int n, int k) {
	float value = 1.0;

	for (int i = 1; i <= k; i++)
	{

		value = value * ((n + 1 - i) / i);
	}

	if (n == k) {
		value = 1;
	}

	return value;
}

vector<Point> Drawable_Path::BezierCurveVertices(std::vector<Point> Position, float smooth) {
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

Point Drawable_Path::ellipseCenter(float cx, float cy, float rx, float ry, float xAxisRotation) {
	float cosphi = cos(xAxisRotation * TAU / 360.0f);
	float sinphi = sin(xAxisRotation * TAU / 360.0f);

	float centerx = cosphi * cx - sinphi * cy;
	float centery = sinphi * cx + cosphi * cy;

	return { centerx, centery };
}

Point Drawable_Path::pointOnEllipse(float cx, float cy, float rx, float ry, float angle) {
	float x = cx + rx * cos(angle);
	float y = cy + ry * sin(angle);
	return { x, y };
}

vector<BezierCurve> Drawable_Path::arcToBezier(float cx, float cy, float rx, float ry, float startAngle, float endAngle, float xAxisRotation) {
	vector<BezierCurve> curves;

	// Tính trung tâm của ellipse
	Point center = ellipseCenter(cx, cy, rx, ry, xAxisRotation);

	// Tính tọa độ của điểm bắt đầu và kết thúc trên ellipse
	Point startPoint = pointOnEllipse(cx, cy, rx, ry, startAngle);
	Point endPoint = pointOnEllipse(cx, cy, rx, ry, endAngle);

	// Tính các điểm control dựa trên tọa độ của điểm bắt đầu và kết thúc, cũng như trung tâm của ellipse
	Point control1 = { startPoint.x + (2.0f / 3.0f) * (center.x - startPoint.x), startPoint.y + (2.0f / 3.0f) * (center.y - startPoint.y) };
	Point control2 = { endPoint.x + (2.0f / 3.0f) * (center.x - endPoint.x), endPoint.y + (2.0f / 3.0f) * (center.y - endPoint.y) };

	// Tạo đường cong Bézier từ điểm bắt đầu, điểm kết thúc và hai điểm control
	BezierCurve bezierCurve = { startPoint, control1, control2, endPoint };
	curves.push_back(bezierCurve);

	return curves;
}

void Drawable_Path::setDrawableAtrributes() {
	countSubpath = 0;
	for (auto x : path) {
		if (x.first == 'z' || x.first == 'Z') countSubpath++;
	}
	if (countSubpath == 0) countSubpath = 1;

	Gdiplus::GraphicsPath* subpath = new Gdiplus::GraphicsPath[countSubpath + path.size()];

	int idx = 0;

	for (int i = 0; i < path.size(); i++) {
		pair<char, vector<Point>> x = path[i];
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
			std::vector<Point> tmp = BezierCurveVertices(x.second, 0.1);
			int tmpSize = tmp.size();
			Gdiplus::Point* points = new Gdiplus::Point[tmpSize];
			for (int j = 0; j < tmpSize; j++) {
				points[j].X = tmp[j].x;
				points[j].Y = tmp[j].y;
			}
			subpath[idx].AddCurve(points, tmpSize);
		}

		else if (cmd == 'a' || cmd == 'A') {

			Point start_point{ x.second[0].x, x.second[0].y };
			float rx = x.second[1].x;
			float ry = x.second[1].y;
			float x_axis_rotation = x.second[2].x;
			bool large_arc_flag = x.second[3].x;
			bool sweep_flag = x.second[3].y;

			Point end_point{ x.second[4].x, x.second[4].y };

			float angle = x_axis_rotation * static_cast<float>(M_PI) / 180.0;
			float cosAngle = cos(angle);
			float sinAngle = sin(angle);

			Point point1;
			float constant = cosAngle * cosAngle - (sinAngle * -sinAngle);
			point1.x = constant * (x.second[0].x - end_point.x) / 2.0;
			point1.y = constant * (x.second[0].y - end_point.y) / 2.0;

			float radii_check = (point1.x * point1.x) / (rx * rx) +
				(point1.y * point1.y) / (ry * ry);

			if (radii_check > 1.0) {
				rx = std::sqrt(radii_check) * rx;
				ry = std::sqrt(radii_check) * ry;
			}

			int sign = (large_arc_flag == sweep_flag ? -1 : 1);
			Point point2;

			float numo = (rx * rx) * (ry * ry) -
				(rx * rx) * (point1.y * point1.y) -
				(ry * ry) * (point1.x * point1.x);
			float deno = (rx * rx) * (point1.y * point1.y) +
				(ry * ry) * (point1.x * point1.x);

			if (numo < 0) {
				numo = std::abs(numo);
			}

			point2.x = sign * std::sqrt(numo / deno) * (rx * point1.y / ry);
			point2.y = sign * std::sqrt(numo / deno) * (-ry * point1.x / rx);

			Point center;
			constant = cosAngle * cosAngle - (sinAngle * -sinAngle);
			center.x = constant * point2.x + (x.second[0].x + end_point.x) / 2.0;
			center.y = constant * point2.y + (x.second[0].y + end_point.y) / 2.0;

			float startAngle =
				atan2((point1.y - point2.y) / ry, (point1.x - point2.x) / rx);
			float endAngle =
				atan2((-point1.y - point2.y) / ry, (-point1.x - point2.x) / rx);

			float deltaAngle = endAngle - startAngle;

			if (sweep_flag && deltaAngle < 0) {
				deltaAngle += 2.0 * M_PI;
			}
			else if (!sweep_flag && deltaAngle > 0) {
				deltaAngle -= 2.0 * M_PI;
			}

			subpath[idx].AddArc(
				center.x - rx, center.y - ry, rx * 2, ry * 2,
				fmod((startAngle * 180.0) / M_PI, 360),
				fmod((deltaAngle * 180.0) / M_PI, 360)
			);
			/*
			std::vector<BezierCurve> curves = arcToBezier(
				start_point.x, start_point.y,
				end_point.x, end_point.y,
				rx, ry,
				x_axis_rotation,
				large_arc_flag,
				sweep_flag
			);*/
		}

		else if (cmd == 'M' || cmd == 'm') {
			for (int j = 0; j < x.second.size() - 1; j++) {
				subpath[idx].AddLine(x.second[j].x, x.second[j].y, x.second[j + 1].x, x.second[j + 1].y);
			}
			if (i != path.size() - 1)
				if (path[i + 1].first == 'M' || path[i + 1].first == 'm') idx++;
		}
	}

	for (int i = 0; i < countSubpath; i++) {
		Gpath.AddPath(&subpath[i], FALSE);
	}

	if (subpath != nullptr) delete[] subpath;

	Gdiplus::RectF rect; Gpath.GetBounds(&rect);
	brush = GDI_Brush(fill, rect);
	pen = GDI_Pen(stroke, stroke_width, rect);
	if (dynamic_cast<LinearGradient*>(fill) || dynamic_cast<RadialGradient*>(fill)) {
		vector<Stop> colorOffset = dynamic_cast<Gradient*>(fill)->getColorOffset();
		RGB_Color* color = new RGB_Color(colorOffset[colorOffset.size() - 1].getColor());
		solidBrush = GDI_Brush(color, rect);
	}
}

// Virtual method
void Drawable_Path::draw(Render_Window) {
	Transform_First(transforms, graphics);
	if (fill->opacity) {
		if (solidBrush) graphics.FillPath(solidBrush, &Gpath);
		graphics.FillPath(brush, &Gpath);
	}
	if (stroke->opacity) graphics.DrawPath(pen, &Gpath);
	Transform_Second(transforms, graphics);
}
//-----------END-OF-IMPLEMENTATION-----------//