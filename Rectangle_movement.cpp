/*
	In this project I've made a simple movement of rectangle.
	Rectangle also changes color if you press left mouse button.
	rectangle can't go off the screen because of borders.
																*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
void update_and_draw(RectangleShape& rectangle, RenderWindow& window);
int main() {
	RenderWindow window(VideoMode(640, 480), "example");
	window.setFramerateLimAit(60);
	RectangleShape rectangle(Vector2f(70, 70));
	rectangle.setPosition((float)window.getPosition().x / 2, (float)window.getPosition().y / 2);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}
		update_and_draw(rectangle, window);
	}
	return 0;
}
void update_and_draw(RectangleShape& rectangle, RenderWindow& window) {
	// keyboard
	if (Keyboard::isKeyPressed(Keyboard::D) && (rectangle.getPosition().x + rectangle.getSize().x) < window.getSize().x) {
		rectangle.move(Vector2f(3, 0));
	}
	else if (Keyboard::isKeyPressed(Keyboard::A) && rectangle.getPosition().x > 0) {
		rectangle.move(Vector2f(-3, 0));
	}
	else if (Keyboard::isKeyPressed(Keyboard::W) && rectangle.getPosition().y > 0) {
		rectangle.move(Vector2f(0, -3));
	}
	else if (Keyboard::isKeyPressed(Keyboard::S) && (rectangle.getPosition().y + rectangle.getSize().y) < window.getSize().y) {
		rectangle.move(Vector2f(0, 3));
	}
	// mouse
	if (Mouse::isButtonPressed(Mouse::Left)) {
		rectangle.setFillColor(Color::Blue);
	}
	else
		rectangle.setFillColor(Color::Black);
	// show
	window.clear(Color::Yellow);
	window.draw(rectangle);
	window.display();
}