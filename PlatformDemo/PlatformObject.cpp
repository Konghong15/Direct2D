#include "PlatformObject.h"
#include "InputManager.h"
#include "RenderManger.h"
#include "Collision.h"
#include "Obstacle.h"

namespace platform
{
	PlatformObject::PlatformObject(const gameProcessor::hRectangle& rectangle, float maxSpeed, float accelation, float jumpSpeed, float gravityAcceleration)
		: GameObject(rectangle)
		, mVelocity(0, 0)
		, mbIsMove(false)
		, mbIsLeft(false)

		, mLeverMaxSpeed(maxSpeed)
		, mLeverVelocityX(0.f)
		, mLeverAccelation(accelation)

		, mButtonMaxSpeed(maxSpeed)
		, mButtonVelocityX(0.f)
		, mButtonAccelation(accelation)
		, mbButtonPush(false)

		, mDoubleDashMaxSpeed(maxSpeed)
		, mDoubleDashVelocityX(0.f)
		, mDoubleDashAccelation(accelation)
		, mbIsDoubleDash(false)
		, mLastInputDirctionX(eDirectionX::None)
		, mDoubleDashElpased(0.f)

		, mbIsJump(false)
		, mJumpVelocityY(0.f)
		, mJumpSpeed(jumpSpeed)
		, mGravityAcceleration(gravityAcceleration)

		, mbEnterJumpKey(false)
		, mJumpExitSpeed(jumpSpeed / 2.f)

		, mJumpCount(0u)

		, mbIsCollision(false)
		, mbTriangleJump(false)
	{
	}

	void PlatformObject::HandleCollision(const Obstacle& obstacle)
	{
		const gameProcessor::hRectangle WorldRectangle = GetWorldRectangle();
		const gameProcessor::hRectangle obstacleWorldRectangle = obstacle.GetWorldRectangle();
		if (gameProcessor::Collision::CheckRectangleToRectangle(obstacleWorldRectangle, WorldRectangle))
		{
			mbIsCollision = true;
		}
	}

	void PlatformObject::HandleInput(gameProcessor::InputManager* inputManager)
	{
		if (inputManager->GetKeyState(VK_LEFT) == gameProcessor::eKeyState::Push)
		{
			mLastInputDirctionX = eDirectionX::Left;
			mbIsDoubleDash = mDoubleDashElpased < 0.2f;
			mDoubleDashElpased = 0.f;
		}
		else if (inputManager->GetKeyState(VK_LEFT) == gameProcessor::eKeyState::Hold)
		{
			mbIsMove = true;
			mbIsLeft = true;
		}
		else if (inputManager->GetKeyState(VK_RIGHT) == gameProcessor::eKeyState::Push)
		{
			mLastInputDirctionX = eDirectionX::Right;
			mbIsDoubleDash = mDoubleDashElpased < 0.2f;
			mDoubleDashElpased = 0.f;
		}
		else if (inputManager->GetKeyState(VK_RIGHT) == gameProcessor::eKeyState::Hold)
		{
			mbIsMove = true;
			mbIsLeft = false;
		}
		else
		{
			mbIsMove = false;
		}

		if (inputManager->GetKeyState(VK_UP) == gameProcessor::eKeyState::Push)
		{
			if (!mbIsJump)
			{
				mbIsJump = true;
				mJumpVelocityY = mJumpSpeed;

				mbEnterJumpKey = true; // 가변 길이 점프 비활성화 하기 위함

				mJumpCount = 1u; // 2단 점프
			}
			else if (mJumpCount < MAX_JUMP_COUNT)
			{
				if (mbIsCollision && mJumpVelocityY > 0.f)
				{
					mbTriangleJump = true;
					mJumpVelocityY = mJumpSpeed;

					mLeverVelocityX *= -0.5f; // 레버 이동량 저장용
					mButtonVelocityX *= -0.5f;
					mDoubleDashVelocityX *= -0.5f;

					++mJumpCount;
				}
				else
				{
					mJumpVelocityY += mJumpSpeed;
					++mJumpCount;
				}
			}
		}

		if (inputManager->GetKeyState('Z') == gameProcessor::eKeyState::Push)
		{
			if (!mbIsJump)
			{
				mbIsJump = true;
				mJumpVelocityY = mJumpSpeed;

				mbEnterJumpKey = true; // 가변 길이 점프

				mJumpCount = 1u; // 2단 점프
			}
		}
		else if (inputManager->GetKeyState('Z') == gameProcessor::eKeyState::Pop)
		{
			mbEnterJumpKey = false;
		}

		if (inputManager->GetKeyState('X') == gameProcessor::eKeyState::Hold)
		{
			mbButtonPush = true;
		}
		else
		{
			mbButtonPush = false;
		}
	}

	void PlatformObject::Update(float deltaTime)
	{
		const float DIRECTION_X = mbIsLeft ? -1 : 1;
		const float VELOCIRY_X = mVelocity.GetX() < 0.f ? -1 : 1;

		// handle 

		// handle variable Jump
		if (!mbEnterJumpKey && mJumpVelocityY > mJumpExitSpeed)
		{
			mJumpVelocityY = mJumpExitSpeed;
		}

		// handle Jump
		if (mbIsJump)
		{
			mJumpVelocityY += mGravityAcceleration * deltaTime;

			if (mTransformInfo.Translate.GetY() < FLOOR_Y) // 바닥과 충돌하면
			{
				mTransformInfo.Translate.SetY(FLOOR_Y);
				mJumpVelocityY = 0;
				mbIsJump = false;

				mbEnterJumpKey = false;

				mJumpCount = 0u;

				mbTriangleJump = false;
			}
		}

		if (!mbIsJump)
		{
			// handle DoubleDash
			mDoubleDashElpased += deltaTime;

			if (mbIsDoubleDash)
			{
				mDoubleDashVelocityX = mDoubleDashMaxSpeed * 2 * DIRECTION_X;

				mbIsDoubleDash = false;
			}
			else
			{
				const float DECELERATION = mDoubleDashMaxSpeed * deltaTime * -5.f * VELOCIRY_X;
				mDoubleDashVelocityX += DECELERATION;

				if (DECELERATION * mDoubleDashVelocityX > 0)
				{
					mDoubleDashVelocityX = 0;
				}
			}

			// handle buttonDash
			if (mbIsMove && mbButtonPush)
			{
				mButtonVelocityX += mButtonAccelation * deltaTime * DIRECTION_X;

				if (fabsf(mButtonVelocityX) > mButtonMaxSpeed)
				{
					mButtonVelocityX = mButtonMaxSpeed * VELOCIRY_X;
				}
			}
			else
			{
				const float DECELERATION = mButtonAccelation * deltaTime * -0.5f * VELOCIRY_X;
				mButtonVelocityX += DECELERATION;

				if (DECELERATION * mButtonVelocityX > 0)
				{
					mButtonVelocityX = 0;
				}
			}

			// handle laver
			if (mbIsMove)
			{
				mLeverVelocityX += mLeverAccelation * deltaTime * DIRECTION_X;

				if (fabsf(mLeverVelocityX) > mLeverMaxSpeed)
				{
					mLeverVelocityX = mLeverMaxSpeed * VELOCIRY_X;
				}
			}
			else
			{
				const float DECELERATION = mLeverAccelation * deltaTime * -0.5f * VELOCIRY_X;
				mLeverVelocityX += DECELERATION;

				if (DECELERATION * mLeverVelocityX > 0)
				{
					mLeverVelocityX = 0;
				}
			}
		}


		mVelocity.SetXY(mLeverVelocityX + mButtonVelocityX + mDoubleDashVelocityX, mJumpVelocityY);

		mTransformInfo.RotateInRadian = -mVelocity.GetX() / (mButtonMaxSpeed + mLeverMaxSpeed + mDoubleDashMaxSpeed);

		if (mbIsCollision && !mbTriangleJump)
		{
			mTransformInfo.Translate.Move(0, mVelocity.GetY());
		}
		else
		{
			mTransformInfo.Translate.Move(mVelocity.GetX(), mVelocity.GetY());
			mbTriangleJump = mbIsCollision;

		}

		GameObject::updateWorldTransform();
		GameObject::updateWorldRectangle();
		GameObject::updateChildren(deltaTime);
	}

	void PlatformObject::Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& transform)
	{
		renderManager->DrawRectangle(mLocalRectangle, mTransformInfo.WorldTransform * transform);

		if (mbButtonPush)
		{
			renderManager->FillRectangle(mLocalRectangle, mTransformInfo.WorldTransform * transform);
		}

		if (mbIsCollision)
		{
			renderManager->FillRectangle(mLocalRectangle, mTransformInfo.WorldTransform * transform, { 255, 0, 0, 255 });
		}

		GameObject::renderChildren(renderManager, transform);
		mbIsCollision = false;
	}
}
