//
// Created by Andrei Luca on 6/1/16.
//

#ifndef SFECS_MOVEMENTSYSTEM_HPP
#define SFECS_MOVEMENTSYSTEM_HPP

#include <SFECS/EntityProcessingSystem.hpp>
#include <SFECS/ComponentMapper.hpp>
#include <SFECS/Components.hpp>

class MovementSystem : public sfecs::EntityProcessingSystem
{
private:
    sfecs::ComponentMapper<MovementComponent> velocityMapper;
    sfecs::ComponentMapper<PositionComponent> positionMapper;

public:
    MovementSystem() {
        setComponentTypes<MovementComponent,PositionComponent>();
    };

    virtual void initialize() {
        velocityMapper.init(*world);
        positionMapper.init(*world);
    };

    virtual void processEntity(sfecs::Entity &e) {
        positionMapper.get(e)->posX += velocityMapper.get(e)->velocityX * world->getDelta();
        positionMapper.get(e)->posY += velocityMapper.get(e)->velocityY * world->getDelta();
    };

};


#endif //SFECS_MOVEMENTSYSTEM_HPP
