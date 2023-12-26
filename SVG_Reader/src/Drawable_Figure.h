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

/**
 * @brief Represents a drawable rectangle.
 */
class Drawable_Rectangle : public Drawable, public Rectangle {
private:
	Gdiplus::RectF rect; /**< GDI+ rectangle representation. */

public:
	/**< Default constructor. */
	Drawable_Rectangle() = default; 
	/**< Virtual destructor. */
	~Drawable_Rectangle() override = default;
	/**< Set drawable attributes. */
	void setDrawableAtrributes() override;
	/**< Draw the rectangle. */
	void draw(Render_Window) override;
	
};



/**
 * @brief Represents a drawable ellipse.
 */
class Drawable_Ellipse : public Drawable, public Ellipse {
private:
	Gdiplus::RectF ellipseRect; /**< GDI+ ellipse representation. */

public:
	/**< Default constructor. */
	Drawable_Ellipse() = default; 
	/**< Virtual destructor. */
	~Drawable_Ellipse() override = default;
	/**< Set drawable attributes. */
	void setDrawableAtrributes() override;
	/**< Draw the ellipse. */
	void draw(Render_Window) override;  
};



/**
 * @brief Represents a drawable circle.
 */
class Drawable_Circle : public Drawable, public Circle {
private:
	Gdiplus::RectF circleRect; /**< GDI+ circle representation. */

public:
	/**< Default constructor. */
	Drawable_Circle() = default;
	/**< Virtual destructor. */
	~Drawable_Circle() override = default;
	/**< Set drawable attributes. */
	void setDrawableAtrributes() override;
	/**< Draw the circle. */
	void draw(Render_Window) override; 
};



/**
 * @brief Represents a drawable line.
 */
class Drawable_Line : public Drawable, public Line {
public:
	/**< Default constructor. */
	Drawable_Line() = default;	 
	/**< Virtual destructor. */
	~Drawable_Line() override = default;
	/**< Set drawable attributes. */
	void setDrawableAtrributes() override;  
	/**< Draw the line. */
	void draw(Render_Window) override;
};



/**
 * @brief Represents a drawable polyline.
 */
class Drawable_Polyline : public Drawable, public Polyline {
private:
	Gdiplus::PointF* gdiPoints; /**< GDI+ points representation. */

public:
	/**< Default constructor. */
	Drawable_Polyline(); 
	/**< Virtual destructor. */
	~Drawable_Polyline() override;
	/**< Set drawable attributes. */
	void setDrawableAtrributes() override; 
	/**< Draw the polyline. */
	void draw(Render_Window) override; 
};



/**
 * @brief Represents a drawable polygon.
 */
class Drawable_Polygon : public Drawable, public Polygon {
private:
	Gdiplus::PointF* gdiPoints; /**< GDI+ points representation. */

public:
	/**< Default constructor. */
	Drawable_Polygon(); 
	/**< Virtual destructor. */
	~Drawable_Polygon() override; 
	/**< Set drawable attributes. */
	void setDrawableAtrributes() override;  
	/**< Draw the polygon. */
	void draw(Render_Window) override;
};



/**
 * @brief Represents a drawable text element.
 */
class Drawable_Text : public Drawable, public Text {
private:
	Gdiplus::GraphicsPath TextPath; /**< GDI+ text path representation. */

public:
	/**< Default constructor. */
	Drawable_Text() = default;
	/**< Virtual destructor. */
	~Drawable_Text() override = default;
	/**< Set drawable attributes. */
	void setDrawableAtrributes() override;
	/**< Draw the text. */
	void draw(Render_Window) override; 
};



/**
 * @brief Represents a drawable path element.
 */
class Drawable_Path : public Drawable, public Path {
private:
	Gdiplus::GraphicsPath Gpath; /**< GDI+ graphics path representation. */
	int countSubpath; /**< Count of subpaths. */

public:
	/**< Default constructor. */
	Drawable_Path() = default; 
	/**< Virtual destructor. */
	~Drawable_Path() override = default; 
	/**< Set drawable attributes. */
	void setDrawableAtrributes() override; 
	/**< Draw the path. */
	void draw(Render_Window) override; 
};

#endif // _RENDER_H