#pragma once

#include <cassert>

#include "Vector2.h"
#include "Component.h"

namespace d2dFramework
{
	class GameObject;

	class Transform : public Component
	{
	public:
		Transform(GameObject* owner)
			: Component(owner)
			, mScale(1.f, 1.f)
			, mRotateInRadian(0.f)
			, mTranslate(0.f, 0.f)
		{
		}
		virtual ~Transform() = default;

		inline void SetScale(const Vector2& scale);
		inline void SetRotate(float rotateInRadian);
		inline void SetTranslate(const Vector2& translate);

		inline void AddScale(const Vector2& scale);
		inline void AddRotate(float rotateInRadian);
		inline void AddTranslate(const Vector2& translate);

		inline const Vector2& GetScale(void) const;
		inline float GetRotate(void) const;
		inline const Vector2& GetTranslate(void) const;

		inline const D2D1::Matrix3x2F GetTransform() const;
		inline const D2D1::Matrix3x2F GetInverseTransform() const;

	private:
		Vector2 mScale;
		float mRotateInRadian;
		Vector2 mTranslate;
	};

	void Transform::SetScale(const Vector2& scale)
	{
		mScale = scale;
	}
	void Transform::SetRotate(float rotateInRadian)
	{
		mRotateInRadian = rotateInRadian;
	}
	void Transform::SetTranslate(const Vector2& translate)
	{
		mTranslate = translate;
	}

	void Transform::AddScale(const Vector2& scale)
	{
		mScale += scale;
	}
	void Transform::AddRotate(float rotateInRadian)
	{
		mRotateInRadian += rotateInRadian;
	}
	void Transform::AddTranslate(const Vector2& translate)
	{
		mTranslate += translate;
	}

	const Vector2& Transform::GetScale(void) const
	{
		return mScale;
	}
	float Transform::GetRotate(void) const
	{
		return mRotateInRadian;
	}
	const Vector2& Transform::GetTranslate(void) const
	{
		return mTranslate;
	}

	const D2D1::Matrix3x2F Transform::GetTransform() const
	{
		return D2D1::Matrix3x2F::Scale({ mScale.GetX(), mScale.GetY() }) * D2D1::Matrix3x2F::Rotation(mRotateInRadian) * D2D1::Matrix3x2F::Translation({ mTranslate.GetX(), mTranslate.GetY() });
	}
	const D2D1::Matrix3x2F Transform::GetInverseTransform() const
	{
		D2D1::Matrix3x2F matrix = GetTransform();
		assert(D2D1InvertMatrix(&matrix));

		return matrix;
	}
}