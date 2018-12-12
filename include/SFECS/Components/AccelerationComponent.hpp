//
// Created by Andrei Luca on 6/1/16.
//

#ifndef SFECS_ACCELERATIONCOMPONENT_HPP
#define SFECS_ACCELERATIONCOMPONENT_HPP

#include <SFECS/Component.hpp>

class AccelerationComponent : public sfecs::Component
{
	
public:
    float accelX;
    float accelY;
    AccelerationComponent(float accelX, float accelY): accelX(accelX), accelY(accelY) {}
};


#endif //SFECS_ACCELERATIONCOMPONENT_HPP
