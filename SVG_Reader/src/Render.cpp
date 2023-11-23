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