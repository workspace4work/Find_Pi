# include <iostream>
# include <memory>

# include <SFML/graphics.hpp>
# include <SFML/network.hpp>
# include <SFML/window.hpp>
# include <SFML/system.hpp>

# include "Space.h"

int main()
{
	std::unique_ptr<Space> window = std::make_unique<Space>();

	while (window->running())
	{
		// handle events
		window->update();

		window->render();
	}


	return 0;
}