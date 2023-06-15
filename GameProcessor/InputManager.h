#pragma once

#include "Vector2.h"

namespace gameProcessor
{
	enum class eKeyState
	{
		None,
		Push,
		Hold,
		Pop,
	};

	class InputManager final
	{
	public:
		InputManager();
		~InputManager() = default;
		InputManager(const InputManager& other) = delete;
		InputManager operator=(const InputManager& other) = delete;

		void Init();
		void Update();

		inline eKeyState GetKeyState(WORD keyCode) const;
		inline const Vector2& GetMousePos() const;

	private:
		enum { KEY_STATES_SIZE = 256 };

		eKeyState mKeyStates[KEY_STATES_SIZE];
		Vector2 mMousePos;
	};

	eKeyState InputManager::GetKeyState(WORD keyCode) const
	{
		return mKeyStates[keyCode];
	}

	const Vector2& InputManager::GetMousePos() const
	{
		return mMousePos;
	}
}