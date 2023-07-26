#pragma once

#include <d2d1.h>

#include "Component.h"
#include "IRenderable.h"

namespace d2dFramework
{
	class GameObject;

	class BoxSprite : public Component, public IRenderable
	{
	public:
		BoxSprite(GameObject* owner);
		virtual ~BoxSprite() = default;

		virtual void Render(RenderManager* renderManager);

		inline void SetRectangle(const D2D1_RECT_F& rectangle);
		inline void SetBaseColor(const D2D1_COLOR_F& baseColor);
		inline void SetBorderColor(const D2D1_COLOR_F& borderColor);

		inline const D2D1_RECT_F& GetRectangle(void) const;
		inline const D2D1_COLOR_F& GetBaseColor(void) const;
		inline const D2D1_COLOR_F& GetBorderColor(void) const;

	private:
		D2D1_RECT_F mRectangle;
		D2D1_COLOR_F mBaseColor;
		D2D1_COLOR_F mBorderColor;
	};

	void BoxSprite::SetRectangle(const D2D1_RECT_F& rectangle)
	{
		mRectangle = rectangle;
	}
	void BoxSprite::SetBaseColor(const D2D1_COLOR_F& baseColor)
	{
		mBaseColor = baseColor;
	}
	void BoxSprite::SetBorderColor(const D2D1_COLOR_F& borderColor)
	{
		mBorderColor = borderColor;
	}

	const D2D1_RECT_F& BoxSprite::GetRectangle(void) const
	{
		return mRectangle;
	}
	const D2D1_COLOR_F& BoxSprite::GetBaseColor(void) const
	{
		return mBaseColor;
	}
	const D2D1_COLOR_F& BoxSprite::GetBorderColor(void) const
	{
		return mBorderColor;
	}
}