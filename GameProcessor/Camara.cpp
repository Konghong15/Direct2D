#include "Camara.h"

namespace gameProcessor
{
	Camara::Camara(unsigned int width, unsigned int height)
		: mLocalRectangle(-static_cast<int>(width) / 2, -static_cast<int>(height) / 2, width / 2, height / 2)
		, mScreenTransform(gameProcessor::Matrix3X3::GetScale(1, -1)* gameProcessor::Matrix3X3::GetTranslate(mLocalRectangle.GetWidth() / 2, mLocalRectangle.GetHeight() / 2))
		, mScale(1, 1)
		, mRotateInRadian(0)
		, mTranslate(0, 0)
	{
		mTransform = Matrix3X3::ComineMatrix(3, Matrix3X3::GetScale(mScale), Matrix3X3::GetRotate(mRotateInRadian), Matrix3X3::GetTranslate(mTranslate));
	}
}