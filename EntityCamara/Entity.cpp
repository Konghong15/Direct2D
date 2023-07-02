#include <stdarg.h>
#include "Entity.h"

namespace entityCamara
{
	Entity::Entity(unsigned int id)
		: mID(id)
		, mComponentflag(0u),
		mComponents{ 0, }
	{
	}

	Entity::~Entity()
	{
		for (int i = 0; i < static_cast<unsigned int>(eComponentType::Size); ++i)
		{
			delete mComponents[i];
		}
	}

	bool Entity::CheckBitflag(unsigned int count, eComponentType  ...) const
	{
		unsigned long long result = 0ull;

		va_list ap;
		va_start(ap, count);
		for (size_t i = 0; i < count; ++i)
		{
			eComponentType componentType = va_arg(ap, eComponentType);
			result |= 1ull << static_cast<unsigned int>(componentType);
		}
		va_end(ap);

		return result == (result & mComponentflag);

	}
}