#include "OldRenderComponent.h"
#include "RenderManger.h"
#include "Helper.h"

namespace componentBased
{
	OldRenderComponent::OldRenderComponent(const gameProcessor::hRectangle& rectangle)
		: mRectangle(rectangle)
		, mMatrix(gameProcessor::Matrix3X3::Identity())
	{
	}

	void OldRenderComponent::Render(gameProcessor::RenderManager* renderManager)
	{
		renderManager->DrawRectangle(mRectangle, mMatrix, gameProcessor::Helper::GetRGBA(0, 0, 255, 255));
	}
}