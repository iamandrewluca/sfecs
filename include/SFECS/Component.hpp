#ifndef COMPONENT_H
#define COMPONENT_H

namespace sfecs {

		class Component {
			public:
				virtual ~Component() = 0;
			protected:
				Component() {};
		};

}

#endif
