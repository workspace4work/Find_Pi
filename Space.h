#ifndef SPACE_H
#define SPACE_H

# include <vector>
# include <memory>
# include <iostream>
# include <thread>

# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include <SFML/Network.hpp>
# include <SFML/Window.hpp>
# include <SFML/System.hpp>
# include <SFML/Window.hpp>

# include "dot.h"

// Main Application
class Space
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	sf::Clock clock;

	double wait, res;

	std::shared_ptr<sf::CircleShape> circle;
	std::shared_ptr<sf::RectangleShape> square;
	
	std::shared_ptr<sf::CircleShape> dot;
	sf::Vector2f pos;

	std::vector<std::shared_ptr<ddd::dot>> dat;

	sf::Font font;

	sf::Text pi;

	int curr, ct;
	int i;

	void initvariables();
	void initWindow();
	void setFont();

public:
	Space(std::vector<std::shared_ptr<ddd::dot>> &dat);

	virtual ~Space();

	const bool running() const;

	void pollEvents();
	void update();
	void render();

};

#endif