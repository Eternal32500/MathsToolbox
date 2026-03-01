#pragma once

namespace Core
{
	namespace Maths
	{
		#define TO_RADIANS(x) ((x) * PI / 180.0f)
		#define TO_DEGREES(x) ((x) * 180.0f / PI)

		constexpr auto PI = 3.14159265358979323846f;
		constexpr auto tolerance = 1e-8f;

		bool IsEqualZero(float num);
		bool IsEqual(float a, float b);
	}
}
