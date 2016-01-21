//
// Created by Andrei on 21.01.2016.
//

#ifndef SFECS_ENTITY_HPP
#define SFECS_ENTITY_HPP

#include <memory>
#include <vector>
#include "SFECS/Component.hpp"

namespace sfecs
{
    class Entity {

    private:

        bool alive{true};
        std::vector<std::unique_ptr<Component>> components;

    public:

        void update() {
            for (auto& c : components) { c->update(); }
        }

        void draw() {
            for (auto& c : components) { c->draw(); }
        }

        bool isAlive() const { return alive; }
        void destroy() { alive = false; }


        template <typename T, typename... TArgs>
        T& addComponent(TArgs&&... mArgs) {
            T* c(new T(std::forward<TArgs>(mArgs)...));

            c->entity = this;

            std::unique_ptr<Component> uPtr{c};

            components.emplace_back(uPtr);


            return *c;
        };

    };
}


#endif //SFECS_ENTITY_HPP
