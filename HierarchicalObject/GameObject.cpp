#include "GameObject.h"
#include "RenderManger.h"

namespace hierarchicalObject
{
	GameObject::GameObject(const gameProcessor::hRectangle rectangle, float radian, float rotateWeight, GameObject* parant)
		: mRectangle(rectangle)
		, mScale(gameProcessor::Matrix3X3::Identity())
		, mRotate(gameProcessor::Matrix3X3::GetRotate(radian))
		, mTranslate(mScale)
		, mTransform()
		, mParant(parant)
		, mRadian(radian)
		, mRotateWeight(rotateWeight)
	{
		const gameProcessor::Vector2& center = mRectangle.GetCenter();
		mRectangle.Move(-center.GetX(), -center.GetY());
		mTranslate.SetTranslate(center.GetX(), center.GetY());
		mTransform = gameProcessor::Matrix3X3::ComineMatrix(3, mScale, mRotate, mTranslate);

		if (mParant != nullptr)
		{
			mTransform *= mParant->mTransform;
			mParant->mChildren.push_back(this);
		}
	}

	void GameObject::Update(float deltaTime)
	{
		mRadian += deltaTime * mRotateWeight;
		mRotate = gameProcessor::Matrix3X3::GetRotate(mRadian);
		mTransform = gameProcessor::Matrix3X3::ComineMatrix(3, mScale, mRotate, mTranslate);

		if (mParant != nullptr)
		{
			mTransform *= mParant->mTransform;
		}

		for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
		{
			(*iter)->Update(deltaTime);
		}
	}

	void GameObject::Render(gameProcessor::RenderManager* renderManager)
	{
		renderManager->DrawRectangle(mRectangle, mTransform, { 0,0,0,1 });

		for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
		{
			(*iter)->Render(renderManager);
		}
	}
}