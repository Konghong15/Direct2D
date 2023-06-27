#pragma once

namespace gameProcessor
{
	class RenderManager;
}

namespace componentBased
{
	class IRenderable
	{
	public:
		virtual void Render(gameProcessor::RenderManager* renderManager) = 0;
	};
}