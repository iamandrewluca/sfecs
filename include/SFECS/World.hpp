//
// Created by Andrei on 21.01.2016.
//

#ifndef SFECS_WORLD_HPP
#define SFECS_WORLD_HPP

namespace sfecs
{
    class World {

        float width;
        float height;

    public:
        World();
        ~World();
        void run();


        float getWidth() const {
            return width;
        }

        void setWidth(float width) {
            World::width = width;
        }

        float getHeight() const {
            return height;
        }

        void setHeight(float height) {
            World::height = height;
        }
    };
}

#endif //SFECS_WORLD_HPP
