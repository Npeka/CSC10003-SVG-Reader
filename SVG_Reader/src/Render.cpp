#include "Render.h"
#include "SVGImage.h"

// class DrawableRectangle
// Constructor
void DrawableRectangle::setAtrribute() {
	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setPosition(x, y);
	rectangle.setFillColor(set_SF_Color(fill));
	rectangle.setOutlineColor(set_SF_Color(stroke));
	rectangle.setOutlineThickness(stroke_width / 2);

	outline = rectangle;
	outline.setFillColor(sf::Color::Transparent);
	outline.setOutlineThickness(-stroke_width / 2);
}

// Virtual method
void DrawableRectangle::draw(sf_Render(window, transform)) {
	sf_Transform(window.draw(rectangle, transform), window.draw(outline, transform));
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawableEllipse
// Constructor
void DrawableEllipse::setAtrribute() {
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

	outline = ellipse;
	outline.setFillColor(sf::Color::Transparent);
	outline.setOutlineThickness(-stroke_width / 2);
}

// Virtual method
void DrawableEllipse::draw(sf_Render(window, transform)) {
	sf_Transform(window.draw(ellipse, transform), window.draw(outline, transform));
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawableCircle
// Constructor
void DrawableCircle::setAtrribute() {
	circle.setRadius(r);
	circle.setPosition(cx - r, cy - r);
	circle.setFillColor(set_SF_Color(fill));
	circle.setOutlineColor(set_SF_Color(stroke));
	circle.setOutlineThickness(stroke_width / 2);
	circle.setPointCount(2000);

	outline = circle;
	outline.setFillColor(sf::Color::Transparent);
	outline.setOutlineThickness(-stroke_width / 2);
}

// Virtual method
void DrawableCircle::draw(sf_Render(window, transform)) {
	sf_Transform(window.draw(circle, transform), window.draw(outline, transform));
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawableLine

// Constructor
DrawableLine::DrawableLine(const Line* other) : Line(*other) {
	setAtrribute();
}

void DrawableLine::setAtrribute() {
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
}

void DrawableLine::setLine(Color stroke) {
	this->line.setFillColor(set_SF_Color(stroke));
}

// Virtual method
void DrawableLine::draw(sf_Render(window, transform)) {
	sf::RectangleShape tmpLine = line;
	sf_Transform(window.draw(line, transform));
	float length = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	tmpLine.setSize(sf::Vector2f(length, -stroke_width / 2));
	sf_Transform(window.draw(tmpLine, transform));
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawablePolyline
// Private
	// Methods
sf::RectangleShape DrawablePolyline::Line(FPoint start, FPoint end) {
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

void DrawablePolyline::drawPolyline(sf_Render(window, transform)) {
	for (int i = 0; i < fpoint.size() - 1; i++) {
		window.draw(lines[i], transform);

		if (i > 0 && i < fpoint.size() - 1) {
			joint[i - 1].setFillColor(set_SF_Color(stroke));
			window.draw(joint[i - 1], transform); //draw joint
		}
	}
}

void DrawablePolyline::drawPolyline2(sf_Render(window, transform)) {
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
			fillArea.setFillColor(set_SF_Color(fill));
			window.draw(fillArea, transform);
			i = end - 1;
		}
	}
	drawPolyline(window, transform);

}
// Public
// Constructor
void DrawablePolyline::setAtrribute() {
	int size = (int)fpoint.size();
	lines = new sf::RectangleShape[size];
	joint = new sf::ConvexShape[size - 2];

	for (int i = 0; i < size - 1; i++) {
		lines[i] = Line(fpoint[i], fpoint[i + 1]);
		lines[i].setFillColor(set_SF_Color(stroke));

		if (i > 0 && i < size - 1) {
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

// Virtual method
void DrawablePolyline::draw(sf_Render(window, transform)) {
	sf_Transform(drawPolyline2(window, transform));
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawablePolygon
// Constructor
void DrawablePolygon::setAtrribute() {
	int vertex = (int)point.size();
	polygon.setPointCount(vertex);
	for (int i = 0; i < vertex; ++i)
		polygon.setPoint(i, sf::Vector2f(point[i].x, point[i].y));
	polygon.setFillColor(set_SF_Color(fill));
	polygon.setOutlineColor(set_SF_Color(stroke));
	polygon.setOutlineThickness(stroke_width / 2);

	outline = polygon;
	outline.setOutlineThickness(-stroke_width / 2);
	outline.setFillColor(sf::Color::Transparent);
}

// Virtual method
void DrawablePolygon::draw(sf_Render(window, transform)) {
	sf_Transform(window.draw(polygon, transform), window.draw(outline, transform));
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// class DrawableText
// Constructor
void DrawableText::setAtrribute() {
	if (!font.loadFromFile(string("SFML/font-family/" + font_family + ".ttf")));
	text.setFont(font);
	text.setCharacterSize(font_size);
	text.setPosition(x, y - font_size);
	text.setFillColor(set_SF_Color(fill));
	text.setOutlineColor(set_SF_Color(stroke));
	text.setOutlineThickness(stroke_width);
	text.setString(data);
}

// Virtual method
void DrawableText::draw(sf_Render(window, transform)) {
	sf_Transform(window.draw(text, transform));
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/

// class SF_Path

// Constructor
void DrawablePath::setAtrribute() {}

Color DrawablePath::getStroke() {
	return Path::stroke;
}

void DrawablePath::drawPath(sf::RenderWindow& window, sf::Transform& transform) {
	for (auto x : path) {
		char cmd = x.first;
		if (cmd == 'V' || cmd == 'H') {
			DrawableLine line1 = new Line(x.second[0], x.second[1]);
			DrawableLine line2 = new Line(x.second[0], x.second[2]);
			line1.setLine(getStroke());
			line2.setLine(getStroke());
			line1.draw(window, transform);
			line2.draw(window, transform);
		}

		else if (cmd == 'c' || cmd == 'C') {
			vector<Point> CVertices = Path::CVertices(x.second);

			for (int i = 0; i < CVertices.size() - 1; i++) {
				DrawableLine line = new Line(CVertices[i], CVertices[i + 1]);
				line.setLine(getStroke());
				line.draw(window, transform);
			}
		}

		else if (cmd == 'L' || cmd == 'l' || cmd == 'h' || cmd == 'v' || cmd == 'z' || cmd == 'Z') {
			DrawableLine line = new Line(x.second[0], x.second[1]);
			line.setLine(getStroke());
			line.draw(window, transform);
		}
	}
}

// Virtual method
void DrawablePath::draw(sf_Render(window, transform)) {
	//SF_Transform_First(this->transform, window, transform);
	//SF_Transform_Second(this->transform, window, transform);
	sf_Transform(drawPath(window, transform));
}

//-----------END-OF-IMPLEMENTATION-----------//
void SVGImage::render() {
	sf::RenderWindow window(sf::VideoMode(1024, 720), "SFML Drawing", sf::Style::Default, sf::ContextSettings(0, 0, 8));
	sf::View view(sf::FloatRect(0, 0, viewbox.width, viewbox.height));
	sf::Vector2f screenPosition(viewbox.width / 2, viewbox.height / 2);

	window.clear(set_SF_Color(background)); //set color background

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

		for (int i = 0; i < figure.size(); i++) {
			figure[i]->draw(window, transform);
		}

		// Di chuyển màn hình
		window.setView(sf::View(screenPosition, sf::Vector2f(window.getSize().x, window.getSize().y)));
		window.display();
	}
}
//-----------END-OF-IMPLEMENTATION-----------//
/*



*/
// Function namespace
void SF_Transform_First(const vector <pair <int, Point>>& t, sf_Render(window, transform)) {
	for (int i = 0; i < t.size(); ++i) {
		if (t[i].first == Translate) {
			transform.translate(t[i].second.x, t[i].second.y);
		}
		else if (t[i].first == Rotate) {
			transform.rotate(t[i].second.x);
		}
		else if (t[i].first == Scale) {
			transform.scale(t[i].second.x, t[i].second.y);
		}
	}
}

void SF_Transform_Second(const vector <pair <int, Point>>& t, sf_Render(window, transform)) {
	for (int i = t.size() - 1; i >= 0; --i) {
		if (t[i].first == Translate) {
			transform.translate(-t[i].second.x, -t[i].second.y);
		}
		else if (t[i].first == Rotate) {
			transform.rotate(-t[i].second.x);
		}
		else if (t[i].first == Scale) {
			transform.scale(1 / t[i].second.x, 1 / t[i].second.y);
		}
	}
}

sf::Color set_SF_Color(const Color& color) {
	return sf::Color(color.r, color.g, color.b, color.a);
}

//-----------END-OF-IMPLEMENTATION-----------//