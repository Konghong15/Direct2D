#pragma once

namespace d2dFramework
{
	class RenderManager;

	class IRenderable
	{
		friend class GameProcessor;

	public:
		IRenderable() = default;
		virtual ~IRenderable() = default;

		virtual void Init() = 0; 
		virtual void Render() = 0;
		virtual void Release() = 0; 

	protected:
		inline RenderManager* GetRenderManager() const;

	private:
		static void SetRenderManager(RenderManager* renderManager);

	private:
		static RenderManager* mRenderManager;
	};

	RenderManager* IRenderable::GetRenderManager() const
	{
		return mRenderManager;
	}
}