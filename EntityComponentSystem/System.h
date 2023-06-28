#pragma once

#include <vector>

namespace gameProcessor
{
	class RenderManager;
}

namespace entityComponentSystem
{
	class Entity;

	class System
	{
	public:
		void Update(std::vector<Entity*> entities, float deltaTime);
		void Render(std::vector<Entity*> entities, gameProcessor::RenderManager* renderManager);
	};
}