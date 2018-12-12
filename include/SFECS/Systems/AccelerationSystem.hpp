//
// Created by Andrei Luca on 6/1/16.
//

#ifndef SFECS_ACCELERATIONSYSTEM_HPP
#define SFECS_ACCELERATIONSYSTEM_HPP


#include <SFECS/EntityProcessingSystem.hpp>
#include <SFECS/ComponentMapper.hpp>
#include <SFECS/Components.hpp>

class AccelerationSystem : public sfecs::EntityProcessingSystem
{
private:
    sfecs::ComponentMapper<AccelerationComponent> accelMapper;
    sfecs::ComponentMapper<MovementComponent> moveMapper;


public:

    AccelerationSystem() {
        setComponentTypes<AccelerationComponent>();
        setComponentTypes<MovementComponent>();
    }

    virtual void initialize() {
        accelMapper.init(*world);
        moveMapper.init(*world);
    }

    virtual void processEntity(sfecs::Entity &e) {
        AccelerationComponent* accel = e.getComponent<AccelerationComponent>();
        MovementComponent* mov = e.getComponent<MovementComponent>();

        mov->velocityX *= accel->accelX;
        mov->velocityY *= accel->accelY;
    };
};


#endif //SFECS_ACCELERATIONSYSTEM_HPP
