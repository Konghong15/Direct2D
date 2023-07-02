#include "RenderComponent.h"
#include "RenderManger.h"

namespace entityCamara
{
	RenderComponent::RenderComponent(unsigned int entityId, const gameProcessor::hRectangle& rectangle)
		: Component(entityId, eComponentType::Render)
		, mRectangle(rectangle)
	{
	}

	void RenderComponent::Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& matrix)
	{
		renderManager->DrawRectangle(mRectangle, matrix);
	}
}