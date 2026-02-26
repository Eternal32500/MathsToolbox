#pragma once

namespace Core
{
	namespace Maths
	{
		constexpr auto PI = 3.14159265358979323846f;
		constexpr auto tolerance = 1e-6f;

		#define TO_RADIANS(x) ((x) * PI / 180.0f)
		#define TO_DEGREES(x) ((x) * 180.0f / PI)
	}
}
