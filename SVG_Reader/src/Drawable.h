#ifndef DRAWABLE_H
#define DRAWABLE_H

// Include lib for render
#include <windows.h>
#include <gdiplus.h>

#include "Header.h"
#include "RGB_Color.h"
#include "LinearGradient.h"
#include "RadialGradient.h"

// Define parameters needed for render lib
#define Render_Window Gdiplus::Graphics& graphics
#define Render_Parameters graphics

// Function to convert from Color to Graphics library Colors
Gdiplus::Color GDI_RGB(const RGB_Color& color);
Gdiplus::Brush* GDI_LinearGradient(const LinearGradient& color, const Gdiplus::RectF& rect);
Gdiplus::Brush* GDI_RadialGradient(const RadialGradient& color, const Gdiplus::RectF& rect);
Gdiplus::Brush* GDI_Brush(Color* color, const Gdiplus::RectF& rect);
void Transform_First(const vector<pair<int, Point>>& t, Render_Window);
void Transform_Second(const vector<pair<int, Point>>& t, Render_Window);

// Drawable
class Drawable {
protected:
	Gdiplus::Brush* brush;
	Gdiplus::Pen* pen;

public:
	Drawable();
	virtual ~Drawable();
	virtual void setDrawableAtrributes() {};
	virtual void draw(Render_Window) {};
};

// Figure
class Drawable_Rectangle;
class Drawable_Ellipse;
class Drawable_Circle;
class Drawable_Line;
class Drawable_Polyline;
class Drawable_Polygon;
class Drawable_Text;
class Drawable_path;

#endif // !DRAWABLE_H
