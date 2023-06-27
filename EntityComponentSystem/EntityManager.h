#pragma once

#include <vector>

namespace entityComponentSystem
{
	class EntityManager
	{
	public:

		void Add();
		void Remove();

		// void SetScene(Scene)

	private:
		std::vector<Entity*> mEntities;
		// ��? ���� ������ ������Ʈ�� ���� ��� �߰��Ѵ�?
	};
}