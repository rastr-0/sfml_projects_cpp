/*
	I've made a game where you need try to catch all enemies.
		if you miss ten enemies, you will die.
														*/
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace sf;
void player_control(Sprite& player, const Window& window);
int main() {
	srand(time(0));
	RenderWindow window(VideoMode(640, 480), "catch_enemies_with_textures");
	window.setFramerateLimit(60);

	// player
	Texture player_texture;
	if (!player_texture.loadFromFile("Textures_for_projects/player.png"))
		throw "smth goes wrong";
	Sprite player;
	player.setTexture(player_texture);
	player.setScale(Vector2f(0.4f, 0.4f));
	// enemy
	Texture enemy_texture;
	if (!enemy_texture.loadFromFile("Textures_for_projects/enemy.png"))
		throw "smth goes wrong";
	Sprite enemy;
	enemy.setTexture(enemy_texture);
	enemy.setScale(Vector2f(0.4f, 0.4f));
	enemy.setPosition(Vector2f(450.f, 100.f));
	std::vector<Sprite> enemies;
	// background
	Texture background_texture;
	if (!background_texture.loadFromFile("Textures_for_projects/background.png"))
		throw "smth goes wrong";
	Sprite background;
	background.setTexture(background_texture);
	background.setScale(Vector2f(1.2f, 1.f));
	background.setPosition(Vector2f(0.f, -60.f));
	// health
	RectangleShape health;
	health.setSize(Vector2f(150.f, 20.f));
	health.setPosition(Vector2f(300, 10));
	health.setFillColor(Color::Red);
	const float constant_health_x = health.getSize().x / 10;

	short enemies_timer = 0;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();
		player_control(player, window);
		if (enemies_timer < 80)
			enemies_timer++;
		else if (enemies_timer == 80) {
			enemy.setPosition(Vector2f(window.getSize().x + 50, rand() % window.getSize().y ));
			enemies.push_back(enemy);
			enemies_timer = 0;
		}
		for (short i = 0; i < enemies.size(); i++) {
			enemies[i].move(-3.f, 0.f);
			if (enemies[i].getPosition().x < 0) {
				health.setSize(Vector2f(health.getSize().x - constant_health_x, health.getSize().y));
				enemies.erase(enemies.begin() + i);
			}
		}
		for (short i = 0; i < enemies.size(); i++) {
			if (player.getGlobalBounds().intersects(enemies[i].getGlobalBounds())) {
				enemies.erase(enemies.begin() + i);
				break;
			}
		}
		if (health.getSize().x == 0)
			window.close();
		window.draw(background);
		window.draw(health);
		window.draw(enemy);
		window.draw(player);
		for (short i = 0; i < enemies.size(); i++)
			window.draw(enemies[i]);
		window.display();
	}
	return 0;
}
void player_control(Sprite& player, const Window& window) {
	if (Keyboard::isKeyPressed(Keyboard::W) && player.getPosition().y > 0)
		player.move(0.f, -7.f);
	else if (Keyboard::isKeyPressed(Keyboard::S) && player.getPosition().y + 120 < window.getSize().y)
		player.move(0.f, 7.f);
}