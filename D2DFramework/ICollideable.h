#pragma once

#include "IBaseInterface.h"

namespace d2dFramework
{
	class hRectangle;

	class ICollideable : public IBaseInterface
	{
	public:
		ICollideable();
		virtual ~ICollideable();

		virtual void CheckCollision(ICollideable* other) = 0;
		inline virtual const hRectangle& GetCollider() = 0; // ���߿��� �������� ��������
	};
}