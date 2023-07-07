#pragma once

#include "hRectangle.h"
#include "Matrix3X3.h"
#include "Object.h"

namespace gameProcessor
{
	class InputManager;
	class AnimationInstance;
	class RenderManager;
}

namespace finiteStateMachine
{
	enum class eWeaponState
	{
		Idle,
		Action,
		Back
	};

	class Weapon : public Object
	{
	public:
		Weapon(gameProcessor::AnimationInstance* animationInstance, const gameProcessor::hRectangle& rectangle, float speed, float distance);
		virtual ~Weapon() override;

		virtual void HandleState();
		virtual void Update(float deltaTime) override;
		virtual void Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& compositeTrasform) override;

		void Action(const gameProcessor::Vector2& direction);

		inline eWeaponState GetState() const;

	protected:
		gameProcessor::AnimationInstance* mAnimationInstnace;
		const gameProcessor::Vector2 mInitTraslate;

		gameProcessor::Matrix3X3 mPrevParentMatrix;
		gameProcessor::Vector2 mDirection;
		float mSpeed;
		float mElapsedDistance;
		const float mMaxDistance;


		eWeaponState mWeaponState;
	};

	inline eWeaponState Weapon::GetState() const
	{
		return mWeaponState;
	}
}