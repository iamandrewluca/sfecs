//
// Created by Andrei Luca on 6/1/16.
//

#ifndef SFECS_RENDERSYSTEM_HPP
#define SFECS_RENDERSYSTEM_HPP

#include <SFECS/EntityProcessingSystem.hpp>
#include <SFECS/ComponentMapper.hpp>
#include <SFECS/Components.hpp>

class RenderSystem : public sfecs::EntityProcessingSystem
{
    sfecs::ComponentMapper<PositionComponent> positionMapper;
    sfecs::ComponentMapper<RenderComponent> renderMapper;

public:

    RenderSystem() {
        setComponentTypes<PositionComponent, RenderComponent>();
    }

    virtual void initialize() {
        positionMapper.init(*world);
        renderMapper.init(*world);
    }

    virtual void processEntity(sfecs::Entity &e) {

        PositionComponent* posCmp = positionMapper.get(e);
        RenderComponent* rendCmp = renderMapper.get(e);

        rendCmp->sprite.setPosition(posCmp->posX, posCmp->posY);
    };
};


#endif //SFECS_RENDERSYSTEM_HPP
