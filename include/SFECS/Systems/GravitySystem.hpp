//
// Created by Andrei Luca on 6/1/16.
//

#ifndef SFECS_GRAVITYSYSTEM_HPP
#define SFECS_GRAVITYSYSTEM_HPP

#include <SFECS/EntityProcessingSystem.hpp>
#include <SFECS/ComponentMapper.hpp>
#include <SFECS/Components.hpp>

class GravitySystem : public sfecs::EntityProcessingSystem
{
private:
    sfecs::ComponentMapper<MovementComponent> moveMapper;
    sfecs::ComponentMapper<GravityComponent> gravMapper;


public:

    GravitySystem() {
        setComponentTypes<MovementComponent>();
        setComponentTypes<GravityComponent>();
    }

    virtual void initialize() {
        moveMapper.init(*world);
        gravMapper.init(*world);
    }

    virtual void processEntity(sfecs::Entity &e) {
        MovementComponent* move = e.getComponent<MovementComponent>();
        GravityComponent* grav = e.getComponent<GravityComponent>();

        if (move->velocityY > 0.5) {
            move->velocityY += grav->gravity;
        }
    };
};


#endif //SFECS_GRAVITYSYSTEM_HPP
