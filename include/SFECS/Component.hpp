//
// Created by Andrei on 21.01.2016.
//

#ifndef SFECS_COMPONENT_HPP
#define SFECS_COMPONENT_HPP


namespace sfecs
{
    class Entity;

    class Component {

        Entity* entity{nullptr};

    public:
        virtual void update();
        virtual void draw();
        virtual ~Component();
    };
}


#endif //SFECS_COMPONENT_HPP
