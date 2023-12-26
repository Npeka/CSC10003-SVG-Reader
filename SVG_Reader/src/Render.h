#ifndef RENDER_H
#define RENDER_H

//#include "SVGImage.h"
#include "Header.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Line.h"
#include "Polyline.h"
#include "Polygon.h"
#include "Path.h"
#include "Text.h"


const float TAU = M_PI * 2; 
struct BezierCurve {
	Point p1, p2, p3, p4;
};

// Include lib for render
#include <windows.h>
#include <gdiplus.h>

// Define parameters needed for render lib
#define Render_Window Gdiplus::Graphics& graphics
#define Render_Parameters graphics

// Function to convert from Color to Graphics library Colors
Gdiplus::Color GDI_Color(const Color& color);
void Transform_First(const std::vector< std::pair<int, Point> >& t, Render_Window);
void Transform_Second(const std::vector< std::pair<int, Point> >& t, Render_Window);
/*



*/
// Drawable
class Drawable {
protected:
	Gdiplus::Pen pen;
	Gdiplus::SolidBrush brush;
public:
	Drawable();
	virtual void setDrawableAtrributes() {};
	virtual void draw(Render_Window) {};
	virtual ~Drawable() = default;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// DrawableRectangle
class Drawable_Rectangle : public Drawable, public Rectangle {
private:
	Gdiplus::Rect rect;
public:
	// Constructor
	Drawable_Rectangle() = default;

	// Virtual method
	void setDrawableAtrributes();
	void draw(Render_Window) override;
	~Drawable_Rectangle() override = default;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// DrawableEllipse
class Drawable_Ellipse : public Drawable, public Ellipse {
private:
	Gdiplus::Rect ellipseRect;
public:
	// Constructor
	Drawable_Ellipse() = default;

	// Virtual method
	void setDrawableAtrributes();
	void draw(Render_Window) override;
	~Drawable_Ellipse() override = default;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// class DrawableCircle
class Drawable_Circle : public Drawable, public Circle {
private:
	
public:
	// Constructor
	Drawable_Circle() = default;

	// Virtual method
	void setDrawableAtrributes();
	void draw(Render_Window) override;
	~Drawable_Circle() override = default;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// class DrawableLine
class Drawable_Line : public Drawable, public Line {
private:
	
public:
	// Constructor 
	Drawable_Line() = default;

	// Virtual method
	void setDrawableAtrributes();
	void draw(Render_Window) override;
	~Drawable_Line() override = default;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// class DrawablePolyline
class Drawable_Polyline : public Drawable, public Polyline {
private:
	Gdiplus::PointF* points;

public:
	// Constructor
	Drawable_Polyline();

	// Virtual method
	void setDrawableAtrributes();
	void draw(Render_Window) override;
	~Drawable_Polyline() override;
};
//-------------END-OF-DECLARATION------------//
/*


*/
// class DrawablePolygon
class Drawable_Polygon : public Drawable, public Polygon {
private:
	Gdiplus::PointF* gdiPoints;
public:
	// Constructor
	Drawable_Polygon();

	// Virtual method
	void setDrawableAtrributes();
	void draw(Render_Window) override;
	~Drawable_Polygon() override;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// class DrawableText
class Drawable_Text : public Drawable, public Text {
private:
	Gdiplus::Font* font;
public:
	// Constructor
	Drawable_Text();

	// Virtual method
    void setDrawableAtrributes();
	void draw(Render_Window) override;
	~Drawable_Text() override;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// class SF_Path
class Drawable_Path : public Drawable, public Path {
private:
	Gdiplus::GraphicsPath* subpath;
	Gdiplus::GraphicsPath Gpath;
	int countSubpath; 
public:
	// Constructor
	Drawable_Path() = default;

	// Virtual method
	void setDrawableAtrributes();
	void draw(Render_Window) override;
	~Drawable_Path() override = default;

	// addition method 
	float computeBinominal(int n, int k);
	std::vector<Point> BezierCurveVertices(std::vector<Point> Pos, float smooth);
	Point EllipticArcPoint(Point c, Point r, float xAngle, float t);
	Point EllipticArcDerivative(Point c, Point r, float xAngle, float t);
	Point EllipticArcControlPoint(Point c, Point r, float xAngle, float t);
	Point EllipticArcControlPoint2(Point c, Point r, float xAngle, float t);
	Point mapToEllipse(const Point& point, float rx, float ry, float cosphi, float sinphi, float centerx, float centery);
	std::vector<Point> approxUnitArc(float ang1, float ang2);
	float vectorAngle(float ux, float uy, float vx, float vy);
	std::tuple<float, float, float, float> getArcCenter(
		float px, float py,
		float cx, float cy,
		float rx, float ry,
		int largeArcFlag, int sweepFlag,
		float sinphi, float cosphi,
		float pxp, float pyp
	);
	BezierCurve computeBezierCurve(const Point& startPoint, const Point& P1, const Point& P2, const Point& endPoint);
	std::vector<BezierCurve> arcToBezier(
		float px, float py,
		float cx, float cy,
		float rx, float ry,
		float xAxisRotation,
		int largeArcFlag,
		int sweepFlag
	);
	std::vector<BezierCurve> arcToBezier(float cx, float cy, float rx, float ry, float startAngle, float endAngle, float xAxisRotation);
	Point pointOnEllipse(float cx, float cy, float rx, float ry, float angle);
	Point ellipseCenter(float cx, float cy, float rx, float ry, float xAxisRotation);
};
//-------------END-OF-DECLARATION------------//

#endif // _RENDER_H