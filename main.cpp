#include "mainUtils.h"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <ctime>

int main()
{
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
        Img front = {};
        imgCtor ("img/AskhatCat.bmp", &front);

        Img back = {};
        imgCtor ("img/Table.bmp", &back);

        clock.restart();
        AlphaBlend(&front, &back, 300, 250);
        sf::Time elapsed = clock.restart();
        printf ("FPS %f\n", 1/elapsed.asSeconds());

        sf::Texture texture;
        texture.loadFromImage(back.image);
        sf::Sprite sprite(texture);
        window.draw(sprite);
		window.display();
        window.clear();


	}

	return 0;
}
