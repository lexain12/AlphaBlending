#include "mainUtils.h"
#include <SFML/Config.hpp>

int main()
{

    Img* front = LoadBitmapFile("Cat.bmp");
    Img* back = LoadBitmapFile("Table.bmp");

	sf::RenderWindow window(sf::VideoMode(Init.width, Init.height), "Blend");

    sf::Clock clock;

    AlphaBlend (front, back, 400, 300);

    saveBmpFile ("CatNew.bmp", back);
    return 0;

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

        sf::Image image;
        image.create(Init.width, Init.height, (sf::Uint8*) back->imgBuff);

        sf::Texture texture;
        texture.loadFromImage(image);
        sf::Sprite sprite(texture);

        window.draw (sprite);
		window.display();
        window.clear();

        sf::Time elapsed = clock.restart();
        printf ("FPS %f\n", 1/elapsed.asSeconds());

	}

	return 0;
}
