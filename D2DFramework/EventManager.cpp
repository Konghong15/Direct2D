#include "EventManager.h"

#include "eFrameworkID.h"

namespace d2dFramework
{
	EventManager* EventManager::mInstance = nullptr;

	EventManager::EventManager()
		: BaseEntity(static_cast<unsigned int>(eFramworkID::EventManager))
	{
		mDefaultEventNameMap.insert({ eDefaultEvent::ChangeScene, "ChangeScene" });
	}

	EventManager* EventManager::GetInstance()
	{
		assert(mInstance != nullptr); // GameProcessor에서 개체 생성을 보장해줘야함
		return mInstance;
	}

	void EventManager::SendEvent(const std::string& event, unsigned int id, const std::string& data)
	{
		auto keyCallback = mEventCallbackMap.find(event);
		assert(keyCallback != mEventCallbackMap.end());

		std::unordered_map<unsigned int, std::function<void(const std::string& data)>> listeners = keyCallback->second;
		auto listener = listeners.find(id);

		if (listener != listeners.end())
		{
			listener->second(data);
		}
	}

	void EventManager::BroadcastEvent(const std::string& event, const std::string& data)
	{
		auto keyCallback = mEventCallbackMap.find(event);
		assert(keyCallback != mEventCallbackMap.end());

		std::unordered_map<unsigned int, std::function<void(const std::string& data)>> listener = keyCallback->second;

		for (auto iter = listener.begin(); iter != listener.end(); ++iter)
		{
			iter->second(data);
		}
	}

	void EventManager::handleEvent()
	{
		while (!mBroadcastEventQueue.empty())
		{
			auto keyData = mBroadcastEventQueue.front();
			mBroadcastEventQueue.pop();

			BroadcastEvent(keyData.first, keyData.second);
		}

		while (!mSendEventQueue.empty())
		{
			auto tupleData = mSendEventQueue.front();
			mSendEventQueue.pop();

			SendEvent(std::get<0>(tupleData), std::get<1>(tupleData), std::get<2>(tupleData));
		}
	}

	void EventManager::release()
	{
		while (!mBroadcastEventQueue.empty())
		{
			mBroadcastEventQueue.pop();
		}
		while (!mSendEventQueue.empty())
		{
			mSendEventQueue.pop();
		}

		mEventCallbackMap.clear();
	}
}