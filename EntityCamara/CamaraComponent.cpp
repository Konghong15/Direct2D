#include "CamaraComponent.h"

namespace entityCamara
{
	CamaraComponent::CamaraComponent(unsigned int entityId, const gameProcessor::hRectangle& rectangle, const gameProcessor::Vector2& scale, float rotateInRadian, const gameProcessor::Vector2& translate)
		: Component(entityId, eComponentType::Camara)
		, mScale(scale)
		, mRotateInRadian(rotateInRadian)
		, mTranslate(translate)
		, mTransform(gameProcessor::Matrix3X3::ComineMatrix(3, gameProcessor::Matrix3X3::GetScale(scale), gameProcessor::Matrix3X3::GetRotate(rotateInRadian), gameProcessor::Matrix3X3::GetTranslate(translate)))
	{
		if (!gameProcessor::Matrix3X3::TryInverse(mTransform, &mInverseTransform))
		{
			mInverseTransform.InitIdentity();
		}
	}

	void CamaraComponent::Update()
	{
		mTransform = gameProcessor::Matrix3X3::ComineMatrix(3, gameProcessor::Matrix3X3::GetScale(mScale), gameProcessor::Matrix3X3::GetRotate(mRotateInRadian), gameProcessor::Matrix3X3::GetTranslate(mTranslate));

		if (!gameProcessor::Matrix3X3::TryInverse(mTransform, &mInverseTransform))
		{
			mInverseTransform.InitIdentity();
		}
	}
}