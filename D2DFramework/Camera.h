#pragma once

#include "Component.h"
#include "Vector2.h"

#include <cassert>

namespace d2dFramework
{
	class GameObject;

	class Camera : public Component
	{
	public:
		Camera(unsigned int id, GameObject* owner);
		~Camera() = default;

		inline void SetSize(const Vector2& size);
		inline void SetScale(const Vector2& scale);
		inline void SetRotate(float rotateInDegree);
		inline void SetTranslate(const Vector2& translate);

		inline void AddSize(const Vector2& size);
		inline void AddScale(const Vector2& scale);
		inline void AddRotate(float rotateInDegree);
		inline void AddTranslate(const Vector2& translate);

		inline const Vector2& GetSize() const;
		inline const Vector2& GetScale(void) const;
		inline float GetRotate(void) const;
		inline const Vector2& GetTranslate(void) const;

		inline const D2D1::Matrix3x2F GetTransform(void) const;
		inline const D2D1::Matrix3x2F GetInverseTransform(void) const;

	private:
		Vector2 mSize;

		Vector2 mScale;
		float mRotateInDegree;
		Vector2 mTranslate;
	};

	void Camera::SetSize(const Vector2& size)
	{
		mSize = size;
	}
	void Camera::SetScale(const Vector2& scale)
	{
		mScale = scale;
	}
	void Camera::SetRotate(float rotateInDegree)
	{
		mRotateInDegree = rotateInDegree;
	}
	void Camera::SetTranslate(const Vector2& translate)
	{
		mTranslate = translate;
	}

	void Camera::AddSize(const Vector2& size)
	{
		mSize += size;
	}
	void Camera::AddScale(const Vector2& scale)
	{
		mScale += scale;
	}
	void Camera::AddRotate(float rotateInDegree)
	{
		mRotateInDegree += rotateInDegree;
	}
	void Camera::AddTranslate(const Vector2& translate)
	{
		mTranslate += translate;
	}

	const Vector2& Camera::GetSize() const
	{
		return mSize;
	}
	const Vector2& Camera::GetScale(void) const
	{
		return mScale;
	}
	float Camera::GetRotate(void) const
	{
		return mRotateInDegree;
	}
	const Vector2& Camera::GetTranslate(void) const
	{
		return mTranslate;
	}
	const D2D1::Matrix3x2F Camera::GetTransform(void) const
	{
		return D2D1::Matrix3x2F::Scale({ mScale.GetX(), mScale.GetY() }) * D2D1::Matrix3x2F::Rotation(mRotateInDegree) * D2D1::Matrix3x2F::Translation({ mTranslate.GetX(), mTranslate.GetY() });
	}
	const D2D1::Matrix3x2F Camera::GetInverseTransform(void) const
	{
		D2D1::Matrix3x2F matrix = GetTransform();
		assert(D2D1InvertMatrix(&matrix));

		return matrix;
	}
}