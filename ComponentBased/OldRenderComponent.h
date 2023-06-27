#pragma once

#include "hRectangle.h"
#include "Matrix3X3.h"

namespace gameProcessor
{
	class RenderManager;
}

namespace componentBased
{
	class OldRenderComponent
	{
	public:
		OldRenderComponent(const gameProcessor::hRectangle& rectangle);

		inline void SetMatrix3X3(const gameProcessor::Matrix3X3& matrix);
		inline const gameProcessor::Matrix3X3& GetMatrix3X3() const;

		void Render(gameProcessor::RenderManager* renderManager);

	private:
		gameProcessor::hRectangle mRectangle;
		gameProcessor::Matrix3X3 mMatrix;
	};

	void OldRenderComponent::SetMatrix3X3(const gameProcessor::Matrix3X3& matrix)
	{
		mMatrix = matrix;
	}

	const gameProcessor::Matrix3X3& OldRenderComponent::GetMatrix3X3() const
	{
		return mMatrix;
	}
}