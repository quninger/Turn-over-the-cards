#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"

int main(int argc, char const *argv[])
{
	Game Mine;
	while (Mine.window.isOpen())
	{
		Mine.Run();
	}

}
