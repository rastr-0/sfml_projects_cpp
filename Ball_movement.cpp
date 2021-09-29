/*
	In this project I've made a simple ball's movement, 
	it's a kind of simple simulation of rebound of the ball.
																	*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
int main() {
	int direction = 1;
	RenderWindow window(VideoMode(640, 480), "example");
	window.setFramerateLimit(60);
	CircleShape hoop;
	CircleShape ball;

	hoop.setFillColor(Color::Black);
	hoop.setOutlineThickness(2);
	hoop.setRadius(40.f);
	hoop.setPosition(Vector2f(20.f, 20.f));

	ball.setRadius(10.f);
	ball.setFillColor(Color::Red);
	ball.setOutlineThickness(2);
	ball.setPosition(320, 400);
	bool is_pressed = false;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(Color::Yellow);
		if (hoop.getPosition().x == 0)
			direction = 1; // to the right
		else if (hoop.getPosition().x + hoop.getRadius() * 2 == window.getSize().x)
			direction = 0; // to the left
		if (direction == 0)
			hoop.move(-5.f, 0);
		else
			hoop.move(5.f, 0);
		if (!is_pressed)
			ball.setPosition(Mouse::getPosition(window).x, 400);
		if (Mouse::isButtonPressed(Mouse::Left)) {
			is_pressed = true;
		}
		if (is_pressed)
			ball.setPosition(ball.getPosition().x, ball.getPosition().y - 5);
		if (ball.getPosition().y < -1 * ball.getRadius() 
			|| ball.getGlobalBounds().intersects(hoop.getGlobalBounds())) {
			is_pressed = false;
			ball.setPosition(320, 400);
		}
		window.draw(hoop);
		window.draw(ball);
		window.display();
	}
	return 0;
}