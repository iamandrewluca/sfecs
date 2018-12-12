//
// Created by Andrei Luca on 6/1/16.
//

#ifndef SFECS_DESTROYSYSTEM_HPP
#define SFECS_DESTROYSYSTEM_HPP

#include <SFECS/EntityProcessingSystem.hpp>
#include <SFECS/ComponentMapper.hpp>
#include <SFECS/Components.hpp>

class DestroySystem : public sfecs::EntityProcessingSystem
{
    sfecs::ComponentMapper<MovementComponent> moveMapper;

public:

    DestroySystem() {
        setComponentTypes<MovementComponent>();
    }

    virtual void initialize() {
        moveMapper.init(*world);
    }

    virtual void processEntity(sfecs::Entity &e) {
        MovementComponent* move = moveMapper.get(e);

//        if (abs(move->velocityX) < 1 || abs(move->velocityY) < 1) e.remove();
    }
};


#endif //SFECS_DESTROYSYSTEM_HPP
