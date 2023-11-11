#include "src/SVGImage.h"

int main() {
	// Tạo một cửa sổ SFML.
	sf::RenderWindow window(sf::VideoMode(1024, 720), "SFML Drawing", sf::Style::Default, sf::ContextSettings(0, 0, 8));
	sf::Vector2f screenPosition(400, 300);
	float zoom = 1;
	// load file lưu vô class
	SVGImage image("sample.svg");

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

		// vẽ hình
		image.draw(window, transform);

		// Di chuyển màn hình
		window.setView(sf::View(screenPosition, sf::Vector2f(window.getSize().x, window.getSize().y)));
		window.display();
	}
	return 0;
}