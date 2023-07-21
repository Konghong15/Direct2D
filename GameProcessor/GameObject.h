#pragma once

#include <vector>

#include "hRectangle.h"
#include "TransformInfo.h"

namespace gameProcessor
{
	class RenderManager;

	class GameObject
	{
	public:
		GameObject(const hRectangle& rectangle);
		GameObject(const hRectangle& rectangle, TransformInfo transformInfo);
		virtual ~GameObject() = default;

		virtual void Update(float deltaTime) = 0;
		virtual void Render(RenderManager* renderManager, const Matrix3X3& transform) = 0;

		inline const hRectangle& GetLocalRectangle() const;
		inline const hRectangle& GetWorldRectangle() const;
		inline const TransformInfo& GetTransformInfo() const;

	protected:
		inline void updateWorldTransform();
		inline void updateWorldRectangle();
		inline void updateChildren(float deltaTime);
		inline void renderChildren(RenderManager* renderManager, const Matrix3X3& transform);

	protected:
		gameProcessor::hRectangle mLocalRectangle;
		gameProcessor::hRectangle mWorldRectangle;
		TransformInfo mTransformInfo;

		GameObject* mParent; // 참조용도로만 사용하고 메모리 관리는 별도로 하도록 처리
		std::vector<GameObject*> mChildren; // 참조용도로만 사용하고 메모리 관리는 별도로 하도록 처리
	};

	const hRectangle& GameObject::GetLocalRectangle() const
	{
		return mLocalRectangle;
	}

	const hRectangle& GameObject::GetWorldRectangle() const
	{
		return mWorldRectangle;
	}

	const TransformInfo& GameObject::GetTransformInfo() const
	{
		return mTransformInfo;
	}

	void GameObject::updateWorldTransform()
	{
		mTransformInfo.LocalTransform = gameProcessor::Matrix3X3::ComineMatrix(
			3,
			gameProcessor::Matrix3X3::GetScale(mTransformInfo.Scale),
			gameProcessor::Matrix3X3::GetRotate(mTransformInfo.RotateInRadian),
			gameProcessor::Matrix3X3::GetTranslate(mTransformInfo.Translate)
		);

		if (mParent != nullptr)
		{
			mTransformInfo.WorldTransform *= mParent->GetTransformInfo().WorldTransform;
		}
		else
		{
			mTransformInfo.WorldTransform = mTransformInfo.LocalTransform;
		}
	}

	void GameObject::updateWorldRectangle()
	{
		mWorldRectangle = mLocalRectangle * mTransformInfo.WorldTransform;
	}

	void GameObject::updateChildren(float deltaTime)
	{
		for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
		{
			(*iter)->Update(deltaTime);
		}
	}

	void GameObject::renderChildren(RenderManager* renderManager, const Matrix3X3& transform)
	{
		for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
		{
			(*iter)->Render(renderManager, transform);
		}
	}
}