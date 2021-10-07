/*
		In this projects I made a 360 degree shooter.
		You need to know a few things before using or reading my code.
		First, I used normalized vector for direction of bullets.
		What does it actually mean? You just need to know this formules.
		|v| = sqrt(pow(x, 2), pow(y, 2)), length of vector from the centre
		u = v / |v|, normalized vector(that's mean to make length of vector does not exceed 1).
		Normalized vector can be come in handy, because we need only direction, not the length.
																								*/

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
using namespace sf;
void control(CircleShape& player, const Window& window);
class Bullet {
public:
	CircleShape shape;
	Vector2f current_velocity;
	float max_speed;
	Bullet(float radius = 5.f) : current_velocity(0.f, 0.f), max_speed(15.f){
		this->shape.setRadius(radius);
		this->shape.setFillColor(Color::Red);
	}
};
int main() {
	srand(time(0));
	RenderWindow window(VideoMode(640, 480), "360 degree shooter");
	window.setFramerateLimit(60);
	// player
	CircleShape player(40.f);
	player.setFillColor(Color::Black);
	// vectors
	Vector2f player_center;
	Vector2f mouse_position;
	Vector2f aim_direction;
	Vector2f aim_direction_normalized;
	player.setRadius(40.f);
	player.setFillColor(Color::Black);
	// enemy
	RectangleShape enemy;
	enemy.setSize(Vector2f(45.f, 45.f));
	enemy.setFillColor(Color::Blue);
	std::vector<RectangleShape> enemies;
	// bullets
	Bullet b1;
	std::vector<Bullet> bullets;
	short enemy_timer = 0;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		control(player, window);
		// initialize player_centre, mouse_position, aim_direction, aim_direction_normolized
		player_center = Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
		mouse_position = Vector2f(Mouse::getPosition(window));
		aim_direction = Vector2f(mouse_position.x - player_center.x, mouse_position.y - player_center.y);
		// in this line I normalized a vector. U.x = V.x / sqrt(V.x^2 + V.y^2), U.y = V.y / sqrt(V.x^2 + V.y^2)
		aim_direction_normalized = Vector2f(aim_direction.x / sqrt(pow(aim_direction.x, 2) + pow(aim_direction.y, 2)), aim_direction.y / sqrt(pow(aim_direction.x, 2) + pow(aim_direction.y, 2)));
		// shooting
		if (Mouse::isButtonPressed(Mouse::Left)) {
			b1.shape.setPosition(player_center);
			b1.current_velocity = aim_direction_normalized * b1.max_speed;
			bullets.push_back(b1);
		}
		for (short i = 0; i < bullets.size(); i++)
		{
			bullets[i].shape.move(bullets[i].current_velocity);
			if (bullets[i].shape.getPosition().x < 0
				|| bullets[i].shape.getPosition().x > window.getSize().x
				|| bullets[i].shape.getPosition().y < 0
				|| bullets[i].shape.getPosition().y > window.getSize().y) {
				bullets.erase(bullets.begin() + i);
			}
			else {
				for (short j = 0; j < enemies.size(); j++) {
					if (bullets[i].shape.getGlobalBounds().intersects(enemies[j].getGlobalBounds()))
					{
						enemies.erase(enemies.begin() + j);
						bullets.erase(bullets.begin() + i);
						break;
					}
				}
			}
		}
		if (enemy_timer < 30)
			enemy_timer++;
		else if (enemy_timer == 30){
			enemy.setPosition(Vector2f(rand() % window.getSize().x - 2 * enemy.getSize().x, rand() % window.getSize().y - 2 * enemy.getSize().y));
			enemies.push_back(enemy);
			enemy_timer = 0;
		}
		window.clear(Color::White);
		window.draw(player);
		for (short i = 0; i < bullets.size(); i++) {
			window.draw(bullets[i].shape);
		}
		for (short i = 0; i < enemies.size(); i++)
			window.draw(enemies[i]);
		window.display();
	}
}
void control(CircleShape& player, const Window& window) {
	if (Keyboard::isKeyPressed(Keyboard::A))
		player.move(-6.f, 0.f);
	else if (Keyboard::isKeyPressed(Keyboard::D))
		player.move(6.f, 0.f);
	else if (Keyboard::isKeyPressed(Keyboard::W))
		player.move(0.f, -6.f);
	else if (Keyboard::isKeyPressed(Keyboard::S))
		player.move(0.f, 6.f);
}