#include "MathHelper.h"

#define PI_F (3.141592f)

namespace d2dFramework
{
	float MathHelper::RadianToDegree(float radian)
	{
		return radian * 180.f / PI_F;
	}

	float MathHelper::DegreeToRadian(float degree)
	{
		return degree * PI_F / 180.f;
	}
}