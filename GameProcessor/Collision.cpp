#include <cmath>
#include <limits>

#include "Collision.h"
#include "Vector2.h"
#include "Circle.h"
#include "hRectangle.h"

#define FLT_EPSILON (0.001f)

namespace gameProcessor
{
	bool Collision::CheckPointToRectangle(const Vector2& point, const hRectangle& rectangle)
	{
		// 정점을 두개만 다루면 제대로 처리가 안된다.

		Vector2 normalVector[4] =
		{
			rectangle.GetTopLeft() - rectangle.GetBottomLeft(),
			rectangle.GetBottomLeft() - rectangle.GetBottomRight(),
			rectangle.GetBottomRight() - rectangle.GetTopRight(),
			rectangle.GetTopRight() - rectangle.GetTopLeft()
		};

		for (int i = 0; i < 4; ++i)
		{
			normalVector[i].Normalize();
			float tempX = normalVector[i].GetX();
			float tempY = normalVector[i].GetY();
			normalVector[i].SetX(-tempY);
			normalVector[i].SetY(tempX);
		}

		for (int i = 0; i < 4; ++i)
		{
			float rectMin = std::numeric_limits<float>::max();
			float rectMax = std::numeric_limits<float>::min();

			for (int j = 0; j < static_cast<int>(eRectangleIndex::Size); ++j)
			{
				int scalar = normalVector[i].Dot(rectangle.GetVertex(static_cast<eRectangleIndex>(j)));

				if (rectMax < scalar)
				{
					rectMax = scalar;
				}
				else if (rectMin > scalar)
				{
					rectMin = scalar;
				}
			}

			float pointScalar = normalVector[i].Dot(point);

			if (pointScalar < rectMin || pointScalar > rectMax)
			{
				return false;
			}
		}

		return true;
	}

	bool Collision::CheckLineToRectangle(const Vector2& start, const Vector2& end, const hRectangle& rectangle)
	{
		Vector2 normalVector[4] =
		{
			rectangle.GetTopLeft() - rectangle.GetBottomLeft(),
			rectangle.GetBottomLeft() - rectangle.GetBottomRight(),
			rectangle.GetBottomRight() - rectangle.GetTopRight(),
			rectangle.GetTopRight() - rectangle.GetTopLeft()
		};

		for (int i = 0; i < 4; ++i)
		{
			normalVector[i].Normalize();
			float tempX = normalVector[i].GetX();
			float tempY = normalVector[i].GetY();
			normalVector[i].SetX(-tempY);
			normalVector[i].SetY(tempX);
		}


		for (int i = 0; i < 4; ++i)
		{
			float rectMin = std::numeric_limits<float>::max();
			float rectMax = std::numeric_limits<float>::min();

			for (int j = 0; j < static_cast<int>(eRectangleIndex::Size); ++j)
			{
				int scalar = normalVector[i].Dot(rectangle.GetVertex(static_cast<eRectangleIndex>(j)));

				if (rectMax < scalar)
				{
					rectMax = scalar;
				}
				else if (rectMin > scalar)
				{
					rectMin = scalar;
				}
			}

			float startScalar = normalVector[i].Dot(start);
			float endScalar = normalVector[i].Dot(end);

			float maxScalar;
			float minScalar;

			if (startScalar > endScalar)
			{
				maxScalar = startScalar;
				minScalar = endScalar;
			}
			else
			{
				maxScalar = endScalar;
				minScalar = startScalar;
			}

			if (maxScalar < rectMin || minScalar > rectMax)
			{
				return false;
			}
		}

		return true;
	}

	bool Collision::CheckCircleToRectangle(const Circle& circle, const hRectangle& rectangle)
	{
		Vector2 normalVector[4] =
		{
			rectangle.GetTopLeft() - rectangle.GetBottomLeft(),
			rectangle.GetBottomLeft() - rectangle.GetBottomRight(),
			rectangle.GetBottomRight() - rectangle.GetTopRight(),
			rectangle.GetTopRight() - rectangle.GetTopLeft()
		};

		for (int i = 0; i < 4; ++i)
		{
			normalVector[i].Normalize();
			float tempX = normalVector[i].GetX();
			float tempY = normalVector[i].GetY();
			normalVector[i].SetX(-tempY);
			normalVector[i].SetY(tempX);
		}


		for (int i = 0; i < 4; ++i)
		{
			float rectMin = std::numeric_limits<float>::max();
			float rectMax = std::numeric_limits<float>::min();

			for (int j = 0; j < static_cast<int>(eRectangleIndex::Size); ++j)
			{
				int scalar = normalVector[i].Dot(rectangle.GetVertex(static_cast<eRectangleIndex>(j)));

				if (rectMax < scalar)
				{
					rectMax = scalar;
				}
				else if (rectMin > scalar)
				{
					rectMin = scalar;
				}
			}

			float centerScalar = normalVector[i].Dot(circle.GetCenter());
			float maxScalar = centerScalar + circle.GetRadius();
			float minScalar = centerScalar - circle.GetRadius();

			if (maxScalar < rectMin || minScalar > rectMax)
			{
				return false;
			}
		}

		return true;
	}

	bool Collision::CheckRectangleToRectangle(const Circle& rectangle1, const hRectangle& rectangle2)
	{
		Vector2 normalVector[4] =
		{
			rectangle2.GetTopLeft() - rectangle2.GetBottomLeft(),
			rectangle2.GetBottomLeft() - rectangle2.GetBottomRight(),
			rectangle2.GetBottomRight() - rectangle2.GetTopRight(),
			rectangle2.GetTopRight() - rectangle2.GetTopLeft()
		};

		for (int i = 0; i < 4; ++i)
		{
			normalVector[i].Normalize();
			float tempX = normalVector[i].GetX();
			float tempY = normalVector[i].GetY();
			normalVector[i].SetX(-tempY);
			normalVector[i].SetY(tempX);
		}

		for (int i = 0; i < 4; ++i)
		{
			float rectMin = std::numeric_limits<float>::max();
			float rectMax = std::numeric_limits<float>::min();

			for (int j = 0; j < static_cast<int>(eRectangleIndex::Size); ++j)
			{
				int scalar = normalVector[i].Dot(rectangle2.GetVertex(static_cast<eRectangleIndex>(j)));

				if (rectMax < scalar)
				{
					rectMax = scalar;
				}
				else if (rectMin > scalar)
				{
					rectMin = scalar;
				}
			}

			float otherRectMin = std::numeric_limits<float>::max();;
			float otherRectMax = std::numeric_limits<float>::min();;

			for (int j = 0; j < static_cast<int>(eRectangleIndex::Size); ++j)
			{
				int scalar = normalVector[i].Dot(rectangle2.GetVertex(static_cast<eRectangleIndex>(j)));

				if (rectMax < scalar)
				{
					rectMax = scalar;
				}
				else if (rectMin > scalar)
				{
					rectMin = scalar;
				}
			}

			if (otherRectMax < rectMin || otherRectMin > rectMax)
			{
				return false;
			}
		}

		return true;
	}

	bool Collision::CheckPointToCircle(const Vector2& point, const Circle& circle)
	{
		float diff = Vector2::GetDistance(point, circle.GetCenter());

		return circle.GetRadius() > diff;
	}
}