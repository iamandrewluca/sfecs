//
// Created by Andrei Luca on 6/1/16.
//

#ifndef SFECS_SCRIPTCOMPONENT_HPP
#define SFECS_SCRIPTCOMPONENT_HPP

#include <SFECS/Components.hpp>
#include <SFECS/Entity.hpp>

class ScriptComponent : public sfecs::Component
{
public:
    ScriptComponent(sfecs::Entity& entity): entity(entity) {}

    void update() {
        PositionComponent& pos = *this->entity.getComponent<PositionComponent>();
        MovementComponent& mov = *this->entity.getComponent<MovementComponent>();

        if (pos.posX < 50 || pos.posX > 750) { mov.velocityX *= -1; }
        if (pos.posY < 50 || pos.posY > 550) {
            mov.velocityY *= -1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            if (mov.velocityX > -20) mov.velocityX -= 0.5;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            if (mov.velocityY > -20) mov.velocityY -= 0.5;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            if (mov.velocityY < 20) mov.velocityY += 0.5;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            if (mov.velocityX < 20) mov.velocityX += 0.5;
        }
    }
private:
    sfecs::Entity& entity;
};


#endif //SFECS_SCRIPTCOMPONENT_HPP
