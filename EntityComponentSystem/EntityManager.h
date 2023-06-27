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
		// 씬? 씬은 렌더링 컴포넌트가 있을 경우 추가한다?
	};
}