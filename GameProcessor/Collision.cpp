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
		const size_t RECT_VERTEX_COUNT = static_cast<size_t>(eRectangleIndex::Size);

		eRectangleIndex index[RECT_VERTEX_COUNT] =
		{
			eRectangleIndex::TopLeft,
			eRectangleIndex::TopRight,
			eRectangleIndex::BottomRight,
			eRectangleIndex::BottomLeft,
		};

		for (int i = 0; i < RECT_VERTEX_COUNT; ++i)
		{
			eRectangleIndex cur = index[i];
			eRectangleIndex next = index[(i + 1) % 4];
			Vector2 line = rectangle.GetVertex(cur) - rectangle.GetVertex(next);

			line.Normalize();
			Vector2 normalVector(-line.GetY(), line.GetX());

			float rectMin = std::numeric_limits<float>::max();
			float rectMax = std::numeric_limits<float>::min();

			for (int j = 0; j < static_cast<int>(eRectangleIndex::Size); ++j)
			{
				int scalar = normalVector.Dot(rectangle.GetVertex(static_cast<eRectangleIndex>(j)));

				if (rectMax < scalar)
				{
					rectMax = scalar;
				}
				else if (rectMin > scalar)
				{
					rectMin = scalar;
				}
			}

			float pointScalar = normalVector.Dot(point);

			if (pointScalar < rectMin || pointScalar > rectMax)
			{
				return false;
			}
		}

		return true;
	}

	bool Collision::CheckLineToRectangle(const Vector2& start, const Vector2& end, const hRectangle& rectangle)
	{
		const size_t RECT_VERTEX_COUNT = static_cast<size_t>(eRectangleIndex::Size);

		eRectangleIndex index[RECT_VERTEX_COUNT] =
		{
			eRectangleIndex::TopLeft,
			eRectangleIndex::TopRight,
			eRectangleIndex::BottomRight,
			eRectangleIndex::BottomLeft,
		};

		for (int i = 0; i < RECT_VERTEX_COUNT; ++i)
		{
			eRectangleIndex cur = index[i];
			eRectangleIndex next = index[(i + 1) % 4];
			Vector2 line = rectangle.GetVertex(cur) - rectangle.GetVertex(next);

			line.Normalize();
			Vector2 normalVector(-line.GetY(), line.GetX());

			float rectMin = std::numeric_limits<float>::max();
			float rectMax = std::numeric_limits<float>::min();

			for (int j = 0; j < static_cast<int>(eRectangleIndex::Size); ++j)
			{
				int scalar = normalVector.Dot(rectangle.GetVertex(static_cast<eRectangleIndex>(j)));

				if (rectMax < scalar)
				{
					rectMax = scalar;
				}
				else if (rectMin > scalar)
				{
					rectMin = scalar;
				}
			}

			float maxScalar = normalVector.Dot(start);
			float minScalar = normalVector.Dot(end);

			if (minScalar > maxScalar)
			{
				float temp = maxScalar;
				maxScalar = minScalar;
				minScalar = maxScalar;
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
		const size_t RECT_VERTEX_COUNT = static_cast<size_t>(eRectangleIndex::Size);

		eRectangleIndex index[RECT_VERTEX_COUNT] =
		{
			eRectangleIndex::TopLeft,
			eRectangleIndex::TopRight,
			eRectangleIndex::BottomRight,
			eRectangleIndex::BottomLeft,
		};

		for (size_t i = 0; i < RECT_VERTEX_COUNT; ++i)
		{
			eRectangleIndex cur = index[i];
			eRectangleIndex next = index[(i + 1) % 4];
			Vector2 line = rectangle.GetVertex(cur) - rectangle.GetVertex(next);

			line.Normalize();
			Vector2 normalVector(-line.GetY(), line.GetX());

			float rectMin = std::numeric_limits<float>::max();
			float rectMax = std::numeric_limits<float>::min();

			for (int j = 0; j < RECT_VERTEX_COUNT; ++j)
			{
				int scalar = normalVector.Dot(rectangle.GetVertex(static_cast<eRectangleIndex>(j)));

				if (rectMax < scalar)
				{
					rectMax = scalar;
				}
				if (rectMin > scalar)
				{
					rectMin = scalar;
				}
			}

			int scalar = normalVector.Dot(circle.GetCenter());

			float circleMin = scalar - circle.GetRadius();
			float circleMax = scalar + circle.GetRadius();

			if (circleMax < rectMin || circleMin > rectMax)
			{
				return false;
			}
		}

		return true;
	}

	bool Collision::CheckCircleToCircle(const Circle& lhs, const Circle& rhs)
	{
		return Vector2::GetDistance(lhs.GetCenter(), rhs.GetCenter()) < lhs.GetRadius() + rhs.GetRadius();
	}

	bool Collision::CheckRectangleToRectangle(const hRectangle& rectangle1, const hRectangle& rectangle2)
	{
		const size_t VERTEX_COUNT = static_cast<size_t>(eRectangleIndex::Size);

		eRectangleIndex index[VERTEX_COUNT] =
		{
			eRectangleIndex::TopLeft,
			eRectangleIndex::TopRight,
			eRectangleIndex::BottomRight,
			eRectangleIndex::BottomLeft,
		};

		Vector2 normalVectors[VERTEX_COUNT];

		for (size_t i = 0; i < VERTEX_COUNT; ++i)
		{
			eRectangleIndex cur = index[i];
			eRectangleIndex next = index[(i + 1) % 4];

			Vector2 line = rectangle1.GetVertex(cur) - rectangle1.GetVertex(next);
			line.Normalize();
			normalVectors[i] = { -line.GetY(), line.GetX() };
		}

		for (size_t i = 0; i < VERTEX_COUNT; ++i)
		{
			float rectMin = std::numeric_limits<float>::max();
			float rectMax = -std::numeric_limits<float>::max();

			for (int j = 0; j < VERTEX_COUNT; ++j)
			{
				float scalar = normalVectors[i].Dot(rectangle1.GetVertex(static_cast<eRectangleIndex>(j)));

				if (rectMax < scalar)
				{
					rectMax = scalar;
				}
				if (rectMin > scalar)
				{
					rectMin = scalar;
				}
			}

			float otherRectMin = std::numeric_limits<float>::max();
			float otherRectMax = -std::numeric_limits<float>::max();

			for (size_t j = 0; j < VERTEX_COUNT; ++j)
			{
				float scalar = normalVectors[i].Dot(rectangle2.GetVertex(static_cast<eRectangleIndex>(j)));

				if (otherRectMax < scalar)
				{
					otherRectMax = scalar;
				}
				if (otherRectMin > scalar)
				{
					otherRectMin = scalar;
				}
			}

			if (otherRectMax < rectMin || rectMax < otherRectMin)
			{
				return false;
			}
		}

		return true;
	}


	bool Collision::ContainRectangleToRectangle(const hRectangle& outRectangle, const hRectangle& inRectangle)
	{
		const size_t VERTEX_COUNT = static_cast<size_t>(eRectangleIndex::Size);

		eRectangleIndex index[VERTEX_COUNT] =
		{
			eRectangleIndex::TopLeft,
			eRectangleIndex::TopRight,
			eRectangleIndex::BottomRight,
			eRectangleIndex::BottomLeft,
		};

		for (int i = 0; i < 4; ++i)
		{
			eRectangleIndex cur = index[i];
			eRectangleIndex next = index[(i + 1) % 4];
			Vector2 line = outRectangle.GetVertex(cur) - outRectangle.GetVertex(next);

			line.Normalize();
			Vector2 normalVector(-line.GetY(), line.GetX());

			float rectMin = std::numeric_limits<float>::max();
			float rectMax = -std::numeric_limits<float>::max();

			for (int j = 0; j < static_cast<int>(eRectangleIndex::Size); ++j)
			{
				float scalar = normalVector.Dot(outRectangle.GetVertex(static_cast<eRectangleIndex>(j)));

				if (rectMax < scalar)
				{
					rectMax = scalar;
				}
				if (rectMin > scalar)
				{
					rectMin = scalar;
				}
			}

			float otherRectMin = std::numeric_limits<float>::max();
			float otherRectMax = -std::numeric_limits<float>::max();

			for (int j = 0; j < static_cast<int>(eRectangleIndex::Size); ++j)
			{
				float scalar = normalVector.Dot(inRectangle.GetVertex(static_cast<eRectangleIndex>(j)));

				if (otherRectMax < scalar)
				{
					otherRectMax = scalar;
				}
				if (otherRectMin > scalar)
				{
					otherRectMin = scalar;
				}
			}

			if (!(rectMin < otherRectMin && rectMax > otherRectMax))
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