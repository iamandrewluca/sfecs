//
// Created by Andrei Luca on 6/1/16.
//

#ifndef SFECS_GRAVITYCOMPONENT_HPP
#define SFECS_GRAVITYCOMPONENT_HPP

#include <SFECS/Component.hpp>

class GravityComponent : public sfecs::Component
{
public:
    float gravity;
    GravityComponent(float gravity): gravity(gravity) {}

};


#endif //SFECS_GRAVITYCOMPONENT_HPP
