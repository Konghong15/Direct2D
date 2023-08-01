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

		virtual void UpdateCollider() = 0; // �� �浹 ó������ ��� �����ϱ� �Ʊ���� �� �� ������Ʈ ��Ų �� �����
		virtual bool CheckCollision(ICollideable* other, Manifold* outManifold) = 0; // �浹 ����
		
		virtual void onCollision(ICollideable* other, const Manifold& manifold) = 0; // �浹 ����


		/* 	�浹 ���� ó���� �������̽� Ŭ������ ���������� GameObject�� ������ ����� �ʿ���
		�ش� �Լ��� ���� ���� �Լ��̹Ƿ� ���� ������� ���� ���� �浹 ���� ��� �����ϴ�. */
		virtual inline GameObject* GetGameObject() const = 0;
		virtual inline eColliderType GetColliderType() const = 0; // ��Ÿ�ӿ� ĳ������ ���� ����

	};
}