#pragma once

#include <cassert>
#include <string>
#include <vector>
#include <windows.h>

namespace d2dFramework
{
	class TimeManager;
	class RenderManager;
	class InputManager;
	class ICollideable;
	class IFixedUpdateable;
	class IUpdateable;
	class IRenderable;
	class GameObject;

	class GameProcessor
	{
	public:
		GameProcessor(UINT width, UINT height, std::wstring name);
		virtual ~GameProcessor();

		virtual void Init();
		virtual void Update();
		virtual void Destroy();

		inline UINT GetWidth() const;
		inline UINT GetHeight() const;
		inline const WCHAR* GetTitle() const;

		inline TimeManager* GetTimeManager() const;
		inline RenderManager* GetRenderManager() const;

		inline void RegisterCollideable(ICollideable* collideable);
		inline void RegisterFixedUpdateable(IFixedUpdateable* fixedUpdateable);
		inline void RegisterUpdateable(IUpdateable* updateable);
		inline void RegisterRenderable(IRenderable* renderable);

		inline void UnregisterCollideable(ICollideable* collideable);
		inline void UnregisterFixedUpdateable(IFixedUpdateable* fixedUpdateable);
		inline void UnregisterUpdateable(IUpdateable* updateable);
		inline void UnregisterRenderable(IRenderable* renderable);

	private:
		void collision();
		void fixedUpdate(float deltaTime);
		void update(float deltaTime);
		void render();

	private:
		UINT mWidth;
		UINT mHeight;
		std::wstring mTitle;

		TimeManager* mTimeManager;
		RenderManager* mRenderManager;

		std::vector<ICollideable*> mCollideable;
		std::vector<IFixedUpdateable*> mFixedUpdateable;
		std::vector<IUpdateable*> mUpdateable;
		std::vector<IRenderable*> mRenderable;
	};

	UINT GameProcessor::GetWidth() const
	{
		return mWidth;
	}

	UINT GameProcessor::GetHeight() const
	{
		return mHeight;
	}

	const WCHAR* GameProcessor::GetTitle() const
	{
		return mTitle.c_str();
	}

	TimeManager* GameProcessor::GetTimeManager() const
	{
		assert(mTimeManager != nullptr);
		return mTimeManager;
	}

	RenderManager* GameProcessor::GetRenderManager() const
	{
		assert(mRenderManager != nullptr);
		return mRenderManager;
	}

	void GameProcessor::RegisterCollideable(ICollideable* collideable)
	{
		mCollideable.push_back(collideable);
	}
	void GameProcessor::RegisterFixedUpdateable(IFixedUpdateable* fixedUpdateable)
	{
		mFixedUpdateable.push_back(fixedUpdateable);
	}
	void GameProcessor::RegisterUpdateable(IUpdateable* updateable)
	{
		mUpdateable.push_back(updateable);
	}
	void GameProcessor::RegisterRenderable(IRenderable* renderable)
	{
		mRenderable.push_back(renderable);
	}

	void GameProcessor::UnregisterCollideable(ICollideable* collideable)
	{
		auto iter = std::find(mCollideable.begin(), mCollideable.end(), collideable);

		if (iter != mCollideable.end())
		{
			mCollideable.erase(iter);
		}
	}
	void GameProcessor::UnregisterFixedUpdateable(IFixedUpdateable* fixedUpdateable)
	{
		auto iter = std::find(mFixedUpdateable.begin(), mFixedUpdateable.end(), fixedUpdateable);

		if (iter != mFixedUpdateable.end())
		{
			mFixedUpdateable.erase(iter);
		}
	}
	void GameProcessor::UnregisterUpdateable(IUpdateable* updateable)
	{
		auto iter = std::find(mUpdateable.begin(), mUpdateable.end(), updateable);

		if (iter != mUpdateable.end())
		{
			mUpdateable.erase(iter);
		}
	}
	void GameProcessor::UnregisterRenderable(IRenderable* renderable)
	{
		auto iter = std::find(mRenderable.begin(), mRenderable.end(), renderable);

		if (iter != mRenderable.end())
		{
			mRenderable.erase(iter);
		}
	}
}
