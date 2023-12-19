#ifndef RENDER_H
#define RENDER_H

#include "Drawable.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Line.h"
#include "Polyline.h"
#include "Polygon.h"
#include "Path.h"
#include "Text.h"

// DrawableRectangle
class Drawable_Rectangle : public Drawable, public Rectangle {
private:
	Gdiplus::RectF rect;

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
	Gdiplus::RectF ellipseRect;
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
	Gdiplus::RectF circleRect;
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
	Gdiplus::PointF* gdiPoints;

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
	Gdiplus::GraphicsPath TextPath;

public:
	// Constructor
	Drawable_Text() = default;

	// Virtual method
    void setDrawableAtrributes();
	void draw(Render_Window) override;
	~Drawable_Text() override = default;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// class SF_Path
class Drawable_Path : public Drawable, public Path {
private:
	Gdiplus::GraphicsPath Gpath;
	int countSubpath;

public:
	// Constructor
	Drawable_Path() = default;

	// Virtual method
	void setDrawableAtrributes();
	void draw(Render_Window) override;
	~Drawable_Path() override = default;
};
//-------------END-OF-DECLARATION------------//

#endif // _RENDER_H