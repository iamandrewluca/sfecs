//
// Created by Andrei Luca on 6/1/16.
//

#ifndef SFECS_MOVEMENTCOMPONENT_HPP
#define SFECS_MOVEMENTCOMPONENT_HPP

#include <SFECS/Component.hpp>

class MovementComponent : public sfecs::Component
{
public:
    float velocityX;
    float velocityY;

    MovementComponent(float velocityX, float velocityY)
    {
        this->velocityX = velocityX;
        this->velocityY = velocityY;
    };
};


#endif //SFECS_MOVEMENTCOMPONENT_HPP
