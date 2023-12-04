#ifndef RENDER_H
#define RENDER_H

#include "Header.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Line.h"
#include "Polyline.h"
#include "Polygon.h"
#include "Path.h"
#include "Text.h"

// Include lib for render
#include <windows.h>
#include <gdiplus.h>

// Define parameters needed for render lib
#define Render_Window Gdiplus::Graphics& graphics

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
	Drawable() : pen(Gdiplus::Color(0, 0, 0)), brush(Gdiplus::Color(0, 0, 0)) {}
	virtual void setAtrribute() = 0;
	virtual void draw(Render_Window) = 0;
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
	void setAtrribute();
	void draw(Render_Window) override;
	~Drawable_Rectangle() override = default;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// DrawableEllipse
class Drawable_Ellipse : public Drawable, public Ellipse {
private:
	
public:
	// Constructor
	Drawable_Ellipse() = default;

	// Virtual method
	void setAtrribute();
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
	void setAtrribute();
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
	Drawable_Line(const Line* line);

	// Virtual method
	void setAtrribute();
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
	Drawable_Polyline() = default;

	// Virtual method
	void setAtrribute();
	void draw(Render_Window) override;
	~Drawable_Polyline() override = default;
};
//-------------END-OF-DECLARATION------------//
/*


*/
// class DrawablePolygon
class Drawable_Polygon : public Drawable, public Polygon {
private:
	
public:
	// Constructor
	Drawable_Polygon() = default;

	// Virtual method
	void setAtrribute();
	void draw(Render_Window) override;
	~Drawable_Polygon() override = default;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// class DrawableText
class Drawable_Text : public Drawable, public Text {
private:
	
public:
	// Constructor
	Drawable_Text() = default;

	// Virtual method
    void setAtrribute();
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
	Gdiplus::Region region; 
public:
	// Constructor
	Drawable_Path() = default;

	//
	Color getStroke();

	// Virtual method
	void setAtrribute();
	void draw(Render_Window) override;
	~Drawable_Path() override = default;
};
//-------------END-OF-DECLARATION------------//

#endif // !RENDER_H