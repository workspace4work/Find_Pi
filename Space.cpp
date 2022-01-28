# include "Space.h"

// Private functions
void Space::setFont()
{
	if (!this->font.loadFromFile("fonts/arial.ttf"))
	{
		std::cout << "Cannot Find Font" << std::endl;
	}

	pi.setFont(font); 
	pi.setString("0");
	pi.setCharacterSize(48);
	pi.setFillColor(sf::Color::White);
	pi.setPosition(sf::Vector2f(800.f, 300.f));
}

void Space::initvariables()
{
	curr = 0;

	this->setFont();

	this->circle = std::make_shared<sf::CircleShape>();
	this->circle->setRadius(300.f);
	this->circle->setOutlineColor(sf::Color::Black);
	this->circle->setOutlineThickness(3);
	this->circle->setPointCount(1000);

	this->dot = std::make_shared<sf::CircleShape>();
	this->dot->setRadius(3.f);
	this->dot->setFillColor(sf::Color::Red);
	
	this->pos = sf::Vector2f(0.f, 0.f);

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
Space::Space(std::vector<std::shared_ptr<ddd::dot>> &dat)
{
	this->dat = dat;

	//std::cout << dat[1]->x << " " << dat[1]->y << " " << dat[1]->d << " " << std::endl;

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
			else if (this->ev.key.code == sf::Keyboard::Right)
			{
				if (curr < 250000-1)
				{
					curr++;
					if (this->dat[curr]->d <= 300.0)
					{
						ct++;
						pi.setString(std::to_string((float)ct / (float)curr*4.0));
					}
				}
			}
			else if (this->ev.key.code == sf::Keyboard::Left)
			{
				if (curr > 0)
				{
					if (this->dat[curr]->d <= 300.0)
					{
						ct--;
						pi.setString(std::to_string((float)ct / (float)curr*4.0));
					}
					curr--;
				}
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
	this->window->clear(sf::Color::Black);
	this->window->draw(pi);
	
	this->window->draw(*(this->square));
	this->window->draw(*(this->circle));

	for (i = 0; i < curr; i++)
	{
		this->pos.x = dat[i]->x;
		this->pos.y = dat[i]->y;
		this->dot->setPosition(this->pos);
		this->window->draw(*(this->dot));
	}
	
	this->window->display();
}