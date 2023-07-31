#include "EventManager.h"

namespace d2dFramework
{
	EventManager* EventManager::mInstance = nullptr;

	EventManager::EventManager()
	{
		mDefaultEventNameMap.insert({ eDefaultEvent::ChangeScene, "ChangeScene" });
	}

	EventManager* EventManager::GetInstance()
	{
		assert(mInstance != nullptr); // GameProcessor에서 개체 생성을 보장해줘야함
		return mInstance;
	}

	void EventManager::handleEvent()
	{
		while (!mEventQueue.empty())
		{
			auto& keyData = mEventQueue.front();
			mEventQueue.pop();

			auto keyCallback = mEventCallbackMap.find(keyData.first);
			assert(keyCallback != mEventCallbackMap.end());
			keyCallback->second(keyData.second);
		}
	}

	void EventManager::release()
	{
		while (!mEventQueue.empty())
		{
			mEventQueue.pop();
		}

		mEventCallbackMap.clear();
	}
}