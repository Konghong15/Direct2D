#pragma once

#include <unordered_set>

namespace d2dFramework
{
	class BaseEntity
	{
	public:
		BaseEntity(unsigned int id);
		~BaseEntity();

		unsigned int GetId() const;

	private:
		static std::unordered_set<unsigned int> mIDSet;

		unsigned int mId;
		// �α� ���� �Ÿ� ��ü ���� ���� �ð� ����?
	};

	unsigned int BaseEntity::GetId() const
	{
		return mId;
	}
}