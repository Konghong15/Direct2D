#pragma once

#include "GameProcessor.h"

namespace componentBase
{
	class D2DComponentBase final : public gameProcessor::GameProcessor
	{
	public:
		D2DComponentBase(UINT width, UINT height, std::wstring name);
		~D2DComponentBase() = default;

		void Init() override;
		void Update() override;
		void Render() override;
		void Destroy() override;

	private:
	};
}