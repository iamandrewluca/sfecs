//
// Created by Andrei on 21.01.2016.
//

#include <SFECS/World.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace sfecs
{
	World::World() {
		std::cout << "World constructed" << std::endl;
	}

	World::~World() {
		std::cout << "World destructed" << std::endl;
	}

	void World::run() {
		sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	    sf::CircleShape shape(100.f);
	    shape.setFillColor(sf::Color::Green);

	    while (window.isOpen())
	    {
	        sf::Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }

	        window.clear();
	        window.draw(shape);
	        window.display();
	    }
	}
}