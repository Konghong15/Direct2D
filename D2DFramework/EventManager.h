#pragma once

#include <cassert>
#include <map>
#include <queue>
#include <functional>
#include <string>

namespace d2dFramework
{
	enum class eDefaultEvent
	{
		ChangeScene,
	};

	class EventManager
	{
		friend class GameProcessor;

	public:
		static EventManager* GetInstance();

		inline void RegisterEvent(eDefaultEvent defaultSceneEvent, const std::string& data);
		inline void RegisterEvent(const std::string& event, const std::string& data);
		inline void RegisterEventHandler(const std::string& event, std::function<void(const std::string&)> callback);

		inline const std::string& GetEventName(eDefaultEvent defaultSceneEvent);

	private:
		EventManager();
		~EventManager() = default;

		void handleEvent();
		void release();

	private:
		static EventManager* mInstance;

		std::map<eDefaultEvent, std::string> mDefaultEventNameMap;
		std::map<std::string, std::function<void(const std::string& data)>> mEventCallbackMap;
		std::queue<std::pair<std::string, std::string>> mEventQueue;
	};

	void EventManager::RegisterEvent(eDefaultEvent defaultSceneEvent, const std::string& data)
	{
		auto keyName = mDefaultEventNameMap.find(defaultSceneEvent);
		assert(keyName != mDefaultEventNameMap.end());

		RegisterEvent(keyName->second, data);
	}
	void EventManager::RegisterEvent(const std::string& event, const std::string& data)
	{
		mEventQueue.push({ event, data });
	}
	void EventManager::RegisterEventHandler(const std::string& event, std::function<void(const std::string&)> callback)
	{
		mEventCallbackMap.insert({ event, callback });
	}

	const std::string& EventManager::GetEventName(eDefaultEvent defaultEvent)
	{
		auto iter = mDefaultEventNameMap.find(defaultEvent);
		assert(iter != mDefaultEventNameMap.end());

		return iter->second;
	}
}