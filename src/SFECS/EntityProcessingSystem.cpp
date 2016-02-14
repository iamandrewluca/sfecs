#include "SFECS/EntityProcessingSystem.hpp"

#ifdef _DEBUG
#include <debug_new.h>
#endif

namespace sfecs {
	
	bool EntityProcessingSystem::checkProcessing() {
		return true;
	}

	void EntityProcessingSystem::processEntities(ImmutableBag<Entity*>& bag) {
		for(int i=0; i < bag.getCount(); i++) 
			{processEntity(*bag.get(i));}
	}

}
