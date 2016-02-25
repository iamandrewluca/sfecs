//
// Created by Andrei Luca on 17.01.2016.
//

int main()
{
    sfecs::World* world = new sfecs::World();

    sfecs::Scene* mainScene = new sfecs::Scene();

    world->addScene(mainScene);
    world->setCurrentScene(mainScene);

    sfecs::Entity* player = new sfecs::Entity();

    sfecs::SpriteComponent* spriteComponent = new sfecs::SpriteComponent();
    sfecs::TransformComponent* transformComponent = new sfecs::TransformComponent();

    player->addComponent(transformComponent);
    player->addComponent(spriteComponent);

    mainScene->addEntity(player);

    world->run();


    return 0;
}