#pragma once

#include <cassert>

namespace componentBase
{
	class RenderSystem;

	class IRenderable
	{
	public:
		IRenderable() = default;
		virtual ~IRenderable() = 0;

		virtual void Render(RenderSystem* renderSystem) = 0;
	};
}