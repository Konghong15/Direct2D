#include "TransformComponent.h"

namespace entityComponentSystem
{
	TransformComponent::TransformComponent(unsigned int entityId, const gameProcessor::Vector2& scale, float rotateInRadian, const gameProcessor::Vector2& translate)
		: Component(entityId, eComponentType::Transform)
		, mScale(scale)
		, mRotateInRadian(rotateInRadian)
		, mTranslate(translate)
		, mTransform(gameProcessor::Matrix3X3::Identity())
	{
	}

	void TransformComponent::Update()
	{
		mTransform = gameProcessor::Matrix3X3::ComineMatrix(3, gameProcessor::Matrix3X3::GetScale(mScale), gameProcessor::Matrix3X3::GetRotate(mRotateInRadian), gameProcessor::Matrix3X3::GetTranslate(mTranslate));
	}
}