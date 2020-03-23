#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include "Player.h"
#include "Platform.h"
#include "Noise.h"

static const float View_Size = 500;


void resizeView(sf::RenderWindow& window, sf::View& view) {
	float ar = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(View_Size * ar, View_Size);
}


int main()
{
	sf::RenderWindow Window(sf::VideoMode(500, 500), "SFML GAME Window");
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(View_Size, View_Size));
	//noiseTest
	std::vector<Platform> platforms;
	const int height = 100;
	const int width = 400;


	float fnoiseSeed1D[width];
	float fperlinNoise1D[width];
	int octave = 7; // 1 - 7, oddly
	float bias = 1.50f;
	float altitude = 4.0f;
	for (int i = 0; i < width; i++)
		fnoiseSeed1D[i] = (float)rand() / (float)RAND_MAX;

	perlinNoise1D(width, fnoiseSeed1D, octave, fperlinNoise1D, bias);
	int y;
	for (int x = 0; x < width; x++) {
		y = (fperlinNoise1D[x] * float(height) / altitude + float(height) / altitude);
		platforms.push_back(Platform(nullptr, sf::Vector2f(50, 25), sf::Vector2f(x * 50, y * 25)));
		for (int f = height; f >= y; f--) {
			//
		}
	}



	//Textures
	sf::Texture playerTexture;
	playerTexture.loadFromFile("Sprites/robotsprite.png");

	//animation
	Player player(&playerTexture, sf::Vector2u(10, 8), 0.05f, 300.0f, 200.0f);

	//collision
	Collision playerCollision = player.GetCollision();

	//clock
	float deltaTime = 0.0f;
	sf::Clock clock;

	while (Window.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.f)
			deltaTime = 1.0f / 20.0f;
		sf::Event Ev;
		while (Window.pollEvent(Ev)) {
			switch (Ev.type) {
			case sf::Event::Closed:
				Window.close();
				break;
			case sf::Event::Resized:
				resizeView(Window, view);
				break;
			}
		}
		player.Update(deltaTime);
		//checking for collision
		sf::Vector2f direction;
		for (Platform& platform : platforms)//equal to for(int i = 0;i<platforms.getsize;i++){ Platforms& platform = platforms[i] so basiclally applying referencing
			if (platform.GetCollision().CheckCollision(playerCollision, direction, 1.0f))
				player.oncollision(direction);


		view.setCenter(player.getPosition());

		Window.setView(view);//always update the view at the end of frame draw




		Window.clear(sf::Color::Blue);
		//draw here


		


		player.draw(Window);
		for (Platform& platform : platforms)
			platform.Draw(Window);


		//draw above
		Window.display();
	}

}