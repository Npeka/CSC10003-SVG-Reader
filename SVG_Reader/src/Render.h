#ifndef RENDER_H
#define RENDER_H

#include "Header.h"
#include "SVGImage.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Line.h"
#include "Polyline.h"
#include "Polygon.h"
#include "Path.h"
#include "Text.h"

// Template class for convert from Figure to other library's Figure
template <class _Figure, class _Rectangle, class _Ellipse, class _Circle, class _Line, class _Polyline, class _Polygon, class _Text, class _Path>
_Figure* getLibFigure(Figure* figure);

template <class _Figure, class _Rectangle, class _Ellipse, class _Circle, class _Line, class _Polyline, class _Polygon, class _Text, class _Path>
void Convert(const SVGImage& svgImage, vector <_Figure*>& shapes);
//-------------END-OF-DECLARATION------------//
/*



*/ 
// SFML RENDERER
// SFML library
#include <SFML/Graphics.hpp>

// namespace functions declaration
namespace sfml {
	// SFML Define shorter code
	#define sf_Render(window, transform) sf::RenderWindow& window, sf::Transform& transform
	#define sf_Transform(code1, code2) \
		SF_Transform_First(this->transform, window, transform); \
		code1; \
		code2; \
		SF_Transform_Second(this->transform, window, transform); \
	/*



	*/
	// SF_Shape
	class SF_Shape {
	public:
		virtual void draw_SF_Shape(sf_Render(window, transform)) = 0;
		virtual ~SF_Shape() = default;
	};
	//-------------END-OF-DECLARATION------------//
	/*



	*/
	// SF_Rectangle
	class SF_Rectangle : public SF_Shape, public Rectangle {
	private:
		sf::RectangleShape rectangle;
		sf::RectangleShape outline;
	public:
		// Constructor
		SF_Rectangle(const Rectangle* rect);

		// Virtual method
		void draw_SF_Shape(sf_Render(window, transform)) override;
		~SF_Rectangle() override = default;
	};
	//-------------END-OF-DECLARATION------------//
	/*



	*/
	// SF_Ellipse
	class SF_Ellipse : public SF_Shape, public Ellipse {
	private:
		sf::ConvexShape ellipse;
		sf::ConvexShape outline;
	public:
		// Constructor
		SF_Ellipse(const Ellipse* rect);

		// Virtual method
		void draw_SF_Shape(sf_Render(window, transform)) override;
		~SF_Ellipse() override = default;
	};
	//-------------END-OF-DECLARATION------------//
	/*



	*/
	// class SF_Circle
	class SF_Circle : public SF_Shape, public Circle {
	private:
		sf::CircleShape circle;
		sf::CircleShape outline;
	public:
		// Constructor
		SF_Circle(const Circle* circle);

		// Virtual method
		void draw_SF_Shape(sf_Render(window, transform)) override;
		~SF_Circle() override = default;
	};
	//-------------END-OF-DECLARATION------------//
	/*



	*/
	// class SF_Line
	class SF_Line : public SF_Shape, public Line {
	private:
		sf::RectangleShape line;
	public:
    // Constructor 
		SF_Line();
		SF_Line(const Line* line);
		void setLine(Color stroke);
    
		// Virtual method
		void draw_SF_Shape(sf_Render(window, transform)) override;
		~SF_Line() override = default;
	};
	//-------------END-OF-DECLARATION------------//
	/*



	*/
	// class SF_Polyline
	class SF_Polyline : public SF_Shape, public Polyline {
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
		SF_Polyline(const Polyline* polyline);

		// Virtual method
		void draw_SF_Shape(sf_Render(window, transform)) override;
		~SF_Polyline() override = default;
	};
	//-------------END-OF-DECLARATION------------//
	/*


	*/
	// class SF_Polygon
	class SF_Polygon : public SF_Shape, public Polygon {
	private:
		sf::ConvexShape polygon;
		sf::ConvexShape outline;
	public:
		// Constructor
		SF_Polygon(const Polygon* polygon);

		// Virtual method
		void draw_SF_Shape(sf_Render(window, transform)) override;
		~SF_Polygon() override = default;
	};
	//-------------END-OF-DECLARATION------------//
	/*



	*/
	// class SF_Text
	class SF_Text : public SF_Shape, public Text {
	private:
		sf::Font font;
		sf::Text text;
	public:
		// Constructor
		SF_Text(const Text* text);

		// Virtual method
		void draw_SF_Shape(sf_Render(window, transform)) override;
		~SF_Text() override = default;
	};
	//-------------END-OF-DECLARATION------------//
	/*



	*/
	// class SF_Path
	class SF_Path : public SF_Shape, public Path {
	private:
		Color getStroke();
		void drawPath(sf::RenderWindow& window, sf::Transform& transform);
	public:
		// Constructor
		SF_Path(const Path* path);

		// Virtual method
		void draw_SF_Shape(sf_Render(window, transform)) override;
		~SF_Path() override = default;
	};
	//-------------END-OF-DECLARATION------------//
	/*



	*/
	// class SF_SVGImage
	class SF_SVGImage : public SVGImage {
	private:
		vector <SF_Shape*> shapes;
	public:
		// Constructor
		SF_SVGImage();
		SF_SVGImage(const SVGImage& svgImage);

		// Destructor
		~SF_SVGImage();

		// Methods
		void draw_SF_SVGImage(sf_Render(window, transform));
		void render();
	};
	//-------------END-OF-DECLARATION------------//
	/*



	*/
	// Functions namespace
	void SF_Transform_First(const vector< pair<int, Point> >& t, sf_Render(window, transform));
	void SF_Transform_Second(const vector< pair<int, Point> >& t, sf_Render(window, transform));
	sf::Color set_SF_Color(const Color& color);
	void render(const SVGImage& svgImage);
	//-------------END-OF-DECLARATION------------//
}

#endif // !RENDER_H