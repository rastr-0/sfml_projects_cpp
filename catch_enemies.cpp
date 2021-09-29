/*
	I've made a game where you need try to catch all enemies.
		if you miss ten enemies, you will die
		Later I'm going to add textures
														*/
#include <ctime>
#include <SFML/Graphics.hpp>
using namespace sf;
void player_control(CircleShape& player, const RenderWindow& window);
int main() {
	srand(time(0));
	RenderWindow window(VideoMode(640, 480), "sfml");
	window.setFramerateLimit(60);

	RectangleShape health;
	health.setSize(Vector2f(150.f, 20.f));
	health.setPosition(Vector2f(300, 10));
	health.setFillColor(Color::Red);
	const float constant_health_x = health.getSize().x / 10;

	RectangleShape enemy;
	enemy.setSize(Vector2f(50.f, 50.f));
	enemy.setFillColor(Color::Black);
	std::vector<RectangleShape> enemies;

	CircleShape player;
	player.setRadius(40.f);
	player.setFillColor(Color::Cyan);
	player.setPosition(Vector2f(30, window.getSize().y / 2));

	short enemies_timer = 0;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(Color(58, 209, 118, 255));
		player_control(player, window);
		if (enemies_timer < 80)
			enemies_timer++;
		else if (enemies_timer == 80) {
			enemy.setPosition(Vector2f(300, rand() % static_cast<int> (window.getSize().y - enemy.getSize().y)));
			enemies.push_back(enemy);
			enemies_timer = 0;
		}
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i].move(-3.f, 0.f);
			if (enemies[i].getPosition().x < 0) {
				health.setSize(Vector2f(health.getSize().x - constant_health_x, health.getSize().y));
				enemies.erase(enemies.begin() + i);
			}
		}
		for (int i = 0; i < enemies.size(); i++) {
			if (player.getGlobalBounds().intersects(enemies[i].getGlobalBounds())) {
				enemies.erase(enemies.begin() + i);
				break;
			}
		}
		if (health.getSize().x == 0)
			window.close();
		window.draw(player);
		window.draw(health);
		for (int i = 0; i < enemies.size(); i++) {
			window.draw(enemies[i]);
		}
		window.display();
	}
}
void player_control(CircleShape& player, const RenderWindow& window) {
	if (Keyboard::isKeyPressed(Keyboard::W) && player.getPosition().y > 0)
			player.move(0.f, -5.f);
		else if (Keyboard::isKeyPressed(Keyboard::S) && (player.getPosition().y + player.getRadius() * 2) < window.getSize().y)
			player.move(0.f, 5.f);
}