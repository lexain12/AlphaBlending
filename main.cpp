#include "mainUtils.h"

int main()
{

    Img* front = LoadBitmapFile("cat.bmp");
    Img* back = LoadBitmapFile("Table.bmp");

	sf::RenderWindow window(sf::VideoMode(Init.width, Init.height), "Blend");

    sf::Image image;
    image.create(Init.width, Init.height, sf::Color::Red);

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

        AlphaBlend (front, back);

        sf::Texture texture;
        texture.loadFromImage (image);
        sf::Sprite sprite(texture);

        window.draw (sprite);
		window.display();
        window.clear();

        sf::Time elapsed = clock.restart();
        printf ("FPS %f\n", 1/elapsed.asSeconds());

	}

	return 0;
}
