#include "Render.h"

/*
	Template class for convert from Figure to other library's Figure
*/
template <class _Figure, class _Rectangle, class _Ellipse, class _Circle, class _Line, class _Polyline, class _Polygon, class _Text, class _Path>
_Figure* getLibFigure(Figure* figure) {
	if (ISVALID(Rectangle*, figure))	return new _Rectangle(CONVERT(Rectangle*, figure));
	if (ISVALID(Ellipse*, figure))		return new _Ellipse(CONVERT(Ellipse*, figure));
	if (ISVALID(Circle*, figure))		return new _Circle(CONVERT(Circle*, figure));
	if (ISVALID(Line*, figure))			return new _Line(CONVERT(Line*, figure));
	if (ISVALID(Polyline*, figure))		return new _Polyline(CONVERT(Polyline*, figure));
	if (ISVALID(Polygon*, figure))		return new _Polygon(CONVERT(Polygon*, figure));
	if (ISVALID(Text*, figure))			return new _Text(CONVERT(Text*, figure));
	if (ISVALID(Path*, figure))			return new _Path(CONVERT(Path*, figure));
	return NULL;
}

template <class _Figure, class _Rectangle, class _Ellipse, class _Circle, class _Line, class _Polyline, class _Polygon, class _Text, class _Path>
void Convert(const SVGImage& svgImage, vector <_Figure*>& shapes) {
	vector <Figure*> figure = svgImage.getFigure();
	for (int i = 0; i < figure.size(); i++) {
		_Figure* new_Figure = getLibFigure<_Figure, _Rectangle, _Ellipse, _Circle, _Line, _Polyline, _Polygon, _Text, _Path>(figure[i]);
		if (new_Figure == NULL) continue;
		shapes.push_back(new_Figure);
	}
}
/*
						end of implementation
*/

namespace sfml {
	// class SF_Rectangle
	SF_Rectangle::SF_Rectangle(const Rectangle* other) : Rectangle(*other) {
		rectangle.setSize(sf::Vector2f(width, height));
		rectangle.setPosition(x, y);
		rectangle.setFillColor(set_SF_Color(fill));
		rectangle.setOutlineColor(set_SF_Color(stroke));
		rectangle.setOutlineThickness(stroke_width / 2);

		set_SF_ShapeTransform<sf::RectangleShape>(rectangle, transform);

		outline = rectangle;
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineThickness(-stroke_width / 2);
	}

	void SF_Rectangle::draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform) {
		window.draw(rectangle, transform);
		window.draw(outline, transform);
	}
	//-----------end-of-implementation-----------//
	/*


	*/
	// class SF_Ellipse
	SF_Ellipse::SF_Ellipse(const Ellipse* other) : Ellipse(*other) {
		ellipse.setPosition(cx, cy);
		ellipse.setFillColor(set_SF_Color(fill));
		ellipse.setOutlineColor(set_SF_Color(stroke));
		ellipse.setOutlineThickness(stroke_width / 2);

		unsigned short quality = 180;
		ellipse.setPointCount(quality);

		for (unsigned short i = 0; i < quality; ++i) {
			float rad = (360 / quality * i) / (360 / M_PI / 2);
			float x = cos(rad) * rx;
			float y = sin(rad) * ry;
			ellipse.setPoint(i, sf::Vector2f(x, y));
		}

		set_SF_ShapeTransform<sf::ConvexShape>(ellipse, transform);

		outline = ellipse;
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineThickness(-stroke_width / 2);
	}

	void SF_Ellipse::draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform) {
		window.draw(ellipse, transform);
		window.draw(outline, transform);
	}
	//-----------end-of-implementation-----------//
	/*


	*/
	// class SF_Circle
	SF_Circle::SF_Circle(const Circle* other) : Circle(*other) {
		circle.setRadius(r);
		circle.setPosition(cx - r, cy - r);
		circle.setFillColor(set_SF_Color(fill));
		circle.setOutlineColor(set_SF_Color(stroke));
		circle.setOutlineThickness(stroke_width / 2);
		circle.setPointCount(2000);

		set_SF_ShapeTransform<sf::CircleShape>(circle, transform);

		outline = circle;
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineThickness(-stroke_width / 2);
	}

	void SF_Circle::draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform) {
		window.draw(circle, transform);
		window.draw(outline, transform);
	}
	//-----------end-of-implementation-----------//
	/*


	*/
	// class SF_Line
	SF_Line::SF_Line() {};

	SF_Line::SF_Line(const Line* other) : Line(*other) {
		Point start(p1);
		Point end(p2);
		if (end.x < start.x) swap(start, end);

		float length = sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
		line.setSize(sf::Vector2f(length, stroke_width / 2));

		float angle = atan((end.y - start.y) / (end.x - start.x));
		angle = angle * 180 / M_PI;

		line.rotate(angle);
		line.setPosition(start.x, start.y);
		line.setFillColor(set_SF_Color(stroke));

		set_SF_ShapeTransform<sf::RectangleShape>(line, transform);
	}

	void SF_Line::draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform) {
		window.draw(line, transform);
		float length = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
		line.setSize(sf::Vector2f(length, -stroke_width / 2));
		window.draw(line, transform);
		
	}
	//-----------end-of-implementation-----------//
	/*


	*/
	// class SF_Polyline
	SF_Polyline::SF_Polyline(const Polyline* polyline) : Polyline(*polyline) {
		lines = new sf::RectangleShape[fpoint.size()];
		joint = new sf::ConvexShape[fpoint.size() - 2];

		for (int i = 0; i < fpoint.size() - 1; i++) {
			lines[i] = Line(fpoint[i], fpoint[i + 1]);
			lines[i].setFillColor(set_SF_Color(stroke));

			if (i > 0 && i < fpoint.size() - 1) {
				double angle1 = getAngle(fpoint[i - 1], fpoint[i]) * M_PI / 180;
				double angle2 = getAngle(fpoint[i], fpoint[i + 1]) * M_PI / 180;

				FPoint A, B, C, D;
				A.x = fpoint[i].x - (stroke_width / 2) * sin(angle1);
				A.y = fpoint[i].y + (stroke_width / 2) * cos(angle1);

				B.x = fpoint[i - 1].x - (stroke_width / 2) * sin(angle1);
				B.y = fpoint[i - 1].y + (stroke_width / 2)* cos(angle1);

				C.x = fpoint[i].x - (stroke_width / 2) * sin(angle2);
				C.y = fpoint[i].y + (stroke_width / 2) * cos(angle2);

				D.x = fpoint[i + 1].x - (stroke_width / 2) * sin(angle2);
				D.y = fpoint[i + 1].y + (stroke_width / 2) * cos(angle2);

				FPoint p1, p2, p3, p4;
				p1 = IntersectionPoint(A, B, C, D);
				
				p3.x = 2 * fpoint[i].x - p1.x;
				p3.y = 2 * fpoint[i].y - p1.y;

				if (angle1 < M_PI) {
					if (angle2 < angle1 || angle2 > angle1 + M_PI) {
						swap(p1, p3);
						p2.x = p1.x - stroke_width * sin(angle1);
						p2.y = p1.y + stroke_width * cos(angle1);

						p4.x = p1.x - stroke_width * sin(angle2);
						p4.y = p1.y + stroke_width * cos(angle2);
					}
					else {
						p2.x = p1.x + stroke_width * sin(angle1);
						p2.y = p1.y - stroke_width * cos(angle1);

						p4.x = p1.x + stroke_width * sin(angle2);
						p4.y = p1.y - stroke_width * cos(angle2);
					}
				}
				else {
					if (angle1 - M_PI < angle2 && angle2 < angle1) {
						swap(p1, p3);
						p2.x = p1.x - stroke_width * sin(angle1);
						p2.y = p1.y + stroke_width * cos(angle1);

						p4.x = p1.x - stroke_width * sin(angle2);
						p4.y = p1.y + stroke_width * cos(angle2);
					}
					else {
						p2.x = p1.x + stroke_width * sin(angle1);
						p2.y = p1.y - stroke_width * cos(angle1);

						p4.x = p1.x + stroke_width * sin(angle2);
						p4.y = p1.y - stroke_width * cos(angle2);
					}
				}

				joint[i - 1].setPointCount(4);

				joint[i - 1].setPoint(0, sf::Vector2f(p1.x, p1.y));
				joint[i - 1].setPoint(1, sf::Vector2f(p2.x, p2.y));
				joint[i - 1].setPoint(2, sf::Vector2f(p3.x, p3.y));
				joint[i - 1].setPoint(3, sf::Vector2f(p4.x, p4.y));
			}
		}
	}

	sf::RectangleShape SF_Polyline::Line(FPoint start, FPoint end) {
		sf::RectangleShape line;
		float length = sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));

		float angle = getAngle(start, end);

		line.setSize(sf::Vector2f(length, stroke_width / 2));

		line.rotate(angle);
		line.setPosition(start.x, start.y);
		line.setFillColor(set_SF_Color(stroke));
		return line;
	}


	void SF_Polyline::drawPolyline(sf::RenderWindow& window, sf::Transform transform) {
		sf::RectangleShape line, next_line;
		next_line = lines[0];
		for (int i = 0; i < fpoint.size() - 1; i++) {
			line = next_line;
			if (i != fpoint.size() - 2)
			{
				next_line = lines[i + 1];

				float angle1 = getAngle(fpoint[i], fpoint[i + 1]);
				float angle2 = getAngle(fpoint[i + 1], fpoint[i + 2]);
				float angle = abs(angle1 + 180 - angle2); 
				
				angle = angle * M_PI / 180;
				angle1 = angle1 * M_PI / 180;
				angle2 = angle2 * M_PI / 180;

				float delta_length = abs((stroke_width / 2) / tan(angle / 2));

				line.setSize(sf::Vector2f(line.getSize().x - delta_length, line.getSize().y));

				next_line.setSize(sf::Vector2f(next_line.getSize().x - delta_length, next_line.getSize().y));
				next_line.setPosition(next_line.getPosition().x + delta_length * cos(angle2), next_line.getPosition().y + delta_length * sin(angle2));		
			}
			
			window.draw(line, transform);
			line.setSize(sf::Vector2f(line.getSize().x, -line.getSize().y));
			window.draw(line, transform);
			if (i > 0 && i < fpoint.size() - 1) {
				joint[i - 1].setFillColor(set_SF_Color(stroke));
				window.draw(joint[i - 1], transform); 
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
				fillArea.setFillColor(set_SF_Color(fill));
				window.draw(fillArea, transform);
				i = end - 1;
			}
		}
		drawPolyline(window, transform);
	}

	void SF_Polyline::draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform) {
		drawPolyline2(window, transform);
	}
	//-----------end-of-implementation-----------//
	/*


	*/
	// class SF_Polygon
	SF_Polygon::SF_Polygon(const Polygon* other) : Polygon(*other) {
		int vertex = (int)point.size();
		polygon.setPointCount(vertex);
		for (int i = 0; i < vertex; ++i)
			polygon.setPoint(i, sf::Vector2f(point[i].x, point[i].y));
		polygon.setFillColor(set_SF_Color(fill));
		polygon.setOutlineColor(set_SF_Color(stroke));
		polygon.setOutlineThickness(stroke_width / 2);

		set_SF_ShapeTransform<sf::ConvexShape>(polygon, transform);

		outline = polygon;
		outline.setOutlineThickness(-stroke_width / 2);
		outline.setFillColor(sf::Color::Transparent);
	}

	void SF_Polygon::draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform) {
		window.draw(polygon, transform);
		window.draw(outline, transform);
	}
	//-----------end-of-implementation-----------//
	/*


	*/
	// class SF_Text
	SF_Text::SF_Text(const Text* other) : Text(*other) {
		if (!font.loadFromFile(string("SFML/font-family/" + font_family + ".ttf"))) exit(1);
		text.setFont(font);
		text.setCharacterSize(font_size);
		text.setPosition(x, y - font_size);
		text.setFillColor(set_SF_Color(fill));
		text.setString(data);

		set_SF_ShapeTransform<sf::Text>(text, transform);
	}

	void SF_Text::draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform) {
		window.draw(text, transform);
	}
	//-----------end-of-implementation-----------//
	/*


	*/
	// class SF_Path

	SF_Path::SF_Path(const Path* path) : Path(*path), SF_Line(){}

	void SF_Path::drawPath(sf::RenderWindow& window, sf::Transform& transform) {
		for (auto x : path) {
			char cmd = x.first;

			if (cmd == 'V' || cmd == 'H') {
				SF_Line line1 = new Line(x.second[0], x.second[1]);
				SF_Line line2 = new Line(x.second[0], x.second[2]);
				line1.draw_SF_Shape(window, transform);
				line2.draw_SF_Shape(window, transform);
			}

			else if (cmd == 'c' || cmd == 'C') {
				vector<Point> CVertices = Path::CVertices(x.second);

				for (int i = 0; i < CVertices.size() - 1; i++) {
					SF_Line line = new Line(CVertices[i], CVertices[i + 1]);
					line.draw_SF_Shape(window, transform);
				}
			}

			else if (cmd == 'L' || cmd == 'l' || cmd == 'h' || cmd == 'v' || cmd == 'z' || cmd == 'Z') {
				SF_Line line = new Line(x.second[0], x.second[1]);
				line.draw_SF_Shape(window, transform);
			}
		}
	}
	void SF_Path::draw_SF_Shape(sf::RenderWindow& window, sf::Transform& transform) {
		drawPath(window, transform);
	}
	//-----------end-of-implementation-----------//
	/*


	*/
	// class SF_SVGImage
	SF_SVGImage::SF_SVGImage() : SVGImage() {

	}

	SF_SVGImage::SF_SVGImage(const SVGImage& svgImage) : SVGImage(svgImage) {
		Convert<SF_Shape, SF_Rectangle, SF_Ellipse, SF_Circle, SF_Line, SF_Polyline, SF_Polygon, SF_Text, SF_Path>(svgImage, shapes);
	}

	void SF_SVGImage::draw_SF_SVGImage(sf::RenderWindow& window, sf::Transform& transform) {
		for (auto shape : shapes) {
			shape->draw_SF_Shape(window, transform);
		}
	}
	//-----------end-of-implementation-----------//
	/*


	*/
	// Function namespace
	template <class sf_shape>
	void set_SF_ShapeTransform(sf_shape& shape, const vector< pair<int, Point> >& transform) {
		for (int i = 0; i < transform.size(); ++i) {
			if (transform[i].first == Translate) {
				shape.move(transform[i].second.x, transform[i].second.y);
			}
			else if (transform[i].first == Rotate) {
				float alpha = transform[i].second.x * M_PI / 180;
				float x = shape.getPosition().x;
				float y = shape.getPosition().y;
				shape.rotate(transform[i].second.x);
				shape.setPosition(x * cos(alpha) - y * sin(alpha), x * sin(alpha) + y * cos(alpha));
			}
			else if (transform[i].first == Scale) {
				shape.scale(transform[i].second.x, transform[i].second.y);
			}
		}
	}

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