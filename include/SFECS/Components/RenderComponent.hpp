//
// Created by Andrei Luca on 6/1/16.
//

#ifndef SFECS_RENDERCOMPONENT_HPP
#define SFECS_RENDERCOMPONENT_HPP

#include <SFECS/Component.hpp>
#include <SFML/Graphics.hpp>

class RenderComponent : public  sfecs::Component
{
public:
    sf::CircleShape sprite;
    RenderComponent()
    {
        sprite = sf::CircleShape(5);
        sprite.setFillColor(sf::Color::Cyan);
//        sf::Texture texture;
//        if (!texture.loadFromFile(image, sf::IntRect(0, 0, 16, 16))) {
//            std::cout << "error";
//        } else {
//            sprite.setTexture(texture, true);
//        }
    }
};


#endif //SFECS_RENDERCOMPONENT_HPP
