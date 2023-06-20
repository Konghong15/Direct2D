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
}