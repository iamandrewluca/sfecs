#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <typeinfo>
#include <unordered_map>
#include "SFECS/ImmutableBag.hpp"
#include <iostream>
namespace sfecs {

	class EntitySystem;
	class Entity;
	class Manager;

	class SystemManager {
		public:
			SystemManager(Manager &world);
			~SystemManager();
			void initializeAll();
			Bag<EntitySystem*> & getSystems();
			EntitySystem& setSystem(EntitySystem * stm);

			template<typename eSystem>
			EntitySystem& getSystem() {
				return *(eSystem*)(systems[typeid(eSystem).hash_code()]);
			}

		private:
			Manager * world;
			std::unordered_map<size_t, EntitySystem*> systems;
			Bag<EntitySystem*> bagged;
	};
}
#endif // $(Guard token)
