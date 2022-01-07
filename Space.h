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

	std::vector<std::shared_ptr<sf::RectangleShape>> points;

	sf::Font font;

	sf::Text denom;
	sf::Text numer;
	sf::Text four;
	sf::Text pi;


	void initvariables();
	void initWindow();
	void setFont();

public:
	Space();

	virtual ~Space();

	const bool running() const;

	void pollEvents();
	void update();
	void render();

};

#endif