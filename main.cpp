# include <iostream>
# include <memory>
#include <fstream>
#include <string>
#include <sstream>


# include <SFML/graphics.hpp>
# include <SFML/network.hpp>
# include <SFML/window.hpp>
# include <SFML/system.hpp>

# include "Space.h"
# include "dot.h"

void parsing(std::ifstream &file, std::vector<std::shared_ptr<ddd::dot>> &dat);

int main()
{

	std::ifstream file("Data1.csv"); // declare file stream
	std::vector<std::shared_ptr<ddd::dot>> dat;
	parsing(file, dat);

	std::unique_ptr<Space> window = std::make_unique<Space>(dat);

	while (window->running())
	{
		// handle events
		window->update();

		window->render();
	}


	return 0;
}


void parsing(std::ifstream &file, std::vector<std::shared_ptr<ddd::dot>> &dat)
{
	dat.reserve(250000);
	// Make sure the file is open
	if (!file.is_open()) throw std::runtime_error("Could not open file");

	std::string val, line;
	float x, y, d;
	while (std::getline(file, line))
	{
		//printf("%s \n", line.c_str());
		std::stringstream s(line);
		std::string x1, y1, d1;

		std::getline(s, x1, ',');
		x = std::stof(x1);
		//std::cout << "x: " << x << " ";

		std::getline(s, y1, ',');
		y = std::stof(y1);
		//std::cout << "y: " << y << " ";

		std::getline(s, d1, '\n');
		d = std::stof(d1);
		//std::cout << "d: " << d << " ";

		dat.push_back(std::make_shared<ddd::dot>(ddd::dot{ x, y, d }));

		/*std::cout << std::endl;*/

		//std::cout << dat[0]->x << " " << dat[0]->y << " " << dat[0]->d << " " << std::endl;

		/*std::cout << std::endl;
		std::cout << std::endl;*/
	}
}