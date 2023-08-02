#pragma once

#include "hRectangle.h"
#include "InputManager.h"

// 추상화 수준이 끝단 있는 거
// 기능 만들기 -> 클래스화 하기 -> 추상화 레벨 높이기

namespace camara
{
	class GameObject;

	class Camara
	{
	public:
		Camara(unsigned int width, unsigned int height, float speed, GameObject* ownerObjectOrNull = nullptr);
		~Camara() = default;

		inline const gameProcessor::Matrix3X3& GetScreenTrasform() const;
		inline const gameProcessor::Matrix3X3& GetCamaraTrasform() const;
		inline const gameProcessor::hRectangle& GetClippingRectangle() const;
		inline gameProcessor::hRectangle GetRectangle() const;

		inline void SetOwnerObject(GameObject* ownerObjectOrNull);

	private:
		const gameProcessor::hRectangle mRectangle;
		const gameProcessor::Matrix3X3 mScreenTransform;

		gameProcessor::Vector2 mTranslate;
		gameProcessor::Vector2 mXaxis;
		float mScale;
		gameProcessor::Matrix3x2F mCamaraTransform;

		float mSpeed;
		GameObject* mOwnerObjectOrNull;
	};

	const gameProcessor::Matrix3X3& Camara::GetScreenTrasform() const
	{
		return mScreenTransform;
	}

	const gameProcessor::Matrix3X3& Camara::GetCamaraTrasform() const
	{
		return mCamaraTransform;
	}

	const gameProcessor::hRectangle& Camara::GetClippingRectangle() const
	{
		return mRectangle * mCamaraTransform;
	}

	void Camara::SetOwnerObject(GameObject* ownerObjectOrNull)
	{
		mOwnerObjectOrNull = ownerObjectOrNull;
	}

	inline gameProcessor::hRectangle Camara::GetRectangle() const
	{
		return mRectangle;
	}
}