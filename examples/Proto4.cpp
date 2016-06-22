//
// Created by Andrei on 17.01.2016.
//

// SFECS
#include <SFECS/Manager.hpp>
#include <SFECS/Components.hpp>
#include <SFECS/Systems.hpp>

int main() {



    sfecs::Manager manager;
    sfecs::SystemManager * sm = manager.getSystemManager();
    MovementSystem& movementsys = (MovementSystem&) sm->setSystem(new MovementSystem());
    RenderSystem& rendersy = (RenderSystem&) sm->setSystem(new RenderSystem());
    ScriptSystem& scriptSystem = (ScriptSystem&) sm->setSystem(new ScriptSystem());
    AccelerationSystem& accelerationSystem = (AccelerationSystem&) sm->setSystem(new AccelerationSystem());
    DestroySystem& destroySystem = (DestroySystem&) sm->setSystem(new DestroySystem());
    GravitySystem& gravitySystem = (GravitySystem&) sm->setSystem(new GravitySystem());

    sfecs::EntityManager * em = manager.getEntityManager();

    sm->initializeAll();


    srand(time(nullptr));

    sfecs::Entity& player = em->create();

    int angle = rand() % 360;
    float rad = (float) (angle * 3.14 / 180);
    float x = (float) (sin(rad) * (rand() % 2));
    float y = (float) (cos(rad) * (rand() % 2));

    player.addComponent(new PositionComponent(400, 300));
    player.addComponent(new MovementComponent(3, 2));
    player.addComponent(new RenderComponent());
    player.addComponent(new ScriptComponent(player));
    player.addComponent(new AccelerationComponent(0.99, 0.99));
    player.addComponent(new GravityComponent(1));
    player.refresh();

    sf::RenderWindow window(sf::VideoMode(800, 600), "Position, Movement, Render, Script, Acceleration, Graity");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                std::cout << "Exit";
                window.close();
            }
        }

        manager.loopStart();
        manager.setDelta(0.1);

        gravitySystem.process();
        movementsys.process();
        accelerationSystem.process();

        scriptSystem.process();

        rendersy.process();
        window.clear();

        window.draw(player.getComponent<RenderComponent>()->sprite);

        window.display();

//        destroySystem.process();
    }

    return 0;
}