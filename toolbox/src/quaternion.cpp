#include "../include/quaternion.h"
#include "../include/utility.h"
#include <algorithm>
#include <iostream>
using namespace Core::Maths;
using namespace std;

const Quaternion Quaternion::Identity = Quaternion(0.f, 0.f, 0.f, 1.f);

Quaternion::Quaternion()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
	w = 1.f;
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

Quaternion::Quaternion(const Vector4D& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

Quaternion Quaternion::Add(Quaternion q)
{
	return { x + q.x, y + q.y, z + q.z, w + q.w };
}

Quaternion Quaternion::Multiply(float f)
{
	return { x * f, y * f, z * f, w * f };
}

Quaternion Quaternion::Multiply(Quaternion q)
{
	return
	{
		w * q.x + q.w * x + (y * q.z - z * q.y),
		w * q.y + q.w * y + (z * q.x - x * q.z),
		w * q.z + q.w * z + (x * q.y - y * q.x),
		w * q.w - (x * q.x + y * q.y + z * q.z)
	};
}

Quaternion Quaternion::Qrotation(Vector3D v, float angle)
{
	v.Normalize();
	angle = TO_RADIANS(angle * 0.5f);
	float sinA = sin(angle);
	return {v.x * sinA, v.y * sinA, v.z * sinA, std::cos(angle)};
}

Quaternion Quaternion::Conjugate()
{
	return {-x, -y, -z, w};
}

Quaternion Quaternion::Opposite()
{
	return { -x, -y, -z, -w };
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

float Quaternion::Magnitude() const
{
	return Vector4D(x, y, z, w).Magnitude();
}

void Quaternion::Normalize()
{
	float norm = Magnitude();
	if (IsEqualZero(norm))
		return;

	float invNorm = 1.0f / norm;
	x *= invNorm;
	y *= invNorm;
	z *= invNorm;
	w *= invNorm;
}

Quaternion Quaternion::Normalized()
{
	return Vector4D(x, y, z, w).Normalized();
}

float Quaternion::Dot(const Quaternion& q)
{
	return x * q.x + y * q.y + z * q.z + w * q.w;
}

Matrix3x3 Quaternion::ToMatrixRot(Quaternion q)
{
	Quaternion q1 = q.Normalized();
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

Quaternion Quaternion::FromEuler(const Vector3D& eulerDeg)
{
	float xRad = TO_RADIANS(eulerDeg.x) * 0.5f;
	float yRad = TO_RADIANS(eulerDeg.y) * 0.5f;
	float zRad = TO_RADIANS(eulerDeg.z) * 0.5f;

	float cx = cosf(xRad);
	float sx = sinf(xRad);
	float cy = cosf(yRad);
	float sy = sinf(yRad);
	float cz = cosf(zRad);
	float sz = sinf(zRad);

	return Quaternion(
		sx * cy * cz - cx * sy * sz,
		cx * sy * cz + sx * cy * sz,
		cx * cy * sz - sx * sy * cz,
		cx * cy * cz + sx * sy * sz
	);
}

float Quaternion::Angle(Quaternion q)
{
	float dot = Dot(q.Normalized());
	return acosf(std::min(std::max(dot, -1.0f), 1.0f)) * 2.0f;
}

Quaternion Quaternion::Inverse() const
{
	float normSq = x * x + y * y + z * z + w * w;
	if (IsEqualZero(normSq))
		return Quaternion::Identity;

	float inv = 1.0f / normSq;
	return Quaternion(-x * inv, -y * inv, -z * inv, w * inv);
}

Quaternion Quaternion::Slerp(Quaternion q1, Quaternion q2, float t)
{
	q1 = q1.Normalized();
	q2 = q2.Normalized();

	float dot = q1.Dot(q2);

	dot = std::min(dot, 1.0f);
	dot = std::max(dot, -1.0f);

	if (dot < 0.0f)
	{
		q2 = q2.Opposite();
		dot = -dot;
	}

	if (dot > 0.9995f) {
		Quaternion result = Nlerp(q1, q2, t);
		result.Normalize();
		return result;
	}

	float omega = acos(dot);
	float sinOmega = sin(omega);
	float a = sin((1.0f - t) * omega) / sinOmega;
	float b = sin(t * omega) / sinOmega;

	return q1 * a + q2 * b;
}

Quaternion Quaternion::Nlerp(Quaternion q1, Quaternion q2, float t)
{
	return (q1 * (1-t) + q2 * t).Normalized();
}

#pragma region Operators

Quaternion Quaternion::operator+(const Quaternion& q) const
{
	return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
}

Quaternion Quaternion::operator-(const Quaternion& q) const
{
	return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
}

Quaternion Quaternion::operator*(float f) const
{
	return Quaternion(x * f, y * f, z * f, w * f);
}

#pragma endregion