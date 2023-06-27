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

		// 1. �ʱ⿡�� Ŭ���� ���� ��� ������ ���� ������Ʈ�� ������
		OldObject* mOldObject;

		// 2. Ŭ������ �� ������ �þ�� ���� �ҽ��ڵ� ������ ���������, Ŭ���� ������ ������ �����ϰ� �;���
		//	a. ����� ���� ���뼺�� ��ȹ���� ���� ��û �� �ҽ��ڵ� ���� -> �������� ������ ��ħ
		//	b. ���������� ���� ���뼺�� ��Ÿ�ӿ��� ������ ������! <- �̸� ���� ���� �߿� ������� �����Ͽ� ����� �� �ִ� ������Ʈ�� �����.
		OldComponentObject* mOldComponentObject;

		// �� ������ �� ����� �и��Ͽ� ������Ʈ�� �۵��Ѵٴ� ����� ������� ���������� ���ذ� ���� ������ ���� ����� �ƴϴ�.
		// �̷��� ������ ����Ͻ��� �������� ������ �ùٸ� ������ �ƴ϶�� ���� ����ؾ� ��

		// 3. ������ �ϳ��� Ŭ���� �ȿ��� �����ϴ� �ɹ��� ������Ʈ�� �и��Ǹ� ���뿡 ������ �߻���
		//  a. ���� ����
		//	b. ��ε�ĳ����

	};
}