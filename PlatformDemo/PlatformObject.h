#pragma once

#include "GameObject.h"


namespace gameProcessor
{
	class InputManager;
}

namespace platform
{
	enum eDirectionX
	{
		Left,
		Right,
		None
	};

	class Obstacle;

	class PlatformObject : public gameProcessor::GameObject
	{
	public:
		PlatformObject(const gameProcessor::hRectangle& rectangle, float maxSpeed, float accelation, float jumpspeed, float gravityAcceleration);

		virtual void HandleCollision(const Obstacle& obstacle);
		virtual void HandleInput(gameProcessor::InputManager* inputManager);
		virtual void Update(float deltaTime) override;
		virtual void Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& transform) override;

	private:
		enum { FLOOR_Y = -200 };

		gameProcessor::Vector2 mVelocity; // ���� �̵��� �����

		// ����� ����
		bool mbIsMove;
		bool mbIsLeft;

		// ���� ���
		const float mLeverMaxSpeed;
		float mLeverVelocityX; // ���� �̵��� �����
		float mLeverAccelation;

		// ��ư ���
		const float mButtonMaxSpeed;
		float mButtonVelocityX;
		float mButtonAccelation;
		bool mbButtonPush;

		// 2�� ���
		const float mDoubleDashMaxSpeed;
		float mDoubleDashVelocityX;
		float mDoubleDashAccelation;
		bool mbIsDoubleDash;
		eDirectionX mLastInputDirctionX;
		float mDoubleDashElpased;

		// ����
		bool mbIsJump;
		float mJumpVelocityY;
		float mGravityAcceleration;

		// ���� ����
		float mJumpSpeed;

		// ���� ����
		bool mbEnterJumpKey;
		float mJumpExitSpeed;

		// 2�� ����
		enum { MAX_JUMP_COUNT = 5 };
		unsigned int mJumpCount;

		// �ﰢ ����
		bool mbIsCollision;
		bool mbTriangleJump;
	};
}