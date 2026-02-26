#include "../include/vector.h"
#include "../include/matrix.h"
#include "../include/utility.h"
#include "../include/quaternion.h"
#include <iostream>

using namespace Core::Maths;

#pragma region Vector2D

const Vector2D Vector2D::Up = Vector2D(0.f, 1.f);
const Vector2D Vector2D::Down = Vector2D(0.f, -1.f);
const Vector2D Vector2D::Right = Vector2D(1.f, 0.f);
const Vector2D Vector2D::Left = Vector2D(-1.f, 0.f);
const Vector2D Vector2D::Zero = Vector2D(0.f, 0.f);
const Vector2D Vector2D::One = Vector2D(1.f, 1.f);

Vector2D::Vector2D()
    : x(0.f), y(0.f)
{}

Vector2D::Vector2D(float _x, float _y)
    : x(_x), y(_y)
{}

Vector2D::Vector2D(float n)
    : x(n), y(n)
{}


Vector2D::Vector2D(Vector2D p1, Vector2D p2)
    :x(p2.x - p1.x), y(p2.y - p1.y)
{}
Vector2D Vector2D::Opposite() const
{
    return { -x, -y };
}

Vector2D Vector2D::MidPoint(const Vector2D& v) const
{
    return Vector2D((x + v.x) / 2, (y + v.y) / 2);
}

float Vector2D::Distance(const Vector2D& v) const
{
    float dx = x - v.x;
    float dy = y - v.y;
    return std::sqrtf(dx * dx + dy * dy);
}

float Vector2D::SquaredMagnitude() const
{
    return x * x + y * y;
}

float Vector2D::Magnitude() const
{
    return std::sqrtf(SquaredMagnitude());
}

Vector2D Vector2D::Normalized() const
{
    float norm = Magnitude();
    if (IsEqualZero(norm))
        return Vector2D(0.f, 0.f);

	return Vector2D(x / norm, y / norm);
}

void Vector2D::Normalize()
{
    float norm = Magnitude();
    if (IsEqualZero(norm))
        return;

    x /= norm;
    y /= norm;
}

Vector2D Vector2D::ClampMagnitude(float maxLength) const
{
    float n = Magnitude();
    if (n > maxLength)
        return Normalized() * maxLength;
    return *this;
}

float Vector2D::DotProduct(const Vector2D& v) const
{
    return x * v.x + y * v.y;
}

float Vector2D::CrossProduct(const Vector2D& v) const
{
    return x * v.y - y * v.x;
}

float Vector2D::Angle(const Vector2D& v) const
{
    float norm = Magnitude();
    float vMagnitude = v.Magnitude();
    if (IsEqualZero(norm) || IsEqualZero(vMagnitude))
        return 0.f;

    return TO_DEGREES(std::acos(DotProduct(v) / (norm * vMagnitude)));
}

Vector2D Vector2D::Rotate(float angle) const
{
	float rad = TO_RADIANS(angle);
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    return Vector2D( x * cosA - y * sinA, x * sinA + y * cosA );
}

Vector2D Vector2D::RotateAround(float angle, const Vector2D& p) const
{
    float rad = TO_RADIANS(angle);
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    float tx = x - p.x;
    float ty = y - p.y;

    float rx = tx * cosA - ty * sinA;
    float ry = tx * sinA + ty * cosA;

    return { rx + p.x, ry + p.y };
}

Vector2D Vector2D::Translate(const Vector2D& t) const
{
    return { x + t.x, y + t.y };
}

Vector2D Vector2D::Translate(float dx, float dy) const
{
    return { x + dx, y + dy };
}

Vector2D Vector2D::Scale(float s) const
{
    return { x * s, y * s };
}

Vector2D Vector2D::Scale(const Vector2D& s) const
{
    return { x * s.x, y * s.y };
}

Vector2D Vector2D::ScaleAround(float s, const Vector2D& p) const
{
    float tx = x - p.x;
    float ty = y - p.y;

    return { tx * s + p.x, ty * s + p.y };
}

Vector2D Vector2D::ScaleAround(const Vector2D& s, const Vector2D& p) const
{
    float tx = x - p.x;
    float ty = y - p.y;

    return { tx * s.x + p.x, ty * s.y + p.y };
}

void Vector2D::Print() const
{
    std::cout << "(" << (IsEqualZero(x) ? 0.f : x) << ", " << (IsEqualZero(y) ? 0.f : y) << ")" << std::endl;
}

Vector2D Vector2D::Lerp(const Vector2D& start, const Vector2D& end, float t)
{
    return start + (end - start) * t;
}

#pragma region Vector2D Operators

Vector2D Vector2D::operator+(const Vector2D& v)
{
    return Vector2D(x + v.x, y + v.y);
}

const Vector2D& Vector2D::operator+(const Vector2D& v) const
{
	return Vector2D(this->x + v.x, this->y + v.y);
}

Vector2D Vector2D::operator-(const Vector2D& v)
{
    return Vector2D(this->x - v.x, this->y - v.y);
}

const Vector2D& Vector2D::operator-(const Vector2D& v) const
{
	return Vector2D(this->x - v.x, this->y - v.y);
}

Vector2D Vector2D::operator*(const Vector2D& v)
{
    return Vector2D(this->x * v.x, this->y * v.y);
}

const Vector2D& Vector2D::operator*(const Vector2D& v) const
{
	return Vector2D(this->x * v.x, this->y * v.y);
}

Vector2D Vector2D::operator/(const Vector2D& v)
{
    return Vector2D(IsEqualZero(v.x) ? 0.f : this->x / v.x, IsEqualZero(v.y) ? 0.f : this->y / v.y);
}

const Vector2D& Vector2D::operator/(const Vector2D& v) const
{
	return Vector2D(IsEqualZero(v.x) ? 0.f : this->x / v.x, IsEqualZero(v.y) ? 0.f : this->y / v.y);
}

void Vector2D::operator+=(const Vector2D& v)
{
	x += v.x;
	y += v.y;
}

void Vector2D::operator-=(const Vector2D& v)
{
	x -= v.x;
	y -= v.y;
}

void Vector2D::operator*=(const Vector2D& v)
{
	x *= v.x;
	y *= v.y;
}

void Vector2D::operator/=(const Vector2D& v)
{
	IsEqualZero(v.x) ? x = 0.f : x /= v.x;
    IsEqualZero(v.y) ? y = 0.f : y /= v.y;
}

Vector2D Vector2D::operator+(const float f)
{
    return Vector2D(x + f, y + f);
}

const Vector2D& Vector2D::operator+(const float f) const
{
    return Vector2D(x + f, y + f);
}

Vector2D Vector2D::operator-(const float f)
{
    return Vector2D(x - f, y - f);
}

const Vector2D& Vector2D::operator-(const float f) const
{
    return Vector2D(x - f, y - f);
}

Vector2D Vector2D::operator*(const float f)
{
    return Vector2D(x * f, y * f);
}

const Vector2D& Vector2D::operator*(const float f) const
{
	return Vector2D(x * f, y * f);
}

Vector2D Vector2D::operator/(const float f)
{
    Vector2D r;
    IsEqualZero(f) ? r = Vector2D::Zero : r = Vector2D(x / f, y / f);
    return r;
}

const Vector2D& Vector2D::operator/(const float f) const
{
    Vector2D r;
    IsEqualZero(f) ? r = Vector2D::Zero : r = Vector2D(x / f, y / f);
    return r;
}

void Vector2D::operator+=(const float f)
{
	x += f;
	y += f;
}

void Vector2D::operator-=(const float f)
{
	x -= f;
	y -= f;
}

void Vector2D::operator*=(const float f)
{
	x *= f;
	y *= f;
}

void Vector2D::operator/=(const float f)
{
    IsEqualZero(f) ? x = 0.f : x /= f;
	IsEqualZero(f) ? y = 0.f : y /= f;
}

float& Vector2D::operator[](int index)
{
	return index == 0 ? x : y;
}

const float& Vector2D::operator[](int index) const
{
    return index == 0 ? x : y;
}

bool Vector2D::operator==(const Vector2D& v) const
{
    return IsEqual(x, v.x) && IsEqual(y, v.y);
}

Vector2D Vector2D::operator-()
{
	return Opposite();
}

const Vector2D& Vector2D::operator-() const
{
    return Opposite();
}

#pragma endregion

#pragma endregion

#pragma region Vector3D

const Vector3D Vector3D::Up = Vector3D(0.f, 1.f, 0.f);
const Vector3D Vector3D::Down = Vector3D(0.f, -1.f, 0.f);
const Vector3D Vector3D::Right = Vector3D(1.f, 0.f, 0.f);
const Vector3D Vector3D::Left = Vector3D(-1.f, 0.f, 0.f);
const Vector3D Vector3D::Zero = Vector3D(0.f, 0.f, 0.f);
const Vector3D Vector3D::One = Vector3D(1.f, 1.f, 1.f);

Vector3D::Vector3D()
    :x(0.f), y(0.f), z(0.f)
{}

Vector3D::Vector3D(float _x, float _y, float _z)
    : x(_x), y(_y), z(_z)
{}

Vector3D::Vector3D(float n)
    :x(n), y(n), z(n)
{}

Vector3D::Vector3D(Vector3D p1, Vector3D p2)
    :x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z)
{}

Vector3D Vector3D::Opposite() const
{
    return Vector3D(-x, -y, -z);
}

Vector3D Vector3D::MidPoint(const Vector3D& v) const
{
    return Vector3D((x + v.x) / 2, (y + v.y) / 2, (z + v.z) / 2);
}

float Vector3D::Distance(const Vector3D& v) const
{
    float dx = x - v.x;
    float dy = y - v.y;
    float dz = z - v.z;
    return std::sqrtf(dx * dx + dy * dy + dz * dz);
}

float Vector3D::SquaredMagnitude() const
{
    return x * x + y * y + z * z;
}

float Vector3D::Magnitude() const
{
    return std::sqrtf(SquaredMagnitude());
}

Vector3D Vector3D::Normalized() const
{
    float norm = Magnitude();
    if (IsEqualZero(norm))
        return *this;

    return Vector3D(x / norm, y / norm, z / norm);
}

void Vector3D::Normalize()
{
    float norm = Magnitude();
    if (IsEqualZero(norm))
        return;

    x /= norm;
    y /= norm;
	z /= norm;
}

float Vector3D::DotProduct(const Vector3D& v) const
{
    return x * v.x + y * v.y + z * v.z;
}

Vector3D Vector3D::CrossProduct(const Vector3D& v) const
{
    return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

float Vector3D::Angle(const Vector3D& v) const
{
    float norm = Magnitude();
    float vMagnitude = v.Magnitude();
    if (IsEqualZero(norm) || IsEqualZero(vMagnitude))
        return 0.f;

    return TO_DEGREES(std::acos(DotProduct(v) / (norm * vMagnitude)));
}

Vector3D Vector3D::GetSafeUpVector(Vector3D dir) 
{
    if (std::abs(dir.x) < 0.99f) 
        return Vector3D(1.0f, 0.0f, 0.0f);

    if (std::abs(dir.y) < 0.99f) 
        return Vector3D(0.0f, 1.0f, 0.0f);

    return Vector3D(0.0f, 0.0f, 1.0f);
}

void Vector3D::Print() const
{
    std::cout << "(" << (IsEqualZero(x) ? 0.f : x) << ", " << (IsEqualZero(y) ? 0.f : y) << ", " << (IsEqualZero(z) ? 0.f : z) << ")" << std::endl;
}

Vector3D Vector3D::ClampMagnitude(float max) const
{
    float n = Magnitude();
    if (n > max)
        return Normalized() * max;
    return *this;
}

Vector3D Vector3D::Translate(const Vector3D& t) const
{
    return { x + t.x, y + t.y, z + t.z };
}

Vector3D Vector3D::Translate(float dx, float dy, float dz) const
{
    return { x + dx, y + dy, z + dz };
}

Vector3D Vector3D::Rotate(float angle, const Vector3D& axe) const
{
    Quaternion q = Quaternion::FromAxisAngle(axe, angle);
    return q.RotateVector(*this);
}

Vector3D Vector3D::Rotate(const Quaternion& q) const
{
    return q.RotateVector(*this);
}

Vector3D Vector3D::RotateAround(float angle, const Vector3D& axis, const Vector3D& p) const
{
    Quaternion q = Quaternion::FromAxisAngle(axis, angle);

    Vector3D translated = *this - p;
    Vector3D rotated = q.RotateVector(translated);

    return rotated + p;
}

Vector3D Vector3D::RotateAround(const Quaternion& q, const Vector3D& p) const
{
    Vector3D translated = *this - p;
    Vector3D rotated = q.RotateVector(translated);
    return rotated + p;
}

Vector3D Vector3D::Scale(float s) const
{
    return { x * s, y * s, z * s };
}

Vector3D Vector3D::Scale(const Vector3D& v) const
{
    return { x * v.x, y * v.y, z * v.z };
}

Vector3D Vector3D::ScaleAround(float s, const Vector3D& p) const
{
    Vector3D t = *this - p;
    return t * s + p;
}

Vector3D Vector3D::ScaleAround(const Vector3D& s, const Vector3D& p) const
{
    Vector3D t = *this - p;
    return t * s + p;
}


Vector3D Vector3D::Lerp(const Vector3D& start, const Vector3D& end, float t)
{
    return start + (end - start) * t;
}

#pragma region Vector3D Operators

Vector3D Vector3D::operator-()
{
	return Opposite();
}

const Vector3D& Vector3D::operator-() const
{
    return Opposite();
}

Vector3D Vector3D::operator+(const Vector3D& v)
{
    return {x + v.x, y + v.y, z + v.z};
}

Vector3D Vector3D::operator-(const Vector3D& v)
{
    return { x - v.x, y - v.y, z - v.z };
}

Vector3D Vector3D::operator*(const Vector3D& v)
{
    return { x * v.x, y * v.y, z * v.z };
}

Vector3D Vector3D::operator/(const Vector3D& v)
{
    return { IsEqualZero(v.x) ? 0.f : x / v.x, IsEqualZero(v.y) ? 0.f : y / v.y, IsEqualZero(v.z) ? 0.f : z / v.z };
}

const Vector3D& Vector3D::operator+(const Vector3D& v) const
{
    return { x + v.x, y + v.y, z + v.z };
}

const Vector3D& Vector3D::operator-(const Vector3D& v) const
{
    return { x - v.x, y - v.y, z - v.z };
}

const Vector3D& Vector3D::operator*(const Vector3D& v) const
{
    return { x * v.x, y * v.y, z * v.z };
}

const Vector3D& Vector3D::operator/(const Vector3D& v) const
{
    return { (IsEqualZero(v.x) ? 0.f : x / v.x), (IsEqualZero(v.y) ? 0.f : y / v.y), (IsEqualZero(v.z) ? 0.f : z / v.z) };
}

void Vector3D::operator+=(const Vector3D& v)
{
    *this = { x + v.x, y + v.y, z + v.z };
}

void Vector3D::operator-=(const Vector3D& v)
{
    *this = { x - v.x, y - v.y, z - v.z };
}

void Vector3D::operator*=(const Vector3D& v)
{
    *this = { x * v.x, y * v.y, z * v.z };
}

void Vector3D::operator/=(const Vector3D& v)
{
    *this = { IsEqualZero(v.x) ? 0.f : x / v.x, IsEqualZero(v.y) ? 0.f : y / v.y, IsEqualZero(v.z) ? 0.f : z / v.z };
}

Vector3D Vector3D::operator+(const float f)
{
    return { x + f, y + f, z + f };
}

Vector3D Vector3D::operator-(const float f)
{
    return { x - f, y - f, z - f };
}

Vector3D Vector3D::operator*(const float f)
{
    return { x * f, y * f, z * f };
}

Vector3D Vector3D::operator/(const float f)
{
    Vector3D r;
	IsEqualZero(f) ? r = Vector3D::Zero : r = Vector3D(x / f, y / f, z / f);
    return r;
}

const Vector3D& Vector3D::operator+(const float f) const
{
    return { x + f, y + f, z + f };
}

const Vector3D& Vector3D::operator-(const float f) const
{
    return { x - f, y - f, z - f };
}

const Vector3D& Vector3D::operator*(const float f) const
{
    return { x * f, y * f, z * f };
}

const Vector3D& Vector3D::operator/(const float f) const
{
    return { x / f, y / f, z / f };
}

void Vector3D::operator+=(const float f)
{
    x += f;
    y += f;
    z += f;
}

void Vector3D::operator-=(const float f)
{
    x -= f;
    y -= f;
    z -= f;
}

void Vector3D::operator*=(const float f)
{
    x *= f;
    y *= f;
    z *= f;
}

void Vector3D::operator/=(const float f)
{
    Vector3D r;
    IsEqualZero(f) ? *this = Vector3D::Zero : *this = Vector3D(x / f, y / f, z / f);
}

float& Vector3D::operator[](int index)
{
    switch (index)
    {
    case 0:
        return x;
        break;
    case 1:
        return y;
        break;
    default:
        return z;
        break;
    }
}

const float& Vector3D::operator[](int index) const
{
    switch (index)
    {
    case 0:
        return x;
        break;
    case 1:
        return y;
        break;
    default:
        return z;
        break;
    }
}

bool Vector3D::operator==(const Vector3D& v) const
{
    return IsEqual(x, v.x) && IsEqual(y, v.y) && IsEqual(z, v.z);
}

#pragma endregion

#pragma endregion

#pragma region Vector4D

const Vector4D Vector4D::Zero = Vector4D(0.f, 0.f, 0.f, 0.f);
const Vector4D Vector4D::One = Vector4D(1.f, 1.f, 1.f, 1.f);

Vector4D::Vector4D()
    :x(0.f), y(0.f), z(0.f), w(0.f)
{
}

Vector4D::Vector4D(float _x, float _y, float _z, float _w)
    : x(_x), y(_y), z(_z), w(_w)
{}

Vector4D::Vector4D(const Vector3D& v, float _w) 
    : x(v.x), y(v.y), z(v.z), w(_w)
{}

Vector4D Vector4D::Opposite() const
{
    return Vector4D(-x, -y, -z, -w);
}

Vector4D Vector4D::MidPoint(const Vector4D& v) const
{
    return Vector4D((x + v.x) / 2, (y + v.y) / 2, (z + v.z) / 2, (w + v.w) / 2);
}

Vector4D Vector4D::Lerp(const Vector4D& start, const Vector4D& end, float t)
{
    return start + (end - start) * t;
}

float Vector4D::Distance(const Vector4D& v) const
{
    return std::sqrtf(std::powf(x - v.x, 2) + std::powf(y - v.y, 2) + std::powf(z - v.z, 2) + std::powf(w - v.w, 2));
}

float Vector4D::SquaredMagnitude() const
{
    return x * x + y * y + z * z + w * w;
}

float Vector4D::Magnitude() const
{
    return std::sqrtf(SquaredMagnitude());
}

float Vector4D::DotProduct(const Vector4D& v) const
{
    return x * v.x + y * v.y + z * v.z + w * v.w;
}

void Vector4D::Print() const
{
    std::cout << "(" << (IsEqualZero(x) ? 0.f : x) << ", " << (IsEqualZero(y) ? 0.f : y) << ", " << (IsEqualZero(z) ? 0.f : z) << ", " << (IsEqualZero(w) ? 0.f : w) << ")" << std::endl;
}

#pragma region Vector4D Operators

Vector4D Vector4D::operator+(const Vector4D& v)
{
    return { x + v.x, y + v.y, z + v.z, w + v.w };
}

Vector4D Vector4D::operator-(const Vector4D& v)
{
    return { x - v.x, y - v.y, z - v.z, w - v.w };
}

Vector4D Vector4D::operator*(const Vector4D& v)
{
    return { x * v.x, y * v.y, z * v.z, w * v.w };
}

Vector4D Vector4D::operator/(const Vector4D& v)
{
    return { 
        (IsEqualZero(v.x) ? 0.f : x / v.x), 
        (IsEqualZero(v.y) ? 0.f : y / v.y),
        (IsEqualZero(v.z) ? 0.f : z / v.z),
        (IsEqualZero(v.w) ? 0.f : w / v.w)
    };
}

const Vector4D Vector4D::operator+(const Vector4D& v) const
{
    return { x + v.x, y + v.y, z + v.z, w + v.w };
}

const Vector4D Vector4D::operator-(const Vector4D& v) const
{
    return { x - v.x, y - v.y, z - v.z, w - v.w };
}

const Vector4D Vector4D::operator*(const Vector4D& v) const
{
    return { x * v.x, y * v.y, z * v.z, w * v.w };
}

const Vector4D Vector4D::operator/(const Vector4D& v) const
{
    return {
        (IsEqualZero(v.x) ? 0.f : x / v.x),
        (IsEqualZero(v.y) ? 0.f : y / v.y),
        (IsEqualZero(v.z) ? 0.f : z / v.z),
        (IsEqualZero(v.w) ? 0.f : w / v.w)
    };
}

void Vector4D::operator+=(const Vector4D& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
}

void Vector4D::operator-=(const Vector4D& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
}

void Vector4D::operator*=(const Vector4D& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
}

void Vector4D::operator/=(const Vector4D& v)
{
    IsEqualZero(v.x) ? 0.f : x /= v.x;
    IsEqualZero(v.y) ? 0.f : y /= v.y;
    IsEqualZero(v.z) ? 0.f : z /= v.z;
    IsEqualZero(v.w) ? 0.f : w /= v.w;
}

Vector4D Vector4D::operator+(const float f)
{
    return { x + f, y + f, z + f, w + f };
}

Vector4D Vector4D::operator-(const float f)
{
    return { x - f, y - f, z - f, w - f };
}

Vector4D Vector4D::operator*(const float f)
{
    return { x * f, y * f, z * f, w * f };
}

Vector4D Vector4D::operator/(const float f)
{
    Vector4D r{};
    IsEqualZero(f) ? r = Vector4D::Zero : r = Vector4D(x / f, y / f, z / f, w / f);
    return r;
}

const Vector4D Vector4D::operator+(const float f) const
{
    return { x + f, y + f, z + f, w + f };
}

const Vector4D Vector4D::operator-(const float f) const
{
    return { x - f, y - f, z - f, w - f };
}

const Vector4D Vector4D::operator*(const float f) const
{
    return { x * f, y * f, z * f, w * f };
}

const Vector4D Vector4D::operator/(const float f) const
{
    Vector4D r{};
    IsEqualZero(f) ? r = Vector4D::Zero : r = Vector4D(x / f, y / f, z / f, w / f);
    return r;
}

void Vector4D::operator+=(const float f)
{
    x += f;
    y += f;
    z += f;
    w += f;
}

void Vector4D::operator-=(const float f)
{
    x -= f;
    y -= f;
    z -= f;
    w -= f;
}

void Vector4D::operator*=(const float f)
{
    x *= f;
    y *= f;
    z *= f;
    w *= f;
}

void Vector4D::operator/=(const float f)
{
    IsEqualZero(f) ? *this = Vector4D::Zero : Vector4D(x += f, y += f, z += f, w += f);
}

Vector4D Vector4D::operator-()
{
    return Opposite();
}

const Vector4D& Vector4D::operator-() const
{
    return Opposite();
}

float& Vector4D::operator[](int index)
{
    switch (index)
    {
    case 0:
        return x;
        break;
    case 1:
        return y;
        break;
    case 2:
        return z;
        break;
    default:
        return w;
        break;
    }
}

const float& Vector4D::operator[](int index) const
{
    switch (index)
    {
    case 0:
        return x;
        break;
    case 1:
        return y;
        break;
    case 2:
        return z;
        break;
    default:
        return w;
        break;
    }
}

bool Vector4D::operator==(const Vector4D& v) const
{
    return IsEqual(x, v.x) && IsEqual(y, v.y) && IsEqual(z, v.z) && IsEqual(w, v.w);
}

#pragma endregion

#pragma endregion