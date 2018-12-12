#include "SFECS/Manager.hpp"
#include "SFECS/Entity.hpp"
#include "SFECS/SystemManager.hpp"
#include "SFECS/GroupManager.hpp"
#include <SFECS/TagManager.hpp>
#include "SFECS/SystemBitManager.hpp"



namespace sfecs {

	Manager::Manager() {
		//TODO add more managers
		this->systemManager = new SystemManager(*this);
		this->entityManager = new EntityManager(*this);
		this->groupManager = new GroupManager();
		this->tagManager = new TagManager();
		delta = 0;
	}

	void Manager::deleteEntity(Entity& e) {
		if(!deleted.contains(&e))
			deleted.add(&e);
	}

	float Manager::getDelta() {
		return this->delta;
	}

	SystemManager*Manager::getSystemManager() {
		return systemManager;
	}

	EntityManager*Manager::getEntityManager() {
		return entityManager;
	}
	
	GroupManager*Manager::getGroupManager(){
		return groupManager;
	}
	
	TagManager*Manager::getTagManager(){
		return tagManager;
	}

	void Manager::loopStart() {
		if(!refreshed.isEmpty()) {
			for(int i=0; i<refreshed.getCount(); i++) {
				//TODO ADD  MANAGERs
				entityManager->refresh(*refreshed.get(i));
			}

			refreshed.clear();

		}

		if(!deleted.isEmpty()) {
			for(int i=0; i<deleted.getCount(); i++) {
				Entity & e = *deleted.get(i);
				groupManager->remove(e);
				tagManager->remove(e);
				entityManager->remove(e);
			}

			deleted.clear();
		}

	}

	Entity&Manager::createEntity() {
		return entityManager->create();
	}

	Entity&Manager::getEntity(int entityId) {
		return entityManager->getEntity(entityId);
	}


	void Manager::refreshEntity(Entity& e) {
		refreshed.add(&e);
	}

	void Manager::setDelta(float delta) {
		this->delta = delta;
	}

	Manager::~Manager() {
		//Entity manager should be deleted first.
		delete entityManager;
		delete systemManager;
		delete groupManager;
		delete tagManager;
		ComponentTypeManager::deleteComponentTypes();
		SystemBitManager::removeBitSets();
	}
}
