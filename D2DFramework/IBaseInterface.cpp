#include "IBaseInterface.h"

namespace d2dFramework
{
	GameProcessor* IBaseInterface::mGameProcessor = nullptr;

	void IBaseInterface::SetGameProcessor(GameProcessor* gameProcessror)
	{
		mGameProcessor = gameProcessror;
	}
}