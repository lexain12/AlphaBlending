#include "mainUtils.h"

int main()
{

    Img front = {};
    imgCtor ("img/AskhatCat.bmp", &front);

    Img back = {};
    imgCtor ("img/Table.bmp", &back);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Blend");

    sf::Clock clock;
	while (window.isOpen())
	{
        window.clear();
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			switch (Event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

			}
		}
        AlphaBlend(&front, &back, 400, 300);

		window.display();
        window.clear();

        sf::Time elapsed = clock.restart();
        printf ("FPS %f\n", 1/elapsed.asSeconds());

	}

	return 0;
}
