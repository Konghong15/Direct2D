#pragma once

#include <d2d1.h>

namespace gameProcessor
{
	class Helper
	{
	public:
		static float RadianToDegree(float radian);
		static float DegreeToRadian(float degree);
		static D2D1_COLOR_F GetRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	};
}