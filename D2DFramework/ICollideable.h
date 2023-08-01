#pragma once

#include "IBaseInterface.h"
#include "eColliderType.h"

namespace d2dFramework
{
	class hRectangle;
	class GameObject;
	struct Manifold;

	class ICollideable : public IBaseInterface
	{
	public:
		ICollideable();
		virtual ~ICollideable();

		virtual void UpdateCollider() = 0; // 매 충돌 처리마다 행렬 연산하기 아까워서 한 번 업데이트 시킨 거 사용함
		virtual bool CheckCollision(ICollideable* other, Manifold* outManifold) = 0; // 충돌 검출
		
		virtual void onCollision(ICollideable* other, const Manifold& manifold) = 0; // 충돌 반응


		/* 	충돌 관련 처리는 인터페이스 클래스에 의존하지만 GameObject에 접근할 방법이 필요함
		해당 함수는 순수 가상 함수이므로 다중 상속으로 인한 구현 충돌 없이 사용 가능하다. */
		virtual inline GameObject* GetGameObject() const = 0;
		virtual inline eColliderType GetColliderType() const = 0; // 런타임에 캐스팅을 위한 정보

	};
}