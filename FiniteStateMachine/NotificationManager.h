#pragma once

#include <vector>
#include <string>

#include "INotifiable.h"

namespace finiteStateMachine
{
	class NotificationManager final
	{
	public:
		static NotificationManager* GetInstance();
		static void DeleteInstance();

		inline void SendNotification(const std::wstring& notifyName, const std::wstring& information);

		inline void Register(INotifiable* notifiable);
		inline void Remove(INotifiable* notifiable);

	private:
		NotificationManager() = default;
		~NotificationManager() = default;
		NotificationManager(const NotificationManager&) = delete;
		NotificationManager& operator=(const NotificationManager&) = delete;

	private:
		static NotificationManager* mInstance;
		enum { RESERVE_SIZE = 512 };


		std::vector<INotifiable*> mNotifiables;
	};

	void NotificationManager::SendNotification(const std::wstring& notifyName, const std::wstring& information)
	{
		for (INotifiable* notifiable : mNotifiables)
		{
			notifiable->OnNotify(notifyName, information);
		}
	}

	void NotificationManager::Register(INotifiable* notifiable)
	{
		mNotifiables.push_back(notifiable);
	}

	void NotificationManager::Remove(INotifiable* notifiable)
	{
		for (auto iter = mNotifiables.begin(); iter != mNotifiables.end(); ++iter)
		{
			if (*iter == notifiable)
			{
				mNotifiables.erase(iter);
				break;
			}
		}
	}
}