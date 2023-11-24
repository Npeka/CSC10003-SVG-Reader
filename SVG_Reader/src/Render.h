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
		virtual void set_SF_Shape() = 0;
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
		void set_SF_Shape();
		void draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform);
	};
	//-------------end-of-declaration------------//

	// class SF_Ellipse
	class SF_ShapeFactory {
	public:
		SF_Shape* get_SF_Shape(Figure* figure);
	};
	//-------------end-of-declaration------------//

	// class SF_Ellipse
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

