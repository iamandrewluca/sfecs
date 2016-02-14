#ifndef D_E_PROCESSING_SYSTEM_H
#define D_E_PROCESSING_SYSTEM_H

#include "SFECS/DelayedEntitySystem.hpp"

namespace sfecs{
	class DelayedEntityProcessingSystem : public DelayedEntitySystem
	{
		protected:
		virtual void processEntities(ImmutableBag<Entity*>& bag, float accumulatedDelta);
		virtual void processEntity(Entity& e, float accumulatedDelta) = 0;
	};
}

#endif // $(Guard token)
