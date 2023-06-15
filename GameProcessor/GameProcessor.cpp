#include "GameProcessor.h"

namespace gameProcessor
{
	GameProcessor::GameProcessor(UINT width, UINT height, std::wstring name)
		: mWidth(width)
		, mHeight(height)
		, mTitle(name)
	{
	}
}