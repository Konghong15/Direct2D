#pragma once

#include "Vector2.h"
#include "Matrix3X3.h"

namespace gameProcessor
{
	struct TransformInfo
	{
		TransformInfo(Vector2 scale, float rotateInRadian, Vector2 translate)
			: Scale(scale)
			, RotateInRadian(rotateInRadian)
			, Translate(translate)
			, LocalTransform(Matrix3X3::ComineMatrix(3, Matrix3X3::GetScale(scale), Matrix3X3::GetRotate(RotateInRadian), Matrix3X3::GetTranslate(translate)))
			, WorldTransform(LocalTransform)
		{
		}

		Vector2 Scale;
		float RotateInRadian;
		Vector2 Translate;
		Matrix3X3 LocalTransform;
		Matrix3X3 WorldTransform;
	};
}