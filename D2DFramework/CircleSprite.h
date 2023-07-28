#pragma once

#include <d2d1.h>

#include "Component.h"
#include "IRenderable.h"

namespace d2dFramework
{
	class GameObject;

	class CircleSprite : public Component, public IRenderable
	{
	public:
		CircleSprite(GameObject* owner);
		virtual ~CircleSprite() = default;

		virtual void Render(RenderManager* renderManager);

		inline void SetEllipse(const D2D1_ELLIPSE& ellipse);
		inline void SetBaseColor(const D2D1_COLOR_F& baseColor);
		inline void SetBorderColor(const D2D1_COLOR_F& borderColor);

		inline const D2D1_ELLIPSE& GetEllipse(void) const;
		inline const D2D1_COLOR_F& GetBaseColor(void) const;
		inline const D2D1_COLOR_F& GetBorderColor(void) const;

	private:
		D2D1_ELLIPSE mEllipse;
		D2D1_COLOR_F mBaseColor;
		D2D1_COLOR_F mBorderColor;
	};

	void CircleSprite::SetEllipse(const D2D1_ELLIPSE& ellipse)
	{
		mEllipse = ellipse;
	}
	void CircleSprite::SetBaseColor(const D2D1_COLOR_F& baseColor)
	{
		mBaseColor = baseColor;
	}
	void CircleSprite::SetBorderColor(const D2D1_COLOR_F& borderColor)
	{
		mBorderColor = borderColor;
	}

	const D2D1_ELLIPSE& CircleSprite::GetEllipse(void) const
	{
		return mEllipse;
	}
	const D2D1_COLOR_F& CircleSprite::GetBaseColor(void) const
	{
		return mBaseColor;
	}
	const D2D1_COLOR_F& CircleSprite::GetBorderColor(void) const
	{
		return mBorderColor;
	}
}