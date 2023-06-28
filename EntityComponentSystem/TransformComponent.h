#pragma once

#include "Vector2.h"
#include "Matrix3X3.h"
#include "Component.h"

namespace entityComponentSystem
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent(unsigned int entityId, const gameProcessor::Vector2& scale, float rotateInRadian, const gameProcessor::Vector2& translate);
		virtual ~TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent& operator=(const TransformComponent& other) = default;

		void Update();

		inline void AddScale(const gameProcessor::Vector2& scale);
		inline void AddRotate(float rotateInRadian);
		inline void AddTranslate(const gameProcessor::Vector2& translate);

		inline const gameProcessor::Matrix3X3& GetTransform() const;

	private:
		gameProcessor::Vector2 mScale;
		float mRotateInRadian;
		gameProcessor::Vector2 mTranslate;
		gameProcessor::Matrix3X3 mTransform;
	};

	void TransformComponent::AddScale(const gameProcessor::Vector2& scale)
	{
		mScale += scale;
	}

	void TransformComponent::AddRotate(float rotateInRadian)
	{
		mRotateInRadian += rotateInRadian;
	}

	void TransformComponent::AddTranslate(const gameProcessor::Vector2& translate)
	{
		mTranslate += translate;
	}

	const gameProcessor::Matrix3X3& TransformComponent::GetTransform() const
	{
		return mTransform;
	}
}