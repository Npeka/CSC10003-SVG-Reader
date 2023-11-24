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
#ifdef DEBUG
#include "SVGImage.cpp"
#endif // DEBUG

#define CONVERT(T, figure) static_cast<T>(figure)
#define ISVALID(T, figure) dynamic_cast<T>(figure)

namespace sfml {
	// class SF_Shape
	class SF_Shape {
	public:
		virtual void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform) = 0;
	};
	//-------------end-of-declaration------------//

	// class SF_Rectangle
	class SF_Rectangle : public SF_Shape, public Rectangle {
	private:
		sf::RectangleShape rectangle;
		sf::RectangleShape outline;
	public:
		SF_Rectangle(const Rectangle* rect);
		void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform);
	};
	//-------------end-of-declaration------------//
	
	// class SF_Ellipse
	class SF_Ellipse : public SF_Shape, public Ellipse {
	private:
		sf::ConvexShape ellipse;
		sf::ConvexShape outline;
	public:
		SF_Ellipse(const Ellipse* rect);
		void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform);
	};
	//-------------end-of-declaration------------//

	// class SF_Circle
	class SF_Circle : public SF_Shape, public Circle {
	private:
		sf::CircleShape circle;
		sf::CircleShape outline;
	public:
		SF_Circle(const Circle* circle);
		void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform);
	};
	//-------------end-of-declaration------------//

	// class SF_Line
	class SF_Line : public SF_Shape, public Line {
	private:
		sf::RectangleShape line;
	public:
		SF_Line(const Line* line);
		void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform);
	};
	//-------------end-of-declaration------------//

	// class SF_Polyline
	class SF_Polyline : public SF_Shape, public Polyline {
	private:
		sf::RectangleShape* lines;
		sf::ConvexShape* joint;
	public:
		SF_Polyline(const Polyline* polyline);
		void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform);
	};
	//-------------end-of-declaration------------//

	// class SF_Polygon
	class SF_Polygon : public SF_Shape, public Polygon {
	private:
		sf::ConvexShape polygon;
		sf::ConvexShape outline;
	public:
		SF_Polygon(const Polygon* polygon);
		void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform);
	};
	//-------------end-of-declaration------------//

	// class SF_Text
	class SF_Text : public SF_Shape, public Text {
	private:
		sf::Font font;
		sf::Text text;
	public:
		SF_Text(const Text* text);
		void draw_SF_Shape(sf::RenderWindow & window, sf::Transform & transform);
	};
	//-------------end-of-declaration------------//

	// class SF_ShapeFactory
	class SF_ShapeFactory {
	public:
		SF_Shape* get_SF_Shape(Figure* figure);
	};
	//-------------end-of-declaration------------//

	// class SF_SVGImage
	class SF_SVGImage : public SVGImage {
	private:
		vector <SF_Shape*> shapes;
	public:
		SF_SVGImage();
		SF_SVGImage(const SVGImage& svgImage);
		void draw_SF_SVGImage(sf::RenderWindow& window, sf::Transform& transform);
	};
	//-------------end-of-declaration------------//

	// Function namespace 
	sf::Color set_SF_Color(const Color& color);
	void render(const SVGImage& svgImage);
	//-------------end-of-declaration------------//
}

#endif // !RENDER_H

