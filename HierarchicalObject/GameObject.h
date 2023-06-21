#pragma once

#include <vector>

#include "Matrix3X3.h"
#include "Vector2.h"
#include "hRectangle.h"

namespace gameProcessor
{
	class RenderManager;
}

namespace hierarchicalObject
{
	class GameObject
	{
	public:
		GameObject(const gameProcessor::hRectangle rectangle, float radian, float rotateWeight, GameObject* parant = nullptr);
		~GameObject() = default;

		void Update(float deltaTime);
		void Render(gameProcessor::RenderManager* renderManager);

	private:
		gameProcessor::hRectangle mRectangle; // 로컬 정점
		gameProcessor::Matrix3X3 mScale;
		gameProcessor::Matrix3X3 mRotate;
		gameProcessor::Matrix3X3 mTranslate;
		gameProcessor::Matrix3X3 mTransform;

		std::vector<GameObject*> mChildren;
		GameObject* mParant;
		float mRadian;
		float mRotateWeight;
	};
}