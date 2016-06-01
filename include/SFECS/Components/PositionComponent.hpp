//
// Created by Andrei Luca on 6/1/16.
//

#ifndef SFECS_POSITIONCOMPONENT_HPP
#define SFECS_POSITIONCOMPONENT_HPP

#include <SFECS/Component.hpp>

class PositionComponent : public sfecs::Component
{
public:
    float posX;
    float posY;
    PositionComponent(float posX, float posY)
    {
        this->posX = posX;
        this->posY = posY;
    };
};


#endif //SFECS_POSITIONCOMPONENT_HPP
