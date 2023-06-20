#pragma once

namespace gameProcessor
{
	class Vector2
	{
	public:
		Vector2();
		~Vector2() = default;
		Vector2(const Vector2&) = default;
		Vector2& operator=(const Vector2&) = default;

		Vector2(float x, float y);

		static float GetDistance(const Vector2& vector, const Vector2& otherVector);

		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;
		Vector2 operator+(const Vector2& other) const;
		Vector2 operator-(const Vector2& other) const;

		float Dot(const Vector2& other);
		void Normalize();
		inline void Move(float x, float y);
		inline void SetX(float x);
		inline void SetY(float y);

		float GetMagnitude() const;
		inline float GetX() const;
		inline float GetY() const;

	private:
		float mX;
		float mY;
	};

	float Vector2::GetX() const
	{
		return mX;
	}

	float Vector2::GetY() const
	{
		return mY;
	}

	void Vector2::SetX(float x)
	{
		mX = x;
	}

	void Vector2::SetY(float y)
	{
		mY = y;
	}

	void Vector2::Move(float x, float y)
	{
		mX += x;
		mY += y;
	}
}