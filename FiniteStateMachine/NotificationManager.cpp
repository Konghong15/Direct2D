#include "NotificationManager.h"

namespace finiteStateMachine
{
	NotificationManager* NotificationManager::mInstance = nullptr;

	NotificationManager* NotificationManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new NotificationManager();
			mInstance->mNotifiables.reserve(RESERVE_SIZE);
		}

		return mInstance;
	}

	void NotificationManager::DeleteInstance()
	{
		delete mInstance;
		mInstance = nullptr;
	}
}