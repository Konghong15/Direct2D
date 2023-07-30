#pragma once

namespace d2dFramework
{
	class MathHelper
	{
	public:
		static float RadianToDegree(float radian);
		static float DegreeToRadian(float degree);
		static float Clamp(float num, float min, float max);
	};
}