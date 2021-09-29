/* 
		I've made simple shooter. You can shoot in your enemies and kill them.
	I also delete bullets and enemies which are out of the screen.
	Later I'm going to make score count and remake enemies with using textures
																				*/

#include <iostream>
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace sf;
int main() {
	srand(time(0));
	RenderWindow window(VideoMode(640, 480), "Game");
	window.setFramerateLimit(60);
	int shoot_timer_bullets = 0;
	int shoot_timer_enemies = 0;
	std::vector<RectangleShape> enemies;
	std::vector<CircleShape> bullets;

	CircleShape player;
	player.setRadius(40.f);
	player.setFillColor(Color::White);
	player.setPosition(Vector2f(window.getSize().x / 2 - player.getRadius(), window.getSize().y - (2 * player.getRadius()) - 10.f));

	CircleShape bullet;
	bullet.setRadius(10.f);
	bullet.setFillColor(Color::Blue);

	RectangleShape enemy;
	enemy.setSize(Vector2f(50.f, 50.f));
	enemy.setFillColor(Color::Magenta);

	Vector2f player_center;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		player_center = Vector2f(player.getPosition().x + player.getRadius() - 10.f, player.getPosition().y + player.getRadius());
		// player movement
		if (Keyboard::isKeyPressed(Keyboard::W))
			player.move(0.f, -5.f);
		else if (Keyboard::isKeyPressed(Keyboard::S))
			player.move(0.f, 5.f);
		else if (Keyboard::isKeyPressed(Keyboard::A))
			player.move(-5.f, 0.f);
		else if (Keyboard::isKeyPressed(Keyboard::D))
			player.move(5.f, 0.f);
		// shoot
		if (shoot_timer_bullets < 10)
			shoot_timer_bullets++;
		// generate one bullet every 10 iterations, you can make this number bigger or less, that depends on your wish
		if (Mouse::isButtonPressed(Mouse::Left) && shoot_timer_bullets == 10) {
			bullet.setPosition(player_center);
			bullets.push_back(bullet);
			shoot_timer_bullets = 0;
		}
		if (shoot_timer_enemies < 30)
			shoot_timer_enemies++;
		// generate enemies every 30 iterations
		if (shoot_timer_enemies == 30) {
			enemy.setPosition(Vector2f(rand() % static_cast<int>(window.getSize().x - enemy.getSize().x - 10.f), 0 - enemy.getSize().y));
			enemies.push_back(enemy);
			shoot_timer_enemies = 0;
		}
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].move(0.f, -7.f);
			// delete bullets which are out of screen
			if (bullets[i].getPosition().y < 0)
				bullets.erase(bullets.begin() + i);
		}
		// move enemies and delete enemies which are out of the screen
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].move(0.f, 3.f);
			if (enemies[i].getPosition().y > window.getSize().y)
				enemies.erase(enemies.begin() + i);
		}
		// check collision
		for (size_t i = 0; i < bullets.size(); i++)
		{
			for (size_t j = 0; j < enemies.size(); j++)
			{
				if (bullets[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {
					bullets.erase(bullets.begin() + i);
					enemies.erase(enemies.begin() + j);
					break;
				}
			}
		}
		window.clear(Color(24, 40, 70, 255));
		window.draw(player);
		for (size_t i = 0; i < enemies.size(); i++)
		{
			window.draw(enemies[i]);
		}
		for (size_t i = 0; i < bullets.size(); i++)
		{
			window.draw(bullets[i]);
		}
		window.display();
	}
}