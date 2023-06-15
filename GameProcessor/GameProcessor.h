#pragma once

#include <string>
#include <windows.h>

namespace gameProcessor
{
	class GameProcessor
	{
	public:
		GameProcessor(UINT width, UINT height, std::wstring name);
		virtual ~GameProcessor() = default;

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Destroy() = 0;

		inline UINT GetWidth() const;
		inline UINT GetHeight() const;
		inline const WCHAR* GetTitle() const;

	protected:
		UINT mWidth;
		UINT mHeight;

	private:
		std::wstring mTitle;
	};

	UINT GameProcessor::GetWidth() const
	{
		return mWidth;
	}

	UINT GameProcessor::GetHeight() const
	{
		return mHeight;
	}

	const WCHAR* GameProcessor::GetTitle() const
	{
		return mTitle.c_str();
	}
}
