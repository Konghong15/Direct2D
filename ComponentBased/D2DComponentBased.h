#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <d2d1helper.h>

#include "GameProcessor.h"
#include "TimeManger.h"
#include "RenderManger.h"
#include "InputManager.h"

namespace componentBased
{
	class OldObject;
	class OldComponentObject;

	class D2DComponentBased : public gameProcessor::GameProcessor
	{
	public:
		D2DComponentBased(UINT width, UINT height, std::wstring name);
		virtual ~D2DComponentBased() = default;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Destroy() override;

	private:
		gameProcessor::TimeManager mTimeManager;
		gameProcessor::RenderManager mRenderManager;
		gameProcessor::InputManager mInputManager;

		// 1. 초기에는 클래스 내에 모든 동작을 가진 오브젝트가 동작함
		OldObject* mOldObject;

		// 2. 클래스의 각 동작이 늘어남에 따라 소스코드 관리가 어려워지며, 클래스 내부의 동작을 재사용하고 싶어짐
		//	a. 상속을 통한 재사용성은 기획자의 수정 요청 시 소스코드 변경 -> 재컴파일 과정을 거침
		//	b. 컴포지션을 통한 재사용성은 런타임에도 수정이 가능함! <- 이를 통해 실행 중에 마음대로 조립하여 사용할 수 있는 오브젝트를 만든다.
		OldComponentObject* mOldComponentObject;

		// 다 좋지만 각 기능을 분리하여 오브젝트가 작동한다는 기능이 사람에게 직관적으로 이해가 가며 성능이 좋은 방식은 아니다.
		// 이러한 선택은 비즈니스적 선택이지 언제나 올바른 방향이 아니라는 것을 기억해야 함

		// 3. 원래는 하나의 클래스 안에서 소통하던 맴버가 컴포넌트로 분리되며 소통에 문제가 발생함
		//  a. 직접 참조
		//	b. 브로드캐스팅

	};
}