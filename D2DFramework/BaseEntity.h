#pragma once

#include <unordered_set>

namespace d2dFramework
{
	class BaseEntity
	{
	public:
		BaseEntity(unsigned int id);
		~BaseEntity();

		inline unsigned int GetId();

	private:
		static std::unordered_set<unsigned int> mIDSet;

		unsigned int mId;
		// 로깅 남길 거면 개체 생성 삭제 시간 정도?
	};

	unsigned int BaseEntity::GetId()
	{
		return mId;
	}
}