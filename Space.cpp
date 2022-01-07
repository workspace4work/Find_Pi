# include "Space.h"

// Private functions
void Space::setFont()
{
	if (!this->font.loadFromFile("fonts/arial.ttf"))
	{
		std::cout << "Cannot Find Font in Mixer" << std::endl;
	}

	four.setFont(font); 
	four.setString("Hello world");
	four.setCharacterSize(24);
	four.setFillColor(sf::Color::White);
	four.setStyle(sf::Text::Bold);
}

void Space::initvariables()
{
	this->setFont();

	this->circle = std::make_shared<sf::CircleShape>();
	this->circle->setRadius(300.f);
	this->circle->setOutlineColor(sf::Color::Black);
	this->circle->setOutlineThickness(3);
	this->circle->setPointCount(1000);

	this->square = std::make_shared<sf::RectangleShape>(sf::Vector2f(600.f, 600.f));
	this->square->setFillColor(sf::Color(155,155,155));


	//this->points.push_back(std::make_shared<sf::RectangleShape>(sf::Vector2f(2.f, 2.f)));
	//this->point->setFillColor(sf::Color::Green);

	this->wait = 0.2;

	this->window = nullptr;
}

void Space::initWindow()
{
	this->videomode.height = 600;
	this->videomode.width = 1440;
	this->window = new sf::RenderWindow(this->videomode, "Find-Pi", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(30);

	// this->window->setVerticalSyncEnabled(true);
}

// Constructor & Destructor
Space::Space()
{
	this->initvariables();
	this->initWindow();
}

Space::~Space()
{
	// std::cout << "Window deleted" << std::endl;
	delete this->window;
}

// Public

const bool Space::running() const
{
	return this->window->isOpen();
}

void Space::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {

		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		default:
			break;
		}
	}
}

void Space::update()
{
	this->pollEvents();
}

void Space::render()
{
	/*
		@return void
		- clear old frame
		- render objects
		- display the new frame
	*/
	//this->window->clear(sf::Color(0,0,0,0));
	this->window->draw(four);
	
	this->window->draw(*(this->square));
	this->window->draw(*(this->circle));
	
	this->window->display();
}