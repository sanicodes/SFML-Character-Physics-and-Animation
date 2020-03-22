#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Player.h"
#include "Platform.h"

void resizeView(sf::RenderWindow& window,sf::View view) {
	float ar = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(1000 * ar, 1000);
}
int main()

{
	sf::RenderWindow Window(sf::VideoMode(1000, 500), "Window");
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1000, 500));
	//player
	sf::Texture playerTexture;
	playerTexture.loadFromFile("Sprites/robotsprite.png");
	//animation
	Player player(&playerTexture, sf::Vector2u(10, 8), 0.05f, 100.0f,200.0f);
	//platforms
	std::vector<Platform> platforms;
	platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 400.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 300.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f)));

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
		for (Platform& platform : platforms)//equal to for(int i = 0;i<platforms.getsize;i++){ Platforms& platform = platforms[i] so basiclally applying referencing}

			if (platform.GetCollision().CheckCollision(playerCollision,direction,0.0f))
				player.oncollision(direction);


		view.setCenter(player.getPosition());
		
		Window.setView(view);//always update the view at the end of frame draw
		
		//other statements
		Window.clear(sf::Color::Blue);
		//draw here
		for (Platform& platform : platforms)
			platform.Draw(Window);

		//Window.draw(Background);
		player.draw(Window);
		//draw above
		Window.display();
	}
	
}