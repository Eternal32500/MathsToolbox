#pragma once

#include "vector.h"
#include "matrix.h"

namespace Core
{
	namespace Maths
	{
		class Quaternion
		{
		public:
			float w;
			float x;
			float y;
			float z;

			Quaternion();
			Quaternion(float _x, float _y, float _z, float _w);
			Quaternion(const Vector4D& v);

			void Normalize();
			float Magnitude() const;
			float Dot(const Quaternion& q2) const;
			float Angle(Quaternion q);
			Quaternion Opposite();
			Quaternion Conjugate();
			Quaternion Normalized();
			Quaternion Inverse() const;

			Quaternion Add(Quaternion q);
			Quaternion Multiply(float f);
			Quaternion Multiply(Quaternion q2);
			Vector3D RotateVector(const Vector3D& v) const;

			static Quaternion Qrotation(Vector3D v, float angle);
			static Quaternion FromAxisAngle(const Vector3D& axis, float angleDeg);
			static Matrix3x3 ToMatrixRot(Quaternion q);
			static Quaternion FromEuler(const Vector3D& eulerDeg);
			static Quaternion Slerp(Quaternion q1, Quaternion q2, float t);
			static Quaternion Nlerp(Quaternion q1, Quaternion q2, float t);

			Quaternion operator+(const Quaternion& q) const;
			Quaternion operator-(const Quaternion& q) const;
			Quaternion operator*(float f) const;

			Quaternion operator-();

			static const Quaternion Identity;
		};
	}
}