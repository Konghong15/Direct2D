#pragma once

#include "Vector2.h"
#include "Component.h"
#include "IFixedUpdateable.h"

namespace d2dFramework
{
	class GameObject;

	class Rigidbody final : public Component, public IFixedUpdateable
	{
	public:
		Rigidbody(unsigned int id, GameObject* owner);
		~Rigidbody() = default;

		void Init() override;
		void FixedUpdate(float deltaTime) override;
		void Release() override;

		inline void SetVelocity(const Vector2& velocity);
		inline void SetAcceleartion(const Vector2& acceleration);
		inline void SetReflection(const Vector2& reflection);
		inline void SetMass(float mass);
		inline void SetCOR(float COR);
		inline void SetGravityScale(float gravityScale);

		inline void AddVelocity(const Vector2& velocity);
		inline void AddAcceleartion(const Vector2& acceleration);
		inline void AddReflection(const Vector2& reflection);

		inline const Vector2& GetVelocity(void);
		inline const Vector2& GetAcceleartion(void);
		inline const Vector2& GetReflection(void);
		inline float GetMass(void);
		inline float GetInvMass(void);
		inline float GetCOR(void);

	private:
		static float mGravityWeight;

		Vector2 mVelocity;
		Vector2 mAcceleartion;
		Vector2 mReflection;

		float mMass;
		float mInvMass;
		float mCOR; // 반발계수 0~1
		float mGravityScale;
	};

	void Rigidbody::SetVelocity(const Vector2& velocity)
	{
		mVelocity = velocity;
	}
	void Rigidbody::SetAcceleartion(const Vector2& acceleration)
	{
		mAcceleartion = acceleration;
	}
	void Rigidbody::SetReflection(const Vector2& reflection)
	{
		mReflection = reflection;
	}
	void Rigidbody::SetMass(float mass)
	{
		mMass = mass;

		if (mass != 0.f)
		{
			mInvMass = 1 / mass;
		}
		else
		{
			mInvMass = 0.f;
		}
	}
	void Rigidbody::SetCOR(float COR)
	{
		mCOR = COR;

		if (COR > 1.f)
		{
			COR = 1.f;
		}
		else if (COR < 0.f)
		{
			COR = 0.f;
		}
	}

	void Rigidbody::SetGravityScale(float gravityScale)
	{
		mGravityScale = gravityScale;
	}

	void Rigidbody::AddVelocity(const Vector2& velocity)
	{
		mVelocity += velocity;
	}
	void Rigidbody::AddAcceleartion(const Vector2& acceleration)
	{
		mAcceleartion += acceleration;
	}
	void Rigidbody::AddReflection(const Vector2& reflection)
	{
		mReflection += reflection;
	}

	const Vector2& Rigidbody::GetVelocity(void)
	{
		return mVelocity;
	}
	const Vector2& Rigidbody::GetAcceleartion(void)
	{
		return mAcceleartion;
	}
	const Vector2& Rigidbody::GetReflection(void)
	{
		return mReflection;
	}
	float Rigidbody::GetMass(void)
	{
		return mMass;
	}
	float Rigidbody::GetInvMass(void)
	{
		return mInvMass;
	}
	float Rigidbody::GetCOR(void)
	{
		return mCOR;
	}
}