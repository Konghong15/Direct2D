#pragma once

#include "Matrix3X3.h"
#include "hRectangle.h"

namespace gameProcessor
{
	class Camara
	{
	public:
		Camara(unsigned int width, unsigned int height);
		~Camara() = default;

		inline void AddTraslate(float x, float y);
		inline void AddScale(float x, float y);
		inline void AddRotateInRadian(float rotateInRadian);

		inline void SetTraslate(float x, float y);
		inline void SetScale(float x, float y);
		inline void SetRotateInRadian(float rotateInRadian);

		inline const Matrix3X3& GetScreenTrasform() const;
		inline const Matrix3X3& GetTrasform() const;
		inline hRectangle GetLocalRectangle() const;

	private:
		const hRectangle mLocalRectangle;
		const Matrix3X3 mScreenTransform;

		Vector2 mScale;
		float mRotateInRadian;
		Vector2 mTranslate;
		gameProcessor::Matrix3X3 mTransform;
	};

	void Camara::AddTraslate(float x, float y)
	{
		mTranslate.Move(x, y);
		mTransform = Matrix3X3::ComineMatrix(3, Matrix3X3::GetScale(mScale), Matrix3X3::GetRotate(mRotateInRadian), Matrix3X3::GetTranslate(mTranslate));
	}

	void Camara::AddScale(float x, float y)
	{
		mScale.Move(x, y);
	}

	void Camara::AddRotateInRadian(float rotateInRadian)
	{
		mRotateInRadian += rotateInRadian;
	}

	void Camara::SetTraslate(float x, float y)
	{
		mTranslate.SetXY(x, y);

		mTransform = Matrix3X3::ComineMatrix(3, Matrix3X3::GetScale(mScale), Matrix3X3::GetRotate(mRotateInRadian), Matrix3X3::GetTranslate(mTranslate));
	}

	void Camara::SetScale(float x, float y)
	{
		mScale.SetXY(x, y);

	}

	void Camara::SetRotateInRadian(float rotateInRadian)
	{
		mRotateInRadian = rotateInRadian;
	}

	const gameProcessor::Matrix3X3& Camara::GetScreenTrasform() const
	{
		return mScreenTransform;
	}

	const gameProcessor::Matrix3X3& Camara::GetTrasform() const
	{
		return mTransform;
	}

	inline gameProcessor::hRectangle Camara::GetLocalRectangle() const
	{
		return mLocalRectangle;
	}
}