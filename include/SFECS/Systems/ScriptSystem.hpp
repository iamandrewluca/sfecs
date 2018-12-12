//
// Created by Andrei Luca on 6/1/16.
//

#ifndef SFECS_SCRIPTSYSTEM_HPP
#define SFECS_SCRIPTSYSTEM_HPP

#include <SFECS/EntityProcessingSystem.hpp>
#include <SFECS/ComponentMapper.hpp>
#include <SFECS/Components.hpp>

class ScriptSystem : public sfecs::EntityProcessingSystem
{
    sfecs::ComponentMapper<ScriptComponent> scriptMapper;

public:

    ScriptSystem() {
        setComponentTypes<ScriptComponent>();
    }

    virtual void initialize() {
        scriptMapper.init(*world);
    }

    virtual void processEntity(sfecs::Entity &e) {
        ScriptComponent* script = scriptMapper.get(e);
        script->update();
    }
};


#endif //SFECS_SCRIPTSYSTEM_HPP
