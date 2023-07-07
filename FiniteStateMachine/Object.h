#pragma once

#include <vector>

#include "hRectangle.h"
#include "Matrix3X3.h"

namespace gameProcessor
{
	class InputManager;
	class AnimationInstance;
	class RenderManager;
}

namespace finiteStateMachine
{
	class Object
	{
	public:
		Object(const gameProcessor::hRectangle& rectangle, Object* parent = nullptr);
		virtual ~Object();

		virtual void Update(float deltaTime) = 0;
		virtual void Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& compositeTrasform);

		inline void SetParent(Object* object);
		inline void AddChild(Object* object);
		inline void RemoveChild(Object* object);
		inline void MultyplyMatrix(const gameProcessor::Matrix3X3& matrix);
		inline void MultyplyMatrixRecursive(const gameProcessor::Matrix3X3& matrix);
		inline void SetScale(const gameProcessor::Vector2& scale);
		inline void SetTranslate(const gameProcessor::Vector2& traslate);
		inline void SetRotateInRadin(float rotateInRadian);

		inline const Object* GetParentOrNull() const;
		inline const std::vector<Object*>& GetChildren() const;
		inline gameProcessor::hRectangle GetWorldRectangle() const;
		inline const gameProcessor::hRectangle& GetRectangle() const;
		inline const gameProcessor::Matrix3X3& GetTrasform() const;
		inline const gameProcessor::Vector2& GetScale() const;
		inline const gameProcessor::Vector2& GetTraslate() const;
		inline const float GetRotateInRadian() const;
		inline const gameProcessor::Vector2& GetDirection() const;

	protected:
		inline virtual gameProcessor::Matrix3X3 combineMatrix();

	protected:
		Object* mParent;
		std::vector<Object*> mChildren;
		gameProcessor::hRectangle mRectangle;

		gameProcessor::Vector2 mScale;
		float mRotateInRadian;
		gameProcessor::Vector2 mTranslate;
		gameProcessor::Matrix3X3 mTransform;
		gameProcessor::Vector2 mDirection;
	};

	void Object::SetParent(Object* object)
	{
		assert(object != nullptr);
		mParent = object;
	}

	void Object::AddChild(Object* object)
	{
		assert(object != nullptr);
		mChildren.push_back(object);
	}

	void Object::RemoveChild(Object* object)
	{
		assert(object != nullptr);
		for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
		{
			if (*iter == object)
			{
				mChildren.erase(iter);

				return;
			}
		}
	}

	void Object::MultyplyMatrix(const gameProcessor::Matrix3X3& matrix)
	{
		mTransform *= matrix;
	}


	void Object::MultyplyMatrixRecursive(const gameProcessor::Matrix3X3& matrix)
	{
		MultyplyMatrix(matrix);

		for (Object* child : mChildren)
		{
			child->MultyplyMatrixRecursive(matrix);
		}
	}

	void Object::SetScale(const gameProcessor::Vector2& scale)
	{
		mScale = scale;
	}

	void Object::SetTranslate(const gameProcessor::Vector2& traslate)
	{
		mTranslate = traslate;
	}

	void Object::SetRotateInRadin(float rotateInRadian)
	{
		mRotateInRadian = rotateInRadian;
	}

	gameProcessor::hRectangle Object::GetWorldRectangle() const
	{
		return mRectangle * mTransform;
	}

	const gameProcessor::hRectangle& Object::GetRectangle() const
	{
		return mRectangle;
	}

	const gameProcessor::Matrix3X3& Object::GetTrasform() const
	{
		return mTransform;
	}

	const gameProcessor::Vector2& Object::GetScale() const
	{
		return mScale;
	}

	const gameProcessor::Vector2& Object::GetTraslate() const
	{
		return mTranslate;
	}

	const float Object::GetRotateInRadian() const
	{
		return mRotateInRadian;
	}

	gameProcessor::Matrix3X3 Object::combineMatrix()
	{
		return gameProcessor::Matrix3X3::ComineMatrix(3,
			gameProcessor::Matrix3X3::GetScale(mScale),
			gameProcessor::Matrix3X3::GetRotate(mRotateInRadian),
			gameProcessor::Matrix3X3::GetTranslate(mTranslate));
	}

	const Object* Object::GetParentOrNull() const
	{
		return mParent;
	}

	const std::vector<Object*>& Object::GetChildren() const
	{
		return mChildren;
	}

	const gameProcessor::Vector2& Object::GetDirection() const
	{
		return mDirection;
	}
}