#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
class dvd {
private:
	float x_speed, y_speed;
	float x, y;
	sf::Texture dvd_texture;
	sf::Sprite dvd_sprite;
	std::vector<sf::Color> colors = { 
		sf::Color::Red, 
		sf::Color::Green, 
		sf::Color::Blue,
		sf::Color::Yellow
	};
public:
	dvd();
	void move_dvd();
	void check_boundary(const sf::Vector2f&);
	void set_color();
	void display();
	sf::Sprite& draw();
};
dvd::dvd() {
	x = 1 + rand() % 400;
	y = 1 + rand() % 400;
	x_speed = 0.3f;
	y_speed = 0.3f;
	if (!dvd_texture.loadFromFile("Textures_for_projects/dvd.png"))
		return;
	dvd_sprite.setTexture(dvd_texture);
	dvd_sprite.setPosition(sf::Vector2f(x, y));
	dvd_sprite.setColor(sf::Color::Red);
}
void dvd::move_dvd() {
	x += x_speed;
	y += y_speed;
}
void dvd::set_color() {
	int random = 1 + rand() % 3;
	// this condition is for not creating same colors
	if (dvd_sprite.getColor() == colors[random]){
		if (random < 3)
			random++;
		else
			random--;
	}
	dvd_sprite.setColor(colors[random]);
}
void dvd::display() {
	dvd_sprite.setPosition(x, y);
}
sf::Sprite& dvd::draw() {
	return dvd_sprite;
}
void dvd::check_boundary(const sf::Vector2f& window) {
	if (x + dvd_texture.getSize().x >= window.x) {
		x_speed = -x_speed;
		set_color();
	}
	else if (x <= 0) {
		x_speed = -x_speed;
		set_color();
	}
	else if (y + dvd_texture.getSize().y >= window.y) {
		y_speed = -y_speed;
		set_color();
	}
	else if (y <= 0) {
		y_speed = -y_speed;
		set_color();
	}
}
int main() {
	srand(time(0));
	dvd one;
	sf::RenderWindow window(sf::VideoMode(640, 480), "dvd");
	window.setFramerateLimit(250);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		one.move_dvd();
		one.check_boundary(sf::Vector2f(window.getSize().x, window.getSize().y));
		one.display();
		window.clear();
		window.draw(one.draw());
		window.display();
	}
}

