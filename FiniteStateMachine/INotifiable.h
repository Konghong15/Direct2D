#pragma once

#include <string>
#include "NotificationManager.h"

namespace finiteStateMachine
{
	class INotifiable
	{
	public:
		INotifiable()
		{
			NotificationManager::GetInstance()->Register(this);
		}
		virtual ~INotifiable()
		{
			NotificationManager::GetInstance()->Remove(this);
		}

		virtual void OnNotify(const std::wstring& notifyName, const std::wstring& infomation) = 0;
	};
}