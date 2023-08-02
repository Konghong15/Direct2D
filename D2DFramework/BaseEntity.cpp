#include "BaseEntity.h"

#include <cassert>

namespace d2dFramework
{
	BaseEntity::BaseEntity(unsigned int id)
		: mId(id)
	{
		assert(mIDSet.find(id) == mIDSet.end());
	}

	BaseEntity::~BaseEntity()
	{
		assert(mIDSet.find(mId) != mIDSet.end());
		mIDSet.erase(mIDSet.find(mId));
	}
}