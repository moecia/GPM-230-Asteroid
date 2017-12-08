#include <Windows.h>

#include "GameState.h"
#include "MainMenu.h"
#include "Asteriod.h"
CurrentState _currentState; 
bool quitGame = false;
int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 768), "Asteriod");

	_currentState.SetWindow(&window);
	_currentState.SetState(new MainMenu());

	sf::Texture texture;
	if (!texture.loadFromFile("Images/Background.png"))
	{
		return -1;
	}
	sf::Sprite background(texture);


	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.draw(background);
		//window.clear(sf::Color::Black);

		_currentState.Update();
		_currentState.Render();

		window.display();

		if (quitGame)
		{
			window.close();
		}

		Sleep(5);
	}

	return 0;
}
