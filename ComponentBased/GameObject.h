#pragma once

#include <vector>
#include <string>

namespace componentBased
{
	class Component;
	class IRenderable;

	class GameObject
	{
	public:
		GameObject(const std::string name);
		~GameObject();

		void AddComponent(Component* component);
		void Update();

	private:
		enum { RESERVE_SIZE = 128 };

		std::string mName;
		std::vector<Component*> mComponents;
	};
}