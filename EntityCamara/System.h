#pragma once

#include <vector>
#include <functional>

namespace gameProcessor
{
	class RenderManager;
}

namespace entityCamara
{
	class Entity;

	class System
	{
	public:
		System() = default;
		~System() = default;

		void RegisterSystemCallback(const std::function<void(std::vector<Entity*>)> systemCallback)
		{
			mSystemCallbacks.push_back(systemCallback);
		}

		void Update(std::vector<Entity*>& entities)
		{
			for (auto iter = mSystemCallbacks.begin(); iter != mSystemCallbacks.end(); ++iter)
			{
				(*iter)(entities);
			}
		}

	private:
		std::vector<std::function<void(std::vector<Entity*>&)>> mSystemCallbacks;
	};
}