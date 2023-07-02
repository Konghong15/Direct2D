#pragma once

#include "Component.h"
#include "hRectangle.h"
#include "TransformComponent.h"

namespace entityCamara
{
	class CamaraComponent : public Component
	{
	public:
		CamaraComponent(unsigned int entityId, const gameProcessor::hRectangle& rectangle, const gameProcessor::Vector2& scale, float rotateInRadian, const gameProcessor::Vector2& translate);
		virtual ~CamaraComponent() = default;
		CamaraComponent(const CamaraComponent& other) = default;
		CamaraComponent& operator=(const CamaraComponent& other) = default;

		void Update();

		inline const gameProcessor::Matrix3X3& GetInverseMatrix() const;

	private:
		gameProcessor::hRectangle mRectangle;
		gameProcessor::Vector2 mScale;
		float mRotateInRadian;
		gameProcessor::Vector2 mTranslate;
		gameProcessor::Matrix3X3 mTransform;
		gameProcessor::Matrix3X3 mInverseTransform;
	};

	const gameProcessor::Matrix3X3& CamaraComponent::GetInverseMatrix() const
	{
		return mInverseTransform;
	}
}