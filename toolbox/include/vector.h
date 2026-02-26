#pragma once

#include <vector>

namespace Core
{
	namespace Maths
	{
		class Quaternion;

		bool IsEqualZero(float num);
		bool IsEqual(float a, float b);

		class Vector2D
		{
		public:
			float x;
			float y;

			Vector2D();
			Vector2D(float _x, float _y);
			Vector2D(float n);
			Vector2D(Vector2D p1, Vector2D p2);
			~Vector2D() = default;

			void Print() const;
			void Normalize();
			float Distance(const Vector2D& v) const;
			float SquaredMagnitude() const;
			float Magnitude() const;
			float DotProduct(const Vector2D& v) const;
			float CrossProduct(const Vector2D& v) const;
			float Angle(const Vector2D& v) const;
			Vector2D MidPoint(const Vector2D& v) const;
			Vector2D Normalized() const;
			Vector2D ClampMagnitude(float maxLength) const;
			Vector2D Translate(const Vector2D& t) const;
			Vector2D Translate(float dx, float dy) const;
			Vector2D Rotate(float angle) const;
			Vector2D RotateAround(float angle, const Vector2D& p) const;
			Vector2D Scale(float s) const;
			Vector2D Scale(const Vector2D& s) const;
			Vector2D ScaleAround(float s, const Vector2D& p) const;
			Vector2D ScaleAround(const Vector2D& s, const Vector2D& p) const;
			static Vector2D Lerp(const Vector2D& start, const Vector2D& end, float t);

			Vector2D operator+(const Vector2D& v);
			Vector2D operator-(const Vector2D& v);
			Vector2D operator*(const Vector2D& v);
			Vector2D operator/(const Vector2D& v);
			const Vector2D& operator+(const Vector2D& v) const;
			const Vector2D& operator-(const Vector2D& v) const;
			const Vector2D& operator*(const Vector2D& v) const;
			const Vector2D& operator/(const Vector2D& v) const;

			void operator+=(const Vector2D& v);
			void operator-=(const Vector2D& v);
			void operator*=(const Vector2D& v);
			void operator/=(const Vector2D& v);

			Vector2D operator+(const float f);
			Vector2D operator-(const float f);
			Vector2D operator*(const float f);
			Vector2D operator/(const float f);
			const Vector2D& operator+(const float f) const;
			const Vector2D& operator-(const float f) const;
			const Vector2D& operator*(const float f) const;
			const Vector2D& operator/(const float f) const;

			void operator+=(const float f);
			void operator-=(const float f);
			void operator*=(const float f);
			void operator/=(const float f);

			Vector2D operator-();
			const Vector2D& operator-() const;

			float& operator[](int index);
			const float& operator[](int index) const;

			bool operator==(const Vector2D& v) const;

			static const Vector2D Zero;
			static const Vector2D One;
			static const Vector2D Up;
			static const Vector2D Down;
			static const Vector2D Left;
			static const Vector2D Right;
		};

		class Vector3D
		{
		public:
			float x;
			float y;
			float z;

			Vector3D();
			Vector3D(float _x, float _y, float _z);
			Vector3D(float n);
			Vector3D(Vector3D p1, Vector3D p2);
			~Vector3D() = default;

			void Print() const;
			void Normalize();
			float Distance(const Vector3D& v) const;
			float SquaredMagnitude() const;
			float Magnitude() const;
			float DotProduct(const Vector3D& v) const;
			float Angle(const Vector3D& v) const;
			Vector3D Opposite() const;
			Vector3D MidPoint(const Vector3D& v) const;
			Vector3D Normalized() const;
			Vector3D CrossProduct(const Vector3D& v) const;
			static Vector3D GetSafeUpVector(Vector3D dir);

			Vector3D ClampMagnitude(float max) const;
			Vector3D Translate(const Vector3D& t) const;
			Vector3D Translate(float dx, float dy, float dz) const;
			Vector3D Rotate(float angle, const Vector3D& axe) const;
			Vector3D Rotate(const Quaternion& q) const;
			Vector3D RotateAround(float angle, const Vector3D& axe, const Vector3D& p) const;
			Vector3D RotateAround(const Quaternion& q, const Vector3D& p) const;
			Vector3D Scale(float s) const;
			Vector3D Scale(const Vector3D& s) const;
			Vector3D ScaleAround(float s, const Vector3D& p) const;
			Vector3D ScaleAround(const Vector3D& s, const Vector3D& p) const;
			static Vector3D Lerp(const Vector3D& start, const Vector3D& end, float t);

			Vector3D operator+(const Vector3D& v);
			Vector3D operator-(const Vector3D& v);
			Vector3D operator*(const Vector3D& v);
			Vector3D operator/(const Vector3D& v);
			const Vector3D& operator+(const Vector3D& v) const;
			const Vector3D& operator-(const Vector3D& v) const;
			const Vector3D& operator*(const Vector3D& v) const;
			const Vector3D& operator/(const Vector3D& v) const;

			void operator+=(const Vector3D& v);
			void operator-=(const Vector3D& v);
			void operator*=(const Vector3D& v);
			void operator/=(const Vector3D& v);

			Vector3D operator+(const float f);
			Vector3D operator-(const float f);
			Vector3D operator*(const float f);
			Vector3D operator/(const float f);
			const Vector3D& operator+(const float f) const;
			const Vector3D& operator-(const float f) const;
			const Vector3D& operator*(const float f) const;
			const Vector3D& operator/(const float f) const;

			void operator+=(const float f);
			void operator-=(const float f);
			void operator*=(const float f);
			void operator/=(const float f);

			Vector3D operator-();
			const Vector3D& operator-() const;

			float& operator[](int index);
			const float& operator[](int index) const;
			bool operator==(const Vector3D& v) const;

			static const Vector3D Zero;
			static const Vector3D One;
			static const Vector3D Up;
			static const Vector3D Down;
			static const Vector3D Left;
			static const Vector3D Right;
		};

		class Vector4D
		{
		public:
			float x = 0.f;
			float y = 0.f;
			float z = 0.f;
			float w = 0.f;

			Vector4D() = default;
			Vector4D(float _x, float _y, float _z, float _w);
			Vector4D(const Vector3D& v, float _w);
			~Vector4D() = default;

			void Print() const;
			float Distance(const Vector4D& v) const;
			float SquaredMagnitude() const;
			float Magnitude() const;
			float DotProduct(const Vector4D& v) const;
			Vector4D Opposite() const;
			Vector4D MidPoint(const Vector4D& v) const;

			Vector4D operator+(const Vector4D& v);
			Vector4D operator-(const Vector4D& v);
			Vector4D operator*(const Vector4D& v);
			Vector4D operator/(const Vector4D& v);

			void operator+=(const Vector4D& v);
			void operator-=(const Vector4D& v);
			void operator*=(const Vector4D& v);
			void operator/=(const Vector4D& v);

			Vector4D operator+(const float f);
			Vector4D operator-(const float f);
			Vector4D operator*(const float f);
			Vector4D operator/(const float f);

			void operator+=(const float f);
			void operator-=(const float f);
			void operator*=(const float f);
			void operator/=(const float f);

			float& operator[](int index);
			const float& operator[](int index) const;

			static const Vector4D Zero;
			static const Vector4D One;
		};

		class VectorND
		{
		public:
			std::vector<float> coordinates;

			VectorND(std::vector<float> _coordinates);
			~VectorND() = default;

			VectorND Opposite() const;
			VectorND MidPoint(const VectorND& v) const;
			float Distance(const VectorND& v) const;
			float SquaredMagnitude() const;
			float Magnitude() const;
			float DotProduct(const VectorND& v) const;
			int GetSize() const;
			void Print() const;

			VectorND operator+(const VectorND& v);
			VectorND operator-(const VectorND& v);
			VectorND operator*(const VectorND& v);
			VectorND operator/(const VectorND& v);

			void operator+=(const VectorND& v);
			void operator-=(const VectorND& v);
			void operator*=(const VectorND& v);
			void operator/=(const VectorND& v);

			VectorND operator+(const float f);
			VectorND operator-(const float f);
			VectorND operator*(const float f);
			VectorND operator/(const float f);

			void operator+=(const float f);
			void operator-=(const float f);
			void operator*=(const float f);
			void operator/=(const float f);

			float& operator[](int index);
			const float& operator[](int index) const;

		private:
			int size = 0;
		};
	}
}