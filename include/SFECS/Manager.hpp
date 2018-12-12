#ifndef MANAGER_H
#define MANAGER_H


#include "SFECS/ImmutableBag.hpp"
#include "SFECS/TagManager.hpp"
#include "SFECS/GroupManager.hpp"
#include <SFECS/SystemManager.hpp>
#include <SFECS/EntityManager.hpp>
#include <SFECS/Entity.hpp>

namespace sfecs {

	class Manager {
		public:
			Manager();
			~Manager();
			SystemManager * getSystemManager();
			EntityManager * getEntityManager();
			TagManager *   getTagManager();
			GroupManager * getGroupManager();
			float getDelta();
			void setDelta(float delta);
			void deleteEntity(Entity& e);
			void refreshEntity(Entity& e);
			Entity& createEntity();
			Entity& getEntity(int entityId);
			void loopStart();



		private:
			SystemManager * systemManager;
			EntityManager * entityManager;
			TagManager * tagManager;
			GroupManager * groupManager;
			float delta;
			Bag<Entity*> refreshed;
			Bag<Entity*> deleted;



	};
};
#endif // $(Guard token)
