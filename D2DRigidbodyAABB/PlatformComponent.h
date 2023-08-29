#pragma once

#include "Component.h"
#include "IUpdateable.h"
#include "Vector2.h"

#include <vector>

namespace d2dRigidbodyAABB
{
	class PlatformComponent
		: public d2dFramework::Component
		, public d2dFramework::IUpdateable
	{
	public:
		PlatformComponent(unsigned int id, d2dFramework::GameObject* owner);
		virtual ~PlatformComponent() = default;

		virtual void Init() override;
		virtual void Update(float deltaTime) override;
		virtual void Release() override;

		virtual inline d2dFramework::GameObject* GetGameObject() const override;
		virtual inline unsigned int GetId() const override;

		inline void SetMovePositions(const std::vector<d2dFramework::Vector2> movePositions);
		inline void SetMoveSpeed(float moveSpeed);
		inline void SetIsMovePaused(bool bIsMovePaused);

		inline const std::vector<d2dFramework::Vector2> GetMovePositions() const;
		inline unsigned int GetCurrentPositionIndex() const;
		inline float GetMoveSpeed() const;
		inline bool GetIsMovePaused() const;

	private:
		std::vector<d2dFramework::Vector2> mMovePositions;
		unsigned int mCurrentPositionIndex;
		float mMoveSpeed;
		float mMoveRatio;
		float mElpasedMoveTime;
		bool mbIsMovePaused;
	};

	d2dFramework::GameObject* PlatformComponent::GetGameObject() const
	{
		return Component::GetGameObject();
	}
	unsigned int PlatformComponent::GetId() const
	{
		return Component::GetId();
	}

	void PlatformComponent::SetMovePositions(const std::vector<d2dFramework::Vector2> movePositions)
	{
		assert(movePositions.size() > 0);
		mMovePositions = movePositions;
	}
	void PlatformComponent::SetMoveSpeed(float moveSpeed)
	{
		assert(moveSpeed > 0.f);
		mMoveSpeed = moveSpeed;
		mMoveRatio = 1 / mMoveSpeed;
	}
	void PlatformComponent::SetIsMovePaused(bool bIsMovePaused)
	{
		mbIsMovePaused = bIsMovePaused;
	}

	const std::vector<d2dFramework::Vector2> PlatformComponent::GetMovePositions() const
	{
		return mMovePositions;
	}
	unsigned int PlatformComponent::GetCurrentPositionIndex() const
	{
		return mCurrentPositionIndex;
	}
	float PlatformComponent::GetMoveSpeed() const
	{
		return mMoveSpeed;
	}
	bool PlatformComponent::GetIsMovePaused() const
	{
		return mbIsMovePaused;
	}
}