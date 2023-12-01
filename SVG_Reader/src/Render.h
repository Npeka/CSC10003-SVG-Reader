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

// SFML RENDERER
// SFML library
#include <SFML/Graphics.hpp>

// SFML Define shorter code
#define sf_Render(window, transform) sf::RenderWindow& window, sf::Transform& transform
#define sf_Transform(code1, code2) \
	SF_Transform_First(this->transform, window, transform); \
	code1; \
	code2; \
	SF_Transform_Second(this->transform, window, transform); \
/*



*/
// Drawable
class Drawable {
public:
	virtual void setAtrribute() = 0;
	virtual void draw(sf_Render(window, transform)) = 0;
	virtual ~Drawable() = default;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// DrawableRectangle
class DrawableRectangle : public Drawable, public Rectangle {
private:
	sf::RectangleShape rectangle;
	sf::RectangleShape outline;
public:
	// Constructor
	DrawableRectangle() = default;

	// Virtual method
	void setAtrribute();
	void draw(sf_Render(window, transform)) override;
	~DrawableRectangle() override = default;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// DrawableEllipse
class DrawableEllipse : public Drawable, public Ellipse {
private:
	sf::ConvexShape ellipse;
	sf::ConvexShape outline;
public:
	// Constructor
	DrawableEllipse() = default;

	// Virtual method
	void setAtrribute();
	void draw(sf_Render(window, transform)) override;
	~DrawableEllipse() override = default;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// class DrawableCircle
class DrawableCircle : public Drawable, public Circle {
private:
	sf::CircleShape circle;
	sf::CircleShape outline;
public:
	// Constructor
	DrawableCircle() = default;

	// Virtual method
	void setAtrribute();
	void draw(sf_Render(window, transform)) override;
	~DrawableCircle() override = default;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// class DrawableLine
class DrawableLine : public Drawable, public Line {
private:
	sf::RectangleShape line;
public:
	// Constructor 
	DrawableLine() = default;
	DrawableLine(const Line* line);
	void setLine(Color stroke);

	// Virtual method
	void setAtrribute();
	void draw(sf_Render(window, transform)) override;
	~DrawableLine() override = default;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// class DrawablePolyline
class DrawablePolyline : public Drawable, public Polyline {
private:
	// Attributes
	sf::RectangleShape* lines;
	sf::ConvexShape* joint;


	// Methods
	sf::RectangleShape Line(FPoint start, FPoint end);
	void drawPolyline(sf_Render(window, transform));
	void drawPolyline2(sf_Render(window, transform));
public:
	// Constructor
	DrawablePolyline() = default;

	// Virtual method
	void setAtrribute();
	void draw(sf_Render(window, transform)) override;
	~DrawablePolyline() override = default;
};
//-------------END-OF-DECLARATION------------//
/*


*/
// class DrawablePolygon
class DrawablePolygon : public Drawable, public Polygon {
private:
	sf::ConvexShape polygon;
	sf::ConvexShape outline;
public:
	// Constructor
	DrawablePolygon() = default;

	// Virtual method
	void setAtrribute();
	void draw(sf_Render(window, transform)) override;
	~DrawablePolygon() override = default;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// class DrawableText
class DrawableText : public Drawable, public Text {
private:
	sf::Font font;
	sf::Text text;
public:
	// Constructor
	DrawableText() = default;

	// Virtual method
    void setAtrribute();
	void draw(sf_Render(window, transform)) override;
	~DrawableText() override = default;
};
//-------------END-OF-DECLARATION------------//
/*



*/
// class SF_Path
class DrawablePath : public Drawable, public Path {
private:
	Color getStroke();
	void drawPath(sf::RenderWindow& window, sf::Transform& transform);
public:
	// Constructor
	DrawablePath() = default;

	// Virtual method
	void setAtrribute();
	void draw(sf_Render(window, transform)) override;
	~DrawablePath() override = default;
};

void SF_Transform_First(const vector< pair<int, Point> >& t, sf_Render(window, transform));
void SF_Transform_Second(const vector< pair<int, Point> >& t, sf_Render(window, transform));
sf::Color set_SF_Color(const Color& color);
//-------------END-OF-DECLARATION------------//

#endif // !RENDER_H