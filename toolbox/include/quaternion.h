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
			static Quaternion Qadd(Quaternion q1, Quaternion q2);
			static Quaternion Qmultiply(Quaternion q1, float f);
			static Quaternion Qmultiply(Quaternion q1, Quaternion q2);
			static Quaternion Qrotation(Vector3D v, float angle);
			static Quaternion Qconjugate(Quaternion q);
			static Quaternion Qopposite(Quaternion q);
			Vector3D RotateVector(const Vector3D& v) const;
			static Quaternion FromAxisAngle(const Vector3D& axis, float angleDeg);
		
			void Normalize();
			static Quaternion Normalize(Quaternion q);
			static float Dot(const Quaternion& q1, const Quaternion& q2);

			static Matrix3x3 ToMatrixRot(Quaternion q);

			static Quaternion Slerp(Quaternion q1, Quaternion q2, float t);
			static Quaternion Nlerp(Quaternion q1, Quaternion q2, float t);

			Quaternion operator+(const Quaternion& q);
			Quaternion operator-(const Quaternion& q);
			Quaternion operator*(float f);
			Quaternion operator*(Quaternion& q);
		private:
		};
	}
}