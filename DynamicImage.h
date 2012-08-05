#pragma once

#include <vector>

#include "Transform.h"

namespace BlackJack
{

	class DynamicImage
	{
		/********************/
		/* Internal Classes */
		/********************/
	public:
		struct DynamicImageDef
		{
			std::vector< Transform >    m_transforms;
		};
	};

}