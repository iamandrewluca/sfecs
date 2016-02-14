//
// Created by Andrei on 17.01.2016.
//

#include <SFECS/Component.hpp>
#include <SFECS/EntityProcessingSystem.hpp>
#include <SFECS/Manager.hpp>
#include <SFECS/ComponentMapper.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>

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

class RenderComponent : public  sfecs::Component
{
public:
    sf::CircleShape shape{5};

    RenderComponent()
    {
        shape.setFillColor(sf::Color(rand()%255, rand()%255, rand()%255));
    }
};

class ScriptComponent : public sfecs::Component
{
public:
    ScriptComponent(sfecs::Entity& entity): entity(entity) {}

    void update() {
        PositionComponent& pos = *this->entity.getComponent<PositionComponent>();
        MovementComponent& mov = *this->entity.getComponent<MovementComponent>();

        if (pos.posX < 50 || pos.posX > 750) { mov.velocityX *= -1; }
        if (pos.posY < 50 || pos.posY > 550) { mov.velocityY *= -1; }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            mov.velocityX = -1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            mov.velocityY = -1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            mov.velocityY = 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            mov.velocityX = 1;
        }
    }
private:
    sfecs::Entity& entity;
};

class AccelerationComponent : public sfecs::Component
{
public:
    float accelX;
    float accelY;
    AccelerationComponent(float accelX, float accelY): accelX(accelX), accelY(accelY) {}
};

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

class MovementSystem : public sfecs::EntityProcessingSystem
{
private:
    sfecs::ComponentMapper<MovementComponent> velocityMapper;
    sfecs::ComponentMapper<PositionComponent> positionMapper;

public:
    MovementSystem() {
        setComponentTypes<MovementComponent,PositionComponent>();
    };

    virtual void initialize() {
        velocityMapper.init(*world);
        positionMapper.init(*world);
    };

    virtual void processEntity(sfecs::Entity &e) {
        positionMapper.get(e)->posX += velocityMapper.get(e)->velocityX * world->getDelta();
        positionMapper.get(e)->posY += velocityMapper.get(e)->velocityY * world->getDelta();
    };

};

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

        rendCmp->shape.setPosition(posCmp->posX, posCmp->posY);
    };
};

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

class DestroySystem : public sfecs::EntityProcessingSystem
{
    sfecs::ComponentMapper<MovementComponent> moveMapper;

public:

    DestroySystem() {
        setComponentTypes<MovementComponent>();
    }

    virtual void initialize() {
        moveMapper.init(*world);
    }

    virtual void processEntity(sfecs::Entity &e) {
        MovementComponent* move = moveMapper.get(e);

//        if (move->velocityX < 1 || move->velocityY < 1) e.remove();
    }
};

int main() {

    sfecs::Manager world;
    sfecs::SystemManager * sm = world.getSystemManager();
    MovementSystem& movementsys = (MovementSystem&) sm->setSystem(new MovementSystem());
    RenderSystem& rendersy = (RenderSystem&) sm->setSystem(new RenderSystem());
    ScriptSystem& scriptSystem = (ScriptSystem&) sm->setSystem(new ScriptSystem());
    AccelerationSystem& accelerationSystem = (AccelerationSystem&) sm->setSystem(new AccelerationSystem());
    DestroySystem& destroySystem = (DestroySystem&) sm->setSystem(new DestroySystem());
    sfecs::EntityManager * em = world.getEntityManager();

    sm->initializeAll();


    srand(time(nullptr));


    sfecs::Entity& player = em->create();

    int angle = rand() % 360;
    float rad = angle * 3.14/180;
    float x = sin(rad) * (rand() % 2);
    float y = cos(rad) * (rand() % 2);

    player.addComponent(new MovementComponent(0, 0));
    player.addComponent(new PositionComponent(400,300));
    player.addComponent(new RenderComponent());
    player.addComponent(new ScriptComponent(player));
//    player.addComponent(new AccelerationComponent(0.9999, 0.9999));
    player.refresh();


    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    sf::RenderWindow window1(sf::VideoMode(800, 600), "SFML worsks!");

    while (window.isOpen() && window1.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                std::cout << "Exit";
                window.close();
            }
        }

        world.loopStart();
        world.setDelta(0.1);

        movementsys.process();
        accelerationSystem.process();

        scriptSystem.process();
//        destroySystem.process();

        rendersy.process();
        window.clear();
        window.draw(player.getComponent<RenderComponent>()->shape);

        window.display();

        window1.display();
    }

    return 0;
}