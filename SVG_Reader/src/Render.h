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

#define CONVERT(T, figure) static_cast<T>(figure)
#define ISVALID(T, figure) dynamic_cast<T>(figure)



/*
	Template class for convert from Figure to other library's Figure
*/
template <class _Figure, class _Rectangle, class _Ellipse, class _Circle, class _Line, class _Polyline, class _Polygon, class _Text, class _Path>
_Figure* getLibFigure(Figure* figure);

template <class _Figure, class _Rectangle, class _Ellipse, class _Circle, class _Line, class _Polyline, class _Polygon, class _Text, class _Path>
void Convert(const SVGImage& svgImage, vector <_Figure*>& shapes);
/*
						end of declaration
*/

// Library SFML
#include <SFML/Graphics.hpp>

// SFML RENDER
namespace sfml {
	//------------------SF_Shape-----------------//
	class SF_Shape {
	public:
		virtual void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform) = 0;
	};
	//-------------END-OF-DECLARATION------------//
	/*


	*/
	//----------------SF_Rectangle---------------//
	class SF_Rectangle : public SF_Shape, public Rectangle {
	private:
		sf::RectangleShape rectangle;
		sf::RectangleShape outline;
	public:
		SF_Rectangle(const Rectangle* rect);
		void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform);

	};
	//-------------END-OF-DECLARATION------------//
	/*


	*/
	//-----------------SF_Ellipse----------------//
	class SF_Ellipse : public SF_Shape, public Ellipse {
	private:
		sf::ConvexShape ellipse;
		sf::ConvexShape outline;
	public:
		SF_Ellipse(const Ellipse* rect);
		void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform);
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
		SF_Circle(const Circle* circle);
		void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform);
	};
    //-------------END-OF-DECLARATION------------//
	/*


	*/
	// class SF_Line
	class SF_Line : public SF_Shape, public Line {
	private:
		sf::RectangleShape line;
	public:
		SF_Line(const Line* line);
		void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform);
	};
    //-------------END-OF-DECLARATION------------//
	/*


	*/
	// class SF_Polyline
	class SF_Polyline : public SF_Shape, public Polyline {
	private:
		sf::RectangleShape* lines;
		sf::ConvexShape* joint;
		sf::RectangleShape Line(FPoint start, FPoint end);
		void drawPolyline(sf::RenderWindow& window, sf::Transform transform);
		void drawPolyline2(sf::RenderWindow& window, sf::Transform transform);
	public:
		SF_Polyline(const Polyline* polyline);
		void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform);
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
		SF_Polygon(const Polygon* polygon);
		void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform);
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
		SF_Text(const Text* text);
		void draw_SF_Shape(sf::RenderWindow & window, sf::Transform & transform);
	};
    //-------------END-OF-DECLARATION------------//
	/*


	*/
	// class SF_Path
	class SF_Path : public SF_Shape, public Path {
	private:
		sf::RectangleShape Line(Point start, Point end);
		void drawPath(sf::RenderWindow& window, sf::Transform& transform);
	public:
		SF_Path(const Path* path);
		void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform);
	};
	//-------------END-OF-DECLARATION------------//
	/*


	*/
	// class SF_SVGImage
	class SF_SVGImage : public SVGImage {
	private:
		vector <SF_Shape*> shapes;
	public:
		SF_SVGImage();
		SF_SVGImage(const SVGImage& svgImage);
		void draw_SF_SVGImage(sf::RenderWindow& window, sf::Transform& transform);
	};
    //-------------END-OF-DECLARATION------------//
	/*


	*/
	//-------------FUNCTIONS-NAMESPACE-----------//
	template <class sf_shape>
	void set_SF_ShapeTransform(sf_shape& shape, const vector< pair<int, Point> >& transform);
	sf::Color set_SF_Color(const Color& color);
	void render(const SVGImage& svgImage);
    //-------------END-OF-DECLARATION------------//
}

#endif // !RENDER_H