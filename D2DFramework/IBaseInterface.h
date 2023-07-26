#pragma once

#include <cassert>

namespace d2dFramework
{
	class GameProcessor;

	class IBaseInterface
	{
		friend class GameProcessor;

	public:
		IBaseInterface() = default;
		virtual ~IBaseInterface() = 0 {}

	protected:
		inline GameProcessor* GetGameProcessor();

	private:
		static void SetGameProcessor(GameProcessor* gameProcessror);

	private:
		static GameProcessor* mGameProcessor;
	};

	GameProcessor* IBaseInterface::GetGameProcessor()
	{
		assert(mGameProcessor != nullptr);

		return mGameProcessor;
	}
}