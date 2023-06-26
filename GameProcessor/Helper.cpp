#include "Helper.h"

#define FLOAT_PI (3.141592f)

namespace gameProcessor
{
	float Helper::RadianToDegree(float radian)
	{
		return radian * 180 / FLOAT_PI;
	}

	float Helper::DegreeToRadian(float degree)
	{
		return degree * FLOAT_PI / 180;
	}

	D2D1_COLOR_F Helper::GetRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		return { static_cast<float>(r) / 255.f, static_cast<float>(g) / 255.f, static_cast<float>(b) / 255.f , static_cast<float>(a) / 255.f };
	}
}