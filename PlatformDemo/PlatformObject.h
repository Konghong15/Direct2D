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

		gameProcessor::Vector2 mVelocity; // 현재 이동량 저장용

		// 입출력 관리
		bool mbIsMove;
		bool mbIsLeft;

		// 레버 대시
		const float mLeverMaxSpeed;
		float mLeverVelocityX; // 레버 이동량 저장용
		float mLeverAccelation;

		// 버튼 대시
		const float mButtonMaxSpeed;
		float mButtonVelocityX;
		float mButtonAccelation;
		bool mbButtonPush;

		// 2단 대시
		const float mDoubleDashMaxSpeed;
		float mDoubleDashVelocityX;
		float mDoubleDashAccelation;
		bool mbIsDoubleDash;
		eDirectionX mLastInputDirctionX;
		float mDoubleDashElpased;

		// 점프
		bool mbIsJump;
		float mJumpVelocityY;
		float mGravityAcceleration;

		// 고정 점프
		float mJumpSpeed;

		// 가변 점프
		bool mbEnterJumpKey;
		float mJumpExitSpeed;

		// 2단 점프
		enum { MAX_JUMP_COUNT = 5 };
		unsigned int mJumpCount;

		// 삼각 점프
		bool mbIsCollision;
		bool mbTriangleJump;
	};
}