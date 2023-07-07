#pragma once

#include "Weapon.h"

namespace finiteStateMachine
{
	class Toungu : public Weapon
	{
	public:
		Toungu(gameProcessor::AnimationInstance* animationInstance, const gameProcessor::hRectangle& rectangle, float speed, float distance);
		virtual ~Toungu() override = default;

		virtual void Update(float deltaTime) override;

	protected:
		inline virtual gameProcessor::Matrix3X3 combineMatrix() override;
	};

	gameProcessor::Matrix3X3 Toungu::combineMatrix()
	{
		return gameProcessor::Matrix3X3::ComineMatrix(3,
			gameProcessor::Matrix3X3::GetTranslate(mTranslate),
			gameProcessor::Matrix3X3::GetScale(mScale),
			gameProcessor::Matrix3X3::GetRotate(mDirection.GetX(), mDirection.GetY()));
	}
}