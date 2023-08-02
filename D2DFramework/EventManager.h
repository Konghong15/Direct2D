#pragma once

#include "BaseEntity.h"

#include <cassert>
#include <map>
#include <unordered_map>
#include <queue>
#include <functional>
#include <string>

namespace d2dFramework
{
	enum class eDefaultEvent 
	{
		ChangeScene,
		EnterCollision,
		OnCollision,
		ExitCollision,
		// CreateObject,
		// DeleteObject
	};

	class EventManager final : public BaseEntity
	{
		friend class GameProcessor;

	public:
		static EventManager* GetInstance();

		void BroadcastEvent(const std::string& event, const std::string& data);
		void SendEvent(const std::string& event, unsigned int id, const std::string& data);

		inline void AddLateBroadcastEvent(const std::string& event, const std::string& data);
		inline void AddLateSendEvent(const std::string& event, unsigned int id, const std::string& data);

		inline void RegisterEventHandler(const std::string& event, unsigned int id, std::function<void(const std::string&)> callback);
		inline void UnRegisterEventHandler(const std::string& event, unsigned int id);

		inline const std::string& GetEventName(eDefaultEvent defaultSceneEvent);

	private:
		EventManager();
		~EventManager() = default;

		void handleEvent();
		void release();

	private:
		static EventManager* mInstance;

		std::map<eDefaultEvent, std::string> mDefaultEventNameMap;
		std::unordered_map<std::string, std::unordered_map<unsigned int, std::function<void(const std::string& data)>>> mEventCallbackMap;
		std::queue<std::pair<std::string, std::string>> mBroadcastEventQueue;
		std::queue<std::tuple<std::string, unsigned int, std::string>> mSendEventQueue;
	};

	void EventManager::AddLateBroadcastEvent(const std::string& event, const std::string& data)
	{
		mBroadcastEventQueue.push({ event, data });
	}
	void EventManager::AddLateSendEvent(const std::string& event, unsigned int id, const std::string& data)
	{
		mSendEventQueue.push({ event, id, data });
	}
	void EventManager::RegisterEventHandler(const std::string& event, unsigned int id, std::function<void(const std::string&)> callback)
	{
		mEventCallbackMap.insert({ event, std::unordered_map<unsigned int, std::function<void(const std::string & data)>>() });
		mEventCallbackMap.find(event)->second.insert({ id, callback });
	}

	void EventManager::UnRegisterEventHandler(const std::string& event, unsigned int id)
	{
		mEventCallbackMap.find(event)->second.erase(id);
	}

	const std::string& EventManager::GetEventName(eDefaultEvent defaultEvent)
	{
		auto iter = mDefaultEventNameMap.find(defaultEvent);
		assert(iter != mDefaultEventNameMap.end());

		return iter->second;
	}
}