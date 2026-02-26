#include "../include/quaternion.h"
#include "../include/utility.h"
#include <algorithm>
#include <iostream>
using namespace Core::Maths;
using namespace std;

Quaternion::Quaternion()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
	w = 0.f;
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

Quaternion Quaternion::Qadd(Quaternion q1, Quaternion q2)
{
	return { q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w };
}

Quaternion Quaternion::Qmultiply(Quaternion q1, float f)
{
	return { q1.x * f, q1.y * f, q1.z * f, q1.w * f };
}

Quaternion Quaternion::Qmultiply(Quaternion q1, Quaternion q2)
{
	return
	{
		q1.w * q2.x + q2.w * q1.x + (q1.y * q2.z - q1.z * q2.y),
		q1.w * q2.y + q2.w * q1.y + (q1.z * q2.x - q1.x * q2.z),
		q1.w * q2.z + q2.w * q1.z + (q1.x * q2.y - q1.y * q2.x),
		q1.w * q2.w - (q1.x * q2.x + q1.y * q2.y + q1.z * q2.z)
	};
}

Quaternion Quaternion::Qrotation(Vector3D v, float angle)
{
	angle = angle * 0.5f * 3.1415927f / 180.f;
	float sinA = sinf(angle);
	return {v.x * sinA, v.y * sinA, v.z * sinA, std::cosf(angle)};
}

Quaternion Quaternion::Qconjugate(Quaternion q)
{
	return {-q.x, -q.y, -q.z, q.w};
}

Quaternion Quaternion::Qopposite(Quaternion q)
{
	return { -q.x, -q.y, -q.z, -q.w };
}

Vector3D Quaternion::RotateVector(const Vector3D& v) const
{
	Quaternion q = *this;
	q.Normalize();

	Vector3D qVec(q.x, q.y, q.z);

	Vector3D t = qVec.CrossProduct(v) * 2.0f;
	return v + t * q.w + qVec.CrossProduct(t);
}

Quaternion Quaternion::FromAxisAngle(const Vector3D& axis, float angleDeg)
{
	float rad = TO_RADIANS(angleDeg);
	float half = rad * 0.5f;

	float sinHalf = std::sin(half);
	float cosHalf = std::cos(half);

	Vector3D n = axis.Normalized();

	return Quaternion(n.x * sinHalf, n.y * sinHalf, n.z * sinHalf, cosHalf);
}

void Quaternion::Normalize()
{
	float norm = sqrtf(w * w + x * x + y * y + z * z);
	x /= norm;
	y /= norm;
	z /= norm;
	w /= norm;
}

Quaternion Quaternion::Normalize(Quaternion q)
{
	float norm = sqrtf(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	return {q.x / norm, q.y / norm, q.z / norm, q.w / norm};
}

float Quaternion::Dot(const Quaternion& q1, const Quaternion& q2)
{
	return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}

Matrix3x3 Quaternion::ToMatrixRot(Quaternion q)
{
	Quaternion q1 = Normalize(q);
	Matrix3x3 m(
		1 - 2 * (q1.y * q1.y + q1.z * q1.z),
		2 * (q1.x * q1.y - q1.z * q1.w),
		2 * (q1.x * q1.z + q1.y * q1.w),

		2 * (q1.x * q1.y + q1.z * q1.w),
		1 - 2 * (q1.x * q1.x + q1.z * q1.z),
		2 * (q1.y * q1.z - q1.x * q1.w),

		2 * (q1.x * q1.z - q1.y * q1.w),
		2 * (q1.y * q1.z + q1.x * q1.w),
		1 - 2 * (q1.x * q1.x + q1.y * q1.y)
	);
	return m;
}

Quaternion Quaternion::Slerp(Quaternion q1, Quaternion q2, float t)
{
	float dot = Dot(q1, q2);

	dot = std::min(dot, 1.0f);
	dot = std::max(dot, -1.0f);

	if (dot < 0.0f)
	{
		q2 = Qopposite(q2);
		dot = -dot;
	}

	if (dot > 0.9995f) {
		Quaternion result = Nlerp(q1, q2, t);
		result.Normalize();
		return result;
	}

	float omega = acosf(dot);
	float sinOmega = sinf(omega);
	float a = sinf((1.0f - t) * omega) / sinOmega;
	float b = sinf(t * omega) / sinOmega;

	return q1 * a + q2 * b;
}

Quaternion Quaternion::Nlerp(Quaternion q1, Quaternion q2, float t)
{
	return q1 * (1-t) + q2 * t;
}

#pragma region Operators
Quaternion Quaternion::operator+(const Quaternion& q)
{
	return Quaternion(q.x + x, q.y + y, q.z + z, q.w + w);
}

Quaternion Quaternion::operator-(const Quaternion& q)
{
	return Quaternion(q.x - x, q.y - y, q.z - z, q.w - w);
}

Quaternion Quaternion::operator*(Quaternion& q)
{
	return Quaternion(q.x * x, q.y * y, q.z * z, q.w * w);
}

Quaternion Quaternion::operator*(float f)
{
	return Quaternion(f * x, f * y, f * z, f * w);
}
#pragma endregion