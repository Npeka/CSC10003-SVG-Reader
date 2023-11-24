#include "Render.h"

namespace sfml {
	// class SF_Rectangle
	SF_Rectangle::SF_Rectangle(const Rectangle* rect) : Rectangle(*rect) {}

	void SF_Rectangle::set_SF_Shape() {
		rectangle.setSize(sf::Vector2f(width, height));
		rectangle.setPosition(x, y);
		rectangle.setFillColor(set_SF_Color(fill));
		rectangle.setOutlineThickness(stroke_width / 2);
		rectangle.setOutlineColor(set_SF_Color(stroke));

		outline = rectangle;
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineThickness(-stroke_width / 2);
	}

	void SF_Rectangle::draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform) {
		window.draw(rectangle, transform);
		window.draw(outline, transform);
	}
	//-----------end-of-implementation-----------//

	// class SF_Circle
	SF_Circle::SF_Circle(const Circle* circle) : Circle(*circle) {}

	void SF_Circle::set_SF_Shape() {
		circle.setRadius(r);
		circle.setPosition(cx - r, cy - r);								// cx cy
		circle.setFillColor(fill.sfColor());							// fill
		circle.setOutlineThickness(stroke_width / 2);					// stroke-width
		circle.setOutlineColor(stroke.sfColor());
		circle.setPointCount(2000);

		outline = circle;
		outline.setFillColor(sf::Color(0, 0, 0, 0));
		outline.setOutlineThickness(-stroke_width / 2);
	}

	void SF_Circle::draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform) {
		window.draw(circle, transform);
		window.draw(outline, transform);
	}
	//-----------end-of-implementation-----------//

	// class SF_Line
	SF_Line::SF_Line(const Line* line) : Line(*line) {}

	void SF_Line::set_SF_Shape() {
		Point start(p1);
		Point end(p2);
		if (end.x < start.x) swap(start, end);

		float length = sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
		line.setSize(sf::Vector2f(length, stroke_width));

		float angle = atan((end.y - start.y) / (end.x - start.x));
		angle = angle * 180 / M_PI;
		start.x += (stroke_width / 2) * cos(M_PI_2 - angle);
		start.y -= (stroke_width / 2) * sin(M_PI_2 - angle);

		line.rotate(angle);
		line.setPosition(start.x, start.y);
		line.setFillColor(stroke.sfColor());
	}

	void SF_Line::draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform) {
		window.draw(line, transform);
	}
	//-----------end-of-implementation-----------//

	// class SF_Polyline
	SF_Polyline::SF_Polyline(const Polyline* polyline) : Polyline(*polyline) {}

	sf::RectangleShape SF_Polyline::Line(FPoint start, FPoint end) {
		if (end.x < start.x) swap(start, end);

		float length = sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
		sf::RectangleShape line(sf::Vector2f(length, stroke_width));

		float angle = atan((end.y - start.y) / (end.x - start.x));
		angle = angle * 180 / M_PI;

		line.rotate(angle);
		line.setOutlineThickness(0);
		line.setPosition(start.x - stroke_width / 2, start.y - stroke_width / 2);
		return line;
	}

	void SF_Polyline::drawPolyline(sf::RenderWindow& window, sf::Transform transform) {

		for (int i = 0; i < fpoint.size() - 1; i++) {
			window.draw(lines[i], transform);

			if (i > 0 && i < fpoint.size() - 1) {
				joint[i - 1].setFillColor(sf::Color(stroke.sfColor()));
				window.draw(joint[i - 1], transform); //draw joint
			}
		}
	}

	void SF_Polyline::drawPolyline2(sf::RenderWindow& window, sf::Transform transform) {
		vector <FPoint> temp = fpoint;
		updateListPoint(temp);
		int start, end;
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i].fill == true) {
				start = i;
				for (int j = i + 1; j < temp.size(); j++) {
					if (temp[j].fill == true) {
						end = j;
						break;
					}
					else if (temp[j].fill == false && j == temp.size() - 1) {
						drawPolyline(window, transform);
						return;
					}
				}

				sf::ConvexShape fillArea;
				for (int k = 0; k < end - start + 1; k++) {
					fillArea.setPointCount(end - start + 1);
					fillArea.setPoint(k, sf::Vector2f(temp[start + k].x, temp[start + k].y));
				}

				fillArea.setOutlineThickness(0);
				fillArea.setPosition(-stroke_width / 2, -stroke_width / 2);
				fillArea.setFillColor(fill.sfColor());
				window.draw(fillArea, transform);
				i = end - 1;
			}
		}
		drawPolyline(window, transform);
	}


	void SF_Polyline::set_SF_Shape() {
		lines = new sf::RectangleShape[fpoint.size()];
		joint = new sf::ConvexShape[fpoint.size() - 2];

		for (int i = 0; i < fpoint.size() - 1; i++) {
			lines[i] = Line(fpoint[i], fpoint[i + 1]);
			lines[i].setFillColor(stroke.sfColor());

			if (i > 0 && i < fpoint.size() - 1) {
				float angle1 = getAngle(fpoint[i - 1], fpoint[i]) * M_PI / 180;
				float angle2 = getAngle(fpoint[i], fpoint[i + 1]) * M_PI / 180;

				float p3_x = fpoint[i].x - stroke_width * cos(M_PI_2 - (angle1 + angle2) / 2) / cos((angle1 - angle2) / 2);
				float p3_y = fpoint[i].y + stroke_width * sin(M_PI_2 - (angle1 + angle2) / 2) / cos((angle1 - angle2) / 2);

				joint[i - 1].setPointCount(4);

				joint[i - 1].setPoint(0, sf::Vector2f(fpoint[i].x, fpoint[i].y));
				joint[i - 1].setPoint(1, sf::Vector2f(fpoint[i].x - stroke_width * sin(angle1), fpoint[i].y + stroke_width * cos(angle1)));
				joint[i - 1].setPoint(2, sf::Vector2f(p3_x, p3_y));
				joint[i - 1].setPoint(3, sf::Vector2f(fpoint[i].x - stroke_width * sin(angle2), fpoint[i].y + stroke_width * cos(angle2)));

				joint[i - 1].setPosition(-stroke_width / 2, -stroke_width / 2);
			}
		}
	}

	void SF_Polyline::draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform) {
		drawPolyline2(window, transform);
	}
	//-----------end-of-implementation-----------//

	// class SF_ShapeFactory
	SF_Shape* SF_ShapeFactory::get_SF_Shape(Figure* figure) {
		if (ISVALID(Rectangle*, figure)) return new SF_Rectangle(CONVERT(Rectangle*, figure));
		return NULL;
	}
	//-----------end-of-implementation-----------//

	// class SF_SVGImage
	SF_SVGImage::SF_SVGImage() : SVGImage() {

	}

	SF_SVGImage::SF_SVGImage(const SVGImage& svgImage) : SVGImage(svgImage) {
		for (int i = 0; i < svgImage.getFigure().size(); i++) {
			SF_Shape* new_SF_Shape = SF_ShapeFactory().get_SF_Shape(svgImage.getFigure()[i]);
			if (new_SF_Shape == NULL) continue;
			new_SF_Shape->set_SF_Shape();
			shapes.push_back(new_SF_Shape);
		}
	}

	void SF_SVGImage::draw_SF_SVGImage(sf::RenderWindow& window, sf::Transform& transform) {
		for (auto shape : shapes) {
			shape->draw_SF_Shape(window, transform);
		}
	}
	//-----------end-of-implementation-----------//

	// Function namespace 
	sf::Color set_SF_Color(const Color& color) {
		return sf::Color(color.r, color.g, color.b, color.a);
	}

	void render(const SVGImage& svgImage) {
		sf::RenderWindow window(sf::VideoMode(1024, 720), "SFML Drawing", sf::Style::Default, sf::ContextSettings(0, 0, 8));
		sf::Vector2f screenPosition(400, 300);

		SF_SVGImage sf_svgImage(svgImage);

		float zoom = 1;
		float angle = 0;
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Add)
						zoom *= 1.2;
					else if (event.key.code == sf::Keyboard::Subtract)
						zoom *= 0.8;
					else if (event.key.code == sf::Keyboard::Q)
						angle -= 5;
					else if (event.key.code == sf::Keyboard::E)
						angle += 5;
				}

				// Di chuyển màn hình
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					screenPosition.y -= 10;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					screenPosition.x -= 10;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					screenPosition.y += 10;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					screenPosition.x += 10;
			}

			// Xóa cửa sổ để vẽ lại
			window.clear(sf::Color::White);

			// Tính toán tỉ lệ to nhỏ của hình ảnh
			sf::Transform transform;
			transform.scale(zoom, zoom);
			transform.rotate(angle, 400, 300);
			// vẽ hình
			sf_svgImage.draw_SF_SVGImage(window, transform);

			// Di chuyển màn hình
			window.setView(sf::View(screenPosition, sf::Vector2f(window.getSize().x, window.getSize().y)));
			window.display();
		}
	}
	//-----------end-of-implementation-----------//
}