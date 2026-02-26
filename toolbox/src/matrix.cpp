#include "../include/matrix.h"
#include "../include/utility.h"
#include <iostream>

using namespace Core::Maths;
#pragma region Matrix2x2

const Matrix2x2 Matrix2x2::Identity = Matrix2x2(1.0f, 0.0f, 1.0f, 0.0f);
const Matrix2x2 Matrix2x2::Zero = Matrix2x2(0.0f, 0.0f, 0.0f, 0.0f);

Matrix2x2::Matrix2x2()
{
    m[0] = 0.0f;
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 0.0f;

    RoundMatrix();
}
Matrix2x2::Matrix2x2(float _m[4])
{
    m[0] = _m[0];
    m[1] = _m[1];
    m[2] = _m[2];
    m[3] = _m[3];

    RoundMatrix();
}

Matrix2x2::Matrix2x2(std::vector<float> vertex)
{
    m[0] = vertex[0];
    m[1] = vertex[1];
    m[2] = vertex[2];
    m[3] = vertex[3];

    RoundMatrix();
}

Matrix2x2::Matrix2x2(const Vector2D& v1, const Vector2D& v2)
{
    m[0] = v1[0];
    m[1] = v1[1];
    m[2] = v2[0];
    m[3] = v2[1];

    RoundMatrix();
}

Matrix2x2::Matrix2x2(float n1, float n2, float n3, float n4)
{
    m[0] = n1;
    m[1] = n2;
    m[2] = n3;
    m[3] = n4;

    RoundMatrix();
}

Matrix2x2::Matrix2x2(float components)
{
    m[0] = components;
    m[1] = components;
    m[2] = components;
    m[3] = components;

    RoundMatrix();
}

Vector2D Matrix2x2::Diagonal() const
{
    return Vector2D(m[0], m[3]);
}

float Matrix2x2::Trace() const
{
    return m[0] + m [3];
}

Matrix2x2 Matrix2x2::Opposite() const
{
    return {
        -m[0], -m[1],
        -m[2], -m[3]
    };
}

Matrix2x2 Matrix2x2::Transposite() const
{
    return {
        m[0], m[2],
        m[1], m[3]
    };
}

Matrix2x2 Matrix2x2::AddMatrix(const Matrix2x2& mat) const
{
    return {
        m[0] + mat.m[0], m[1] + mat.m[1],
        m[2] + mat.m[2], m[3] + mat.m[3]
    };
}

Matrix2x2 Matrix2x2::AddMatrix(const MatrixND& mat) const
{
    if (mat.lines != 2 || mat.columns != 2)
        return Matrix2x2::Zero;

    return {
        m[0] + mat.m[0], m[1] + mat.m[1],
        m[2] + mat.m[2], m[3] + mat.m[3]
    };
}

Matrix2x2 Matrix2x2::MultiplyScalar(float f) const
{
    return {
        m[0] * f, m[1] * f,
        m[2] * f, m[3] * f
    };
}

Matrix2x2 Matrix2x2::MultiplyMatrix(const Matrix2x2& mat) const
{
    return {
         m[0] * mat.m[0] + m[1] * mat.m[2],
         m[0] * mat.m[1] + m[1] * mat.m[3],
         m[2] * mat.m[0] + m[3] * mat.m[2],
         m[2] * mat.m[1] + m[3] * mat.m[3]
    }; 
}

MatrixND Matrix2x2::MultiplyMatrix(const MatrixND& mat) const
{
    std::vector<float> _m;
    if (mat.lines != 2)
        return MatrixND(0, 0, _m);

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < mat.columns; ++j)
        {
            _m.push_back(0.f);
            for (int k = 0; k < 2; ++k)
            {
                _m[i * mat.columns + j] += m[i * 2 + k] * mat.m[k * mat.columns + j];
            }
        }
    }

    return MatrixND(2, mat.columns, _m);
}

Vector2D Matrix2x2::MultriplyVector2D(const Vector2D& vec) const
{
    return {
        m[0] * vec.x + m[1] * vec.y,
        m[2] * vec.x + m[3] * vec.y
    };
}

float Matrix2x2::Determinant() const
{
    return m[0] * m[3] - m[2] * m[1];
}

MatrixND Matrix2x2::ExpandRight(const Matrix2x2& mat) const
{
    std::vector<float> _m = {
        m[0], m[1], mat.m[0], mat.m[1],
        m[2], m[3], mat.m[2], mat.m[3],
    };

    return MatrixND(2, 4, _m);
}

MatrixND Matrix2x2::ExpandRight(const MatrixND& mat) const
{
    std::vector<float> _m;

    if (mat.lines != 2)
        return MatrixND(0, 0, _m);

    for (int i = 0; i < 2; ++i)
    {
        _m.push_back(m[i * 2]);
        _m.push_back(m[i * 2 + 1]);

        for(int j = 0; j < mat.columns; ++j)
            _m.push_back(mat.m[i * mat.columns + j]);
    }

    return MatrixND(2, 2 + mat.columns, _m);
}

Matrix2x2 Matrix2x2::Pivot() const
{
    float _m[4] = {
        m[0], m[1],
        m[2], m[3]
    };

    int r = -1;
    for (int j = 0; j < 2; ++j)
    {
        int k = j;

        for (int i = j; i < 2; ++i)
            if (std::abs(_m[i * 2 + j]) > std::abs(_m[k * 2 + j]))
                k = i;

        if (IsEqualZero(_m[k * 2 + j]))
            continue;

        ++r;

        if (k != r)
            for (int i = 0; i < 2; ++i)
                std::swap(_m[r * 2 + i], _m[k * 2 + i]);

        float pivot = _m[r * 2 + j];
        if (!IsEqualZero(pivot))
            for (int i = 0; i < 2; ++i)
                _m[r * 2 + i] /= pivot;

        for (int i = 0; i < 2; ++i)
        {
            if (i != r)
            {
                float factor = _m[i * 2 + j];
                for (int l = 0; l < 2; ++l)
                    _m[i * 2 + l] -= factor * _m[r * 2 + l];
            }
        }
    }

    return Matrix2x2(_m);
}

Matrix2x2 Matrix2x2::Inverse() const
{
    if (IsEqualZero(Determinant()))
        return Matrix2x2::Zero;

    MatrixND mat(2, 4, ExpandRight(Matrix2x2::Identity).m);
    mat = mat.Pivot();

    return {
        mat.m[2], mat.m[3],
        mat.m[6], mat.m[7]
    };;
}

Matrix3x3 Matrix2x2::Translate(Vector3D p)
{
    return {
        1.f, 0.f, p.x,
        0.f, 1.f, p.y,
        0.f, 0.f, 1.f
    };
}

Matrix2x2 Matrix2x2::Rotate2DOrigin(float angle) const
{
   

    return {
        std::cos(angle), -std::sin(angle),
        std::sin(angle),   std::cos(angle)
    };
}

Matrix3x3 Matrix2x2::Rotate2DPoint(float angle, Vector2D p)
{
    angle = TO_RADIANS(angle);

    return {
        std::cos(angle), -std::sin(angle), p.x * (1 - std::cos(angle)) + p.y * std::sin(angle),
        std::sin(angle),   std::cos(angle),  p.y * (1 - std::cos(angle)) - p.x * std::sin(angle),
             0.f,               0.f,                             1.f
    };;
}

void Matrix2x2::Print() const
{
    std::cout << m[0] << " " << m[1] << std::endl 
              << m[2] << " " << m[3] << std::endl;
}

Vector2D Matrix2x2::operator*(Vector2D& v)
{
    return MultriplyVector2D(v);
}

bool  Matrix2x2::operator==(const Matrix2x2& mPrime)
{
    return IsEqual(m[0], mPrime.m[0]) && 
           IsEqual(m[1], mPrime.m[1]) && 
           IsEqual(m[2], mPrime.m[2]) && 
           IsEqual(m[3], mPrime.m[3]);
}

float Matrix2x2::operator[](int index)
{
    switch (index)
    {
    case 0:
        return m[0];
    case 1:
        return m[1];
    case 2:
        return m[2];
    default:
        return m[3];
    }
}

Matrix2x2 Matrix2x2::operator+(const Matrix2x2& mPrime)
{
    return AddMatrix(mPrime);
}

Matrix2x2 Matrix2x2::operator+(const MatrixND& mPrime)
{
    return AddMatrix(mPrime);
}

Matrix2x2 Matrix2x2::operator+(float x)
{
    return {
         m[0] + x, m[1] + x,
         m[2] + x, m[3] + x
    };
}

void Matrix2x2::operator+=(const Matrix2x2& mPrime)
{
    m[0] += mPrime.m[0];
    m[1] += mPrime.m[1];
    m[2] += mPrime.m[2];
    m[3] += mPrime.m[3];
}

void Matrix2x2::operator+=(const MatrixND& mPrime)
{
    if (mPrime.lines != 2 || mPrime.columns != 2)
        return;

    m[0] += mPrime.m[0];
    m[1] += mPrime.m[1];
    m[2] += mPrime.m[2];
    m[3] += mPrime.m[3];
}

void Matrix2x2::operator+=(float x)
{
    m[0] += x;
    m[1] += x;
    m[2] += x;
    m[3] += x;
}

Matrix2x2 Matrix2x2::operator-(const Matrix2x2& mPrime)
{
    return {
        m[0] - mPrime.m[0], m[1] - mPrime.m[1],
        m[2] - mPrime.m[2], m[3] - mPrime.m[3]
    };
}

Matrix2x2 Matrix2x2::operator-(const MatrixND& mat)
{
    if (mat.lines != 2 || mat.columns != 2)
        return Matrix2x2::Zero;

    return {
        m[0] - mat.m[0], m[1] - mat.m[1],
        m[2] - mat.m[2], m[3] - mat.m[3]
    };
}

Matrix2x2 Matrix2x2::operator-(float x)
{
    return {
        m[0] - x, m[1] - x,
        m[2] - x, m[3] - x
    };
}

void Matrix2x2::operator-=(const Matrix2x2& mPrime)
{
    m[0] -= mPrime.m[0];
    m[1] -= mPrime.m[1];
    m[2] -= mPrime.m[2];
    m[3] -= mPrime.m[3];
}

void Matrix2x2::operator-=(const MatrixND& mPrime)
{
    if (mPrime.lines != 2 || mPrime.columns != 2)
        return;

    m[0] -= mPrime.m[0];
    m[1] -= mPrime.m[1];
    m[2] -= mPrime.m[2];
    m[3] -= mPrime.m[3];
}

void Matrix2x2::operator-=(float x)
{
    m[0] -= x;
    m[1] -= x;
    m[2] -= x;
    m[3] -= x;
}

Matrix2x2 Matrix2x2::operator*(const Matrix2x2& mPrime)
{
    return MultiplyMatrix(mPrime);
}

MatrixND Matrix2x2::operator*(const MatrixND& mPrime)
{
    return MultiplyMatrix(mPrime);
}

Vector2D Matrix2x2::operator*(const Vector2D& v)
{
    return MultriplyVector2D(v);
}

Matrix2x2 Matrix2x2::operator*(float x)
{
    return MultiplyScalar(x);
}

void Matrix2x2::operator*=(const Matrix2x2& mPrime)
{
    m[0] *= mPrime.m[0];
    m[1] *= mPrime.m[1];
    m[2] *= mPrime.m[2];
    m[3] *= mPrime.m[3];
}

void Matrix2x2::operator*=(float x)
{
    m[0] *= x;
    m[1] *= x;
    m[2] *= x;
    m[3] *= x;
}

void Matrix2x2::operator/=(float x)
{
    if (IsEqualZero(x))
        return;

    m[0] /= x; 
    m[1] /= x;
    m[2] /= x; 
    m[3] /= x;
}

void Matrix2x2::operator/=(const Matrix2x2& mPrime)
{
    if (IsEqualZero(mPrime.m[0]) || IsEqualZero(mPrime.m[1]) || IsEqualZero(mPrime.m[2]) || IsEqualZero(mPrime.m[3]))
        return;

    m[0] /= mPrime.m[0];
    m[1] /= mPrime.m[1];
    m[2] /= mPrime.m[2];
    m[3] /= mPrime.m[3];
}

Matrix2x2 Matrix2x2::operator/(float x)
{
    if (IsEqualZero(x))
        return Matrix2x2::Zero;

    return {
        m[0] / x, m[1] / x,
        m[2] / x, m[3] / x
    };
}

Matrix2x2 Matrix2x2::operator/(const Matrix2x2& mPrime)
{
    if (IsEqualZero(mPrime.m[0]) || IsEqualZero(mPrime.m[1]) || IsEqualZero(mPrime.m[2]) || IsEqualZero(mPrime.m[3]))
        return Matrix2x2::Zero;

    return {
        m[0] / mPrime.m[0], m[1] / mPrime.m[1],
        m[2] / mPrime.m[2], m[3] / mPrime.m[3]
    };
}

void Matrix2x2::RoundMatrix()
{
    if (NearZero(m[0])) m[0] = 0.f;
    if (NearZero(m[1])) m[1] = 0.f;
    if (NearZero(m[2])) m[2] = 0.f;
    if (NearZero(m[3])) m[3] = 0.f;
}

bool Matrix2x2::NearZero(float num) const
{
    if (std::fabs(num) < 0.00001f)
        return true;
    else
        return false;
}


#pragma endregion

#pragma region Matrix3x3

const Matrix3x3 Matrix3x3::Identity = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

const Matrix3x3 Matrix3x3::Zero = {
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f
};

Matrix3x3::Matrix3x3()
{
    m[0] = 0.0f;
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 0.0f;
    m[4] = 0.0f;
    m[5] = 0.0f;
    m[6] = 0.0f;
    m[7] = 0.0f;
    m[8] = 0.0f;

    RoundMatrix();
}

Matrix3x3::Matrix3x3(std::vector<float> vertex)
{
    m[0] = vertex[0];
    m[1] = vertex[1];
    m[2] = vertex[2];
    m[3] = vertex[3];
    m[4] = vertex[4];
    m[5] = vertex[5];
    m[6] = vertex[6];
    m[7] = vertex[7];
    m[8] = vertex[8];

    RoundMatrix();
}

Matrix3x3::Matrix3x3(float _m[9])
{
    m[0] = _m[0];
    m[1] = _m[1];
    m[2] = _m[2];
    m[3] = _m[3];
    m[4] = _m[4];
    m[5] = _m[5];
    m[6] = _m[6];
    m[7] = _m[7];
    m[8] = _m[8];

    RoundMatrix();
}

Matrix3x3::Matrix3x3(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3)
{
    m[0] = v1[0];
    m[1] = v1[1];
    m[2] = v1[2];

    m[3] = v2[0];
    m[4] = v2[1];
    m[5] = v2[2];

    m[6] = v3[0];
    m[7] = v3[1];
    m[8] = v3[2];

    RoundMatrix();
}

Matrix3x3::Matrix3x3(float n1, float n2, float n3, float n4, float n5, float n6, float n7, float n8, float n9)
{
    m[0] = n1;
    m[1] = n2;
    m[2] = n3;
    m[3] = n4;
    m[4] = n5;
    m[5] = n6;
    m[6] = n7;
    m[7] = n8;
    m[8] = n9;

    RoundMatrix();
}

Matrix3x3::Matrix3x3(float components)
{
    m[0] = components;
    m[1] = components;
    m[2] = components;
    m[3] = components;
    m[4] = components;
    m[5] = components;
    m[6] = components;
    m[7] = components;
    m[8] = components;

    RoundMatrix();
}

Matrix3x3::Matrix3x3(Matrix4x4 mat)
{
	m[0] = mat.m[0];
	m[1] = mat.m[1];
	m[2] = mat.m[2];
	m[3] = mat.m[4];
	m[4] = mat.m[5];
	m[5] = mat.m[6];
	m[6] = mat.m[8];
	m[7] = mat.m[9];
	m[8] = mat.m[10];

	RoundMatrix();
}

Vector3D Matrix3x3::Diagonal() const
{
    return Vector3D(m[0], m[4], m[8]);
}

float Matrix3x3::Trace() const
{
    return m[0] + m[4] + m[8];
}

Matrix3x3 Matrix3x3::Opposite() const
{
    return {
        -m[0], -m[1], -m[2],
        -m[3], -m[4], -m[5],
        -m[6], -m[7], -m[8]
    };
}

Matrix3x3 Matrix3x3::Transposite() const
{
    return {
        m[0], m[3], m[6],
        m[1], m[4], m[7],
        m[2], m[5], m[8]
    };
}

Matrix3x3 Matrix3x3::AddMatrix(const Matrix3x3& mat) const
{
    return {
        m[0] + mat.m[0], m[1] + mat.m[1], m[2] + mat.m[2],
        m[3] + mat.m[3], m[4] + mat.m[4], m[5] + mat.m[5],
        m[6] + mat.m[6], m[7] + mat.m[7], m[8] + mat.m[8]
    };
}

Matrix3x3 Matrix3x3::AddMatrix(const MatrixND& mat) const
{
    if (mat.lines != 3 || mat.columns != 3)
        return Matrix3x3::Zero;

    return {
        m[0] + mat.m[0], m[1] + mat.m[1], m[2] + mat.m[2],
        m[3] + mat.m[3], m[4] + mat.m[4], m[5] + mat.m[5],
        m[6] + mat.m[6], m[7] + mat.m[7], m[8] + mat.m[8]
    };
}

Matrix3x3 Matrix3x3::MultiplyScalar(float f) const
{
    return {
        m[0] * f, m[1] * f, m[2] * f,
        m[3] * f, m[4] * f, m[5] * f,
        m[6] * f, m[7] * f, m[8] * f
    };
}

Matrix3x3 Matrix3x3::MultiplyMatrix(const Matrix3x3& mat) const
{
    return {
        m[0] * mat.m[0] + m[1] * mat.m[3] + m[2] * mat.m[6],
        m[0] * mat.m[1] + m[1] * mat.m[4] + m[2] * mat.m[7],
        m[0] * mat.m[2] + m[1] * mat.m[5] + m[2] * mat.m[8],

        m[3] * mat.m[0] + m[4] * mat.m[3] + m[5] * mat.m[6],
        m[3] * mat.m[1] + m[4] * mat.m[4] + m[5] * mat.m[7],
        m[3] * mat.m[2] + m[4] * mat.m[5] + m[5] * mat.m[8],

        m[6] * mat.m[0] + m[7] * mat.m[3] + m[8] * mat.m[6],
        m[6] * mat.m[1] + m[7] * mat.m[4] + m[8] * mat.m[7],
        m[6] * mat.m[2] + m[7] * mat.m[5] + m[8] * mat.m[8]
    };
}

MatrixND Matrix3x3::MultiplyMatrix(const MatrixND& mat) const
{
    std::vector<float> _m;
    if (mat.lines != 3)
        return MatrixND(0, 0, _m);

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < mat.columns; ++j)
        {
            _m.push_back(0.f);
            for (int k = 0; k < 3; ++k)
            {
                _m[i * mat.columns + j] += m[i * 3 + k] * mat.m[k * mat.columns + j];
            }
        }
    }
    return MatrixND(3, mat.columns, _m);
}

Vector3D Matrix3x3::MultiplyVector3D(const Vector3D& vec) const
{
    float _m[3] = {
        0.f, 0.f, 0.f
    };

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            _m[i] += m[i * 3 + j] * vec[j];
        }
    }
    return Vector3D(_m[0], _m[1], _m[2]);
}

float Matrix3x3::Determinant() const
{
    float det = 0.f;

    det += m[0] * (m[4] * m[8] - m[7] * m[5]);
    det -= m[3] * (m[1] * m[8] - m[7] * m[2]);
    det += m[6] * (m[1] * m[5] - m[4] * m[2]);

    return det;
}

MatrixND Matrix3x3::ExpandRight(const Matrix3x3& mat) const
{
    std::vector<float> _m = {
        m[0], m[1], m[2], mat.m[0], mat.m[1], mat.m[2],
        m[3], m[4], m[5], mat.m[3], mat.m[4], mat.m[5],
        m[6], m[7], m[8], mat.m[6], mat.m[7], mat.m[8]
    };

    return MatrixND(3, 6, _m);
}

MatrixND Matrix3x3::ExpandRight(const MatrixND& mat) const
{
    std::vector<float> _m;

    if (mat.lines != 3)
        return MatrixND(0, 0, _m);

    for (int i = 0; i < 3; ++i)
    {
        _m.push_back(m[i * 3]);
        _m.push_back(m[i * 3 + 1]);
        _m.push_back(m[i * 3 + 2]);

        for (int j = 0; j < mat.columns; ++j)
            _m.push_back(mat.m[i * mat.columns + j]);
    }

    return MatrixND(3, 3 + mat.columns, _m);
}

Matrix3x3 Matrix3x3::Pivot() const
{
    float _m[9] = {
        m[0], m[1], m[2],
        m[3], m[4], m[5],
        m[6], m[7], m[8]
    };

    int r = -1;
    for (int j = 0; j < 3; ++j)
    {
        int k = j;

        for (int i = j; i < 3; ++i)
            if (std::abs(_m[i * 3 + j]) > std::abs(_m[k * 3 + j]))
                k = i;

        if (IsEqualZero(_m[k * 3 + j]))
            continue;

        ++r;

        if (k != r)
            for (int i = 0; i < 3; ++i)
                std::swap(_m[r * 3 + i], _m[k * 3 + i]);

        float pivot = _m[r * 3 + j];
        if (!IsEqualZero(pivot))
            for (int i = 0; i < 3; ++i)
                _m[r * 3 + i] /= pivot;

        for (int i = 0; i < 3; ++i)
        {
            if (i != r)
            {
                float factor = _m[i * 3 + j];
                for (int l = 0; l < 3; ++l)
                    _m[i * 3 + l] -= factor * _m[r * 3 + l];
            }
        }
    }

    return Matrix3x3(_m);
}

Matrix3x3 Matrix3x3::Inverse() const
{
    if (IsEqualZero(Determinant()))
        return *this;

    MatrixND mat(3, 6, ExpandRight(Matrix3x3::Identity).m);
    mat = mat.Pivot();

    return {
        mat.m[3],  mat.m[4],  mat.m[5],
        mat.m[9],  mat.m[10], mat.m[11],
        mat.m[15], mat.m[16], mat.m[17]
    };
}

Matrix4x4 Matrix3x3::Translate(Vector3D p) const
{
    return {
        1.f, 0.f, 0.f, p.x,
        0.f, 1.f, 0.f, p.y,
        0.f, 0.f, 1.f, p.z,
        0.f, 0.f, 0.f, 1.f
    };
}

Matrix3x3 Matrix3x3::Rotate3DOrigin(float x, float y, float z) const
{
    Matrix3x3 mat = Matrix3x3::Identity;

    float radConvert = PI / 180.f;
    x *= radConvert;
    y *= radConvert;
    z *= radConvert;

    if (!NearZero(z))
        mat = mat.MultiplyMatrix(Rotate3DZOrigin(z));
    if (!NearZero(y))
        mat = mat.MultiplyMatrix(Rotate3DYOrigin(y));
    if (!NearZero(x))
        mat = mat.MultiplyMatrix(Rotate3DXOrigin(x));

    return mat;
}

Matrix4x4 Matrix3x3::Rotate3DPoint(Vector3D p, Vector3D axis, float angle)
{
    angle *= PI / 180.0f;
    float cosA = cos(angle);
    float sinA = sin(angle);
    axis = axis.Normalized();

    float _m[16] = {
        cosA + axis.x * axis.x * (1.f - cosA),
        axis.x * axis.y * (1.f - cosA) - axis.z * sinA,
        axis.x * axis.z * (1.f - cosA) + axis.y * sinA,
        0.f,

        axis.y * axis.x * (1.f - cosA) + axis.z * sinA,
        cosA + axis.y * axis.y * (1.f - cosA),
        axis.y * axis.z * (1.f - cosA) - axis.x * sinA,
        0.f,

        axis.z * axis.x * (1.f - cosA) - axis.y * sinA,
        axis.z * axis.y * (1.f - cosA) + axis.x * sinA,
        cosA + axis.z * axis.z * (1.f - cosA),
        0.f,

        0.f, 0.f, 0.f, 1.f
    };

    Matrix4x4 rotation(_m);

    Matrix4x4 transOpposite = Matrix4x4::Identity.Translate(p.Opposite());
    Matrix4x4 transBack = Matrix4x4::Identity.Translate(p);

    return transBack.MultiplyMatrix(rotation).MultiplyMatrix(transOpposite);
}

Matrix3x3 Matrix3x3::Rotate3DXOrigin(float angle) const
{
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);

    return {
        1.f, 0.f,  0.f,
        0.f, cosA, -sinA,
        0.f, sinA, cosA
    };
}

Matrix3x3 Matrix3x3::Rotate3DYOrigin(float angle) const
{
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);

    return {
        cosA,  0.f, sinA,
        0.f,   1.f, 0.f,
        -sinA, 0.f, cosA
    };
}

Matrix3x3 Matrix3x3::Rotate3DZOrigin(float angle) const
{
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);

    return {
        cosA, -sinA, 0.f,
        sinA, cosA,  0.f,
        0.f,  0.f,   1.f
    };
}

Matrix3x3 Matrix3x3::CreateRotationXMatrix(float alpha)
{
    alpha = TO_RADIANS(alpha);

    return {
        1, 0, 0,
        0, cos(alpha), -sin(alpha),
        0, sin(alpha), cos(alpha)
    };
}

Matrix3x3 Matrix3x3::CreateRotationYMatrix(float alpha)
{
    alpha = TO_RADIANS(alpha);

    return {
        cos(alpha), 0, sin(alpha),
        0, 1, 0,
        -sin(alpha), 0, cos(alpha)
    };
}

Matrix3x3 Matrix3x3::CreateRotationZMatrix(float alpha)
{
    alpha = TO_RADIANS(alpha);

    return {
        cos(alpha), -sin(alpha), 0,
        sin(alpha), cos(alpha), 0,
        0, 0, 1
    };
}

Matrix3x3 Matrix3x3::CreateRotation3DMatrix(const Vector3D& rotation)
{
    return CreateRotationZMatrix(rotation.z) * CreateRotationYMatrix(rotation.y) * CreateRotationXMatrix(rotation.x);
}

void Matrix3x3::Print() const
{
    std::cout << m[0] << " " << m[1] << " " << m[2] << std::endl
              << m[3] << " " << m[4] << " " << m[5] << std::endl
              << m[6] << " " << m[7] << " " << m[8] << std::endl;
}

bool Matrix3x3::operator==(const Matrix3x3& mPrime)
{
    return IsEqual(m[0], mPrime.m[0]) && IsEqual(m[1], mPrime.m[1]) && IsEqual(m[2], mPrime.m[2]) &&
        IsEqual(m[3], mPrime.m[3]) && IsEqual(m[4], mPrime.m[4]) && IsEqual(m[5], mPrime.m[5]) &&
        IsEqual(m[6], mPrime.m[6]) && IsEqual(m[7], mPrime.m[7]) && IsEqual(m[8], mPrime.m[8]);
}

float Matrix3x3::operator[](int index)
{
    if (index >= 0 && index < 8)
        return m[index];
    return m[8];
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& mPrime)
{
    return AddMatrix(mPrime);
}

Matrix3x3 Matrix3x3::operator+(const MatrixND& mPrime)
{
    return AddMatrix(mPrime);
}

Matrix3x3 Matrix3x3::operator+(float x)
{
    return {
        m[0] + x, m[1] + x, m[2] + x,
        m[3] + x, m[4] + x, m[5] + x,
        m[6] + x, m[7] + x, m[8] + x
    };
}

void Matrix3x3::operator+=(const Matrix3x3& mPrime)
{
    m[0] += mPrime.m[0];
    m[1] += mPrime.m[1];
    m[2] += mPrime.m[2];
    m[3] += mPrime.m[3];
    m[4] += mPrime.m[4];
    m[5] += mPrime.m[5];
    m[6] += mPrime.m[6];
    m[7] += mPrime.m[7];
    m[8] += mPrime.m[8];
}

void Matrix3x3::operator+=(const MatrixND& mPrime)
{
    if (mPrime.lines != 3 || mPrime.columns != 3) return;

    m[0] += mPrime.m[0];
    m[1] += mPrime.m[1];
    m[2] += mPrime.m[2];
    m[3] += mPrime.m[3];
    m[4] += mPrime.m[4];
    m[5] += mPrime.m[5];
    m[6] += mPrime.m[6];
    m[7] += mPrime.m[7];
    m[8] += mPrime.m[8];
}

void Matrix3x3::operator+=(float x)
{
    m[0] += x;
    m[1] += x;
    m[2] += x;
    m[3] += x;
    m[4] += x;
    m[5] += x;
    m[6] += x;
    m[7] += x;
    m[8] += x;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& mPrime)
{
    return {
        m[0] - mPrime.m[0], m[1] - mPrime.m[1], m[2] - mPrime.m[2],
        m[3] - mPrime.m[3], m[4] - mPrime.m[4], m[5] - mPrime.m[5],
        m[6] - mPrime.m[6], m[7] - mPrime.m[7], m[8] - mPrime.m[8]
    };
}

Matrix3x3 Matrix3x3::operator-(const MatrixND& mat)
{
    if (mat.lines != 3 || mat.columns != 3) 
        return Matrix3x3::Zero;

    return {
        m[0] - mat.m[0], m[1] - mat.m[1], m[2] - mat.m[2],
        m[3] - mat.m[3], m[4] - mat.m[4], m[5] - mat.m[5],
        m[6] - mat.m[6], m[7] - mat.m[7], m[8] - mat.m[8]
    };
}

Matrix3x3 Matrix3x3::operator-(float x)
{
    return {
        m[0] - x, m[1] - x, m[2] - x,
        m[3] - x, m[4] - x, m[5] - x,
        m[6] - x, m[7] - x, m[8] - x
    };
}

void Matrix3x3::operator-=(const Matrix3x3& mPrime)
{
    m[0] -= mPrime.m[0];
    m[1] -= mPrime.m[1];
    m[2] -= mPrime.m[2];
    m[3] -= mPrime.m[3];
    m[4] -= mPrime.m[4];
    m[5] -= mPrime.m[5];
    m[6] -= mPrime.m[6];
    m[7] -= mPrime.m[7];
    m[8] -= mPrime.m[8];
}

void Matrix3x3::operator-=(const MatrixND& mPrime)
{
    if (mPrime.lines != 3 || mPrime.columns != 3) 
        return;

    m[0] -= mPrime.m[0];
    m[1] -= mPrime.m[1];
    m[2] -= mPrime.m[2];
    m[3] -= mPrime.m[3];
    m[4] -= mPrime.m[4];
    m[5] -= mPrime.m[5];
    m[6] -= mPrime.m[6];
    m[7] -= mPrime.m[7];
    m[8] -= mPrime.m[8];
}

void Matrix3x3::operator-=(float x)
{
    m[0] -= x;
    m[1] -= x;
    m[2] -= x;
    m[3] -= x;
    m[4] -= x;
    m[5] -= x;
    m[6] -= x;
    m[7] -= x;
    m[8] -= x;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& mPrime)
{
    return MultiplyMatrix(mPrime);
}

MatrixND Matrix3x3::operator*(const MatrixND& mPrime)
{
    return MultiplyMatrix(mPrime);
}

Vector3D Matrix3x3::operator*(const Vector3D& v)
{
    return MultiplyVector3D(v);
}

Vector3D Matrix3x3::operator*(Vector3D& v)
{
    return MultiplyVector3D(v);
}

Matrix3x3 Matrix3x3::operator*(float x)
{
    return MultiplyScalar(x);
}

void Matrix3x3::operator*=(const Matrix3x3& mPrime)
{
    m[0] *= mPrime.m[0];
    m[1] *= mPrime.m[1];
    m[2] *= mPrime.m[2];
    m[3] *= mPrime.m[3];
    m[4] *= mPrime.m[4];
    m[5] *= mPrime.m[5];
    m[6] *= mPrime.m[6];
    m[7] *= mPrime.m[7];
    m[8] *= mPrime.m[8];
}

void Matrix3x3::operator*=(float x)
{
    m[0] *= x;
    m[1] *= x;
    m[2] *= x;
    m[3] *= x;
    m[4] *= x;
    m[5] *= x;
    m[6] *= x;
    m[7] *= x;
    m[8] *= x;
}

Matrix3x3 Matrix3x3::operator/(float x)
{
    if (IsEqualZero(x)) 
        return Matrix3x3::Zero;

    return {
        m[0] / x, m[1] / x, m[2] / x,
        m[3] / x, m[4] / x, m[5] / x,
        m[6] / x, m[7] / x, m[8] / x
    };
}

Matrix3x3 Matrix3x3::operator/(const Matrix3x3& mP)
{
    if (IsEqualZero(mP.m[0]) || IsEqualZero(mP.m[1]) || IsEqualZero(mP.m[2]) || 
        IsEqualZero(mP.m[3]) || IsEqualZero(mP.m[4]) || IsEqualZero(mP.m[5]) || 
        IsEqualZero(mP.m[6]) || IsEqualZero(mP.m[7]) || IsEqualZero(mP.m[8]))
        return Matrix3x3::Zero;
    
    return {
        m[0] / mP.m[0], m[1] / mP.m[1], m[2] / mP.m[2],
        m[3] / mP.m[3], m[4] / mP.m[4], m[5] / mP.m[5],
        m[6] / mP.m[6], m[7] / mP.m[7], m[8] / mP.m[8]
    };
}

void Matrix3x3::operator/=(float x)
{
    if (IsEqualZero(x)) 
        return;

    m[0] /= x;
    m[1] /= x;
    m[2] /= x;
    m[3] /= x;
    m[4] /= x;
    m[5] /= x;
    m[6] /= x;
    m[7] /= x;
    m[8] /= x;
}

void Matrix3x3::operator/=(const Matrix3x3& mPrime)
{
    if (IsEqualZero(mPrime.m[0]) || IsEqualZero(mPrime.m[1]) || IsEqualZero(mPrime.m[2]) ||
        IsEqualZero(mPrime.m[3]) || IsEqualZero(mPrime.m[4]) || IsEqualZero(mPrime.m[5]) ||
        IsEqualZero(mPrime.m[6]) || IsEqualZero(mPrime.m[7]) || IsEqualZero(mPrime.m[8]))
        return;

    m[0] /= mPrime.m[0];
    m[1] /= mPrime.m[1];
    m[2] /= mPrime.m[2];
    m[3] /= mPrime.m[3];
    m[4] /= mPrime.m[4];
    m[5] /= mPrime.m[5];
    m[6] /= mPrime.m[6];
    m[7] /= mPrime.m[7];
    m[8] /= mPrime.m[8];
}

void Matrix3x3::RoundMatrix()
{
    if (NearZero(m[0])) m[0] = 0.f;
    if (NearZero(m[1])) m[1] = 0.f;
    if (NearZero(m[2])) m[2] = 0.f;
    if (NearZero(m[3])) m[3] = 0.f;
    if (NearZero(m[4])) m[4] = 0.f;
    if (NearZero(m[5])) m[5] = 0.f;
    if (NearZero(m[6])) m[6] = 0.f;
    if (NearZero(m[7])) m[7] = 0.f;
    if (NearZero(m[8])) m[8] = 0.f;
}

bool Matrix3x3::NearZero(float num) const
{
    if (std::fabs(num) < 0.00001f)
        return true;
    else
        return false;
}
#pragma endregion

#pragma region Matrix4x4

const Matrix4x4 Matrix4x4::Identity = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};

const Matrix4x4 Matrix4x4::Zero = {
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
};

Matrix4x4::Matrix4x4(float _m[16])
{
    m[0] = _m[0];
    m[1] = _m[1];
    m[2] = _m[2];
    m[3] = _m[3];
    m[4] = _m[4];
    m[5] = _m[5];
    m[6] = _m[6];
    m[7] = _m[7];
    m[8] = _m[8];
    m[9] = _m[9];
    m[10] = _m[10];
    m[11] = _m[11];
    m[12] = _m[12];
    m[13] = _m[13];
    m[14] = _m[14];
    m[15] = _m[15];

    RoundMatrix();
}

Matrix4x4::Matrix4x4(const Vector4D& v1, const Vector4D& v2, const Vector4D& v3, const Vector4D& v4)
{
    m[0] =  v1[0];
    m[1] =  v1[1];
    m[2] =  v1[2];
    m[3] =  v1[3];
    m[4] =  v2[0];
    m[5] =  v2[1];
    m[6] =  v2[2];
    m[7] =  v2[3];
    m[8] =  v3[0];
    m[9] =  v3[1];
    m[10] = v3[2];
    m[11] = v3[3];
    m[12] = v4[0];
    m[13] = v4[1];
    m[14] = v4[2];
    m[15] = v4[3];

    RoundMatrix();
}

Matrix4x4::Matrix4x4(float n1, float n2, float n3, float n4, float n5, float n6, float n7, float n8, float n9, float n10, float n11, float n12, float n13, float n14, float n15, float n16)
{
    m[0] = n1;
    m[1] = n2;
    m[2] = n3;
    m[3] = n4;
    m[4] = n5;
    m[5] = n6;
    m[6] = n7;
    m[7] = n8;
    m[8] = n9;
    m[9] = n10;
    m[10] = n11;
    m[11] = n12;
    m[12] = n13;
    m[13] = n14;
    m[14] = n15;
    m[15] = n16;

    RoundMatrix();
}

Matrix4x4::Matrix4x4(float components)
{
    m[0] = components;
    m[1] = components;
    m[2] = components;
    m[3] = components;
    m[4] = components;
    m[5] = components;
    m[6] = components;
    m[7] = components;
    m[8] = components;
    m[9] = components;
    m[10] = components;
    m[11] = components;
    m[12] = components;
    m[13] = components;
    m[14] = components;
    m[15] = components;

    RoundMatrix();
}

Matrix4x4::Matrix4x4()
{
	m[0] = 0.f; 
    m[1] = 0.f; 
    m[2] = 0.f; 
    m[3] = 0.f;
	m[4] = 0.f; 
    m[5] = 0.f; 
    m[6] = 0.f; 
    m[7] = 0.f;
	m[8] = 0.f; 
    m[9] = 0.f; 
    m[10] = 0.f; 
    m[11] = 0.f;
	m[12] = 0.f; 
    m[13] = 0.f; 
    m[14] = 0.f; 
    m[15] = 0.f;

    RoundMatrix();
}

Matrix4x4::Matrix4x4(std::vector<float> vertex)
{
    m[0] = vertex[0];
    m[1] = vertex[1];
    m[2] = vertex[2];
    m[3] = vertex[3];
    m[4] = vertex[4];
    m[5] = vertex[5];
    m[6] = vertex[6];
    m[7] = vertex[7];
    m[8] = vertex[8];
    m[9] = vertex[9];
    m[10] = vertex[10];
    m[11] = vertex[11];
    m[12] = vertex[12];
    m[13] = vertex[13];
    m[14] = vertex[14];
    m[15] = vertex[15];

    RoundMatrix();
}

Matrix4x4::Matrix4x4(const Matrix3x3& mat)
{
	m[0] = mat.m[0]; m[1] = mat.m[1]; m[2] = mat.m[2]; m[3] = 0.f;
	m[4] = mat.m[3]; m[5] = mat.m[4]; m[6] = mat.m[5]; m[7] = 0.f;
    m[8] = mat.m[6]; m[9] = mat.m[7]; m[10] = mat.m[8]; m[11] = 0.f;
	m[12] = 0.f; m[13] = 0.f; m[14] = 0.f; m[15] = 1.f;
}

Vector4D Matrix4x4::Diagonal() const
{
    return Vector4D(m[0], m[5], m[10], m[15]);
}

float Matrix4x4::Trace() const
{
    return m[0] + m[5] + m[10] + m[15];
}

Matrix4x4 Matrix4x4::Opposite() const
{
    return {
        -m[0],  -m[1],  -m[2],  -m[3],
        -m[4],  -m[5],  -m[6],  -m[7],
        -m[8],  -m[9],  -m[10], -m[11],
        -m[12], -m[13], -m[14], -m[15]
    };
}

Matrix4x4 Matrix4x4::Transposite() const
{
    return {
        m[0], m[4], m[8],  m[12],
        m[1], m[5], m[9],  m[13],
        m[2], m[6], m[10], m[14],
        m[3], m[7], m[11], m[15]
    };
}

Matrix4x4 Matrix4x4::AddMatrix(const Matrix4x4& mat) const
{
    return {
        m[0] + mat.m[0],   m[1] + mat.m[1],   m[2] + mat.m[2],  m[3] + mat.m[3],
        m[4] + mat.m[4],   m[5] + mat.m[5],   m[6] + mat.m[6],  m[7] + mat.m[7],
        m[8] + mat.m[8],   m[9] + mat.m[9],   m[10] + mat.m[10], m[11] + mat.m[11],
        m[12] + mat.m[12], m[13] + mat.m[13], m[14] + mat.m[14], m[15] + mat.m[15]
    };
}

Matrix4x4 Matrix4x4::AddMatrix(const MatrixND& mat) const
{
    if (mat.lines != 4 || mat.columns != 4)
        return Matrix4x4::Zero;

    return {
        m[0] + mat.m[0],   m[1] + mat.m[1],   m[2] + mat.m[2],  m[3] + mat.m[3],
        m[4] + mat.m[4],   m[5] + mat.m[5],   m[6] + mat.m[6],  m[7] + mat.m[7],
        m[8] + mat.m[8],   m[9] + mat.m[9],   m[10] + mat.m[10], m[11] + mat.m[11],
        m[12] + mat.m[12], m[13] + mat.m[13], m[14] + mat.m[14], m[15] + mat.m[15]
    };
}

Matrix4x4 Matrix4x4::MultiplyScalar(float f) const
{
    return {
        m[0] * f,  m[1] * f,  m[2] * f,  m[3] * f,
        m[4] * f,  m[5] * f,  m[6] * f,  m[7] * f,
        m[8] * f,  m[9] * f,  m[10] * f, m[11] * f,
        m[12] * f, m[13] * f, m[14] * f, m[15] * f
    };
}

Matrix4x4 Matrix4x4::MultiplyMatrix(const Matrix4x4& array) const
{
    return {
        array.m[0] * m[0] + array.m[1] * m[4] + array.m[2] * m[8] + array.m[3] * m[12],
        array.m[0] * m[1] + array.m[1] * m[5] + array.m[2] * m[9] + array.m[3] * m[13],
        array.m[0] * m[2] + array.m[1] * m[6] + array.m[2] * m[10] + array.m[3] * m[14],
        array.m[0] * m[3] + array.m[1] * m[7] + array.m[2] * m[11] + array.m[3] * m[15],

        array.m[4] * m[0] + array.m[5] * m[4] + array.m[6] * m[8] + array.m[7] * m[12],
        array.m[4] * m[1] + array.m[5] * m[5] + array.m[6] * m[9] + array.m[7] * m[13],
        array.m[4] * m[2] + array.m[5] * m[6] + array.m[6] * m[10] + array.m[7] * m[14],
        array.m[4] * m[3] + array.m[5] * m[7] + array.m[6] * m[11] + array.m[7] * m[15],

        array.m[8] * m[0] + array.m[9] * m[4] + array.m[10] * m[8] + array.m[11] * m[12],
        array.m[8] * m[1] + array.m[9] * m[5] + array.m[10] * m[9] + array.m[11] * m[13],
        array.m[8] * m[2] + array.m[9] * m[6] + array.m[10] * m[10] + array.m[11] * m[14],
        array.m[8] * m[3] + array.m[9] * m[7] + array.m[10] * m[11] + array.m[11] * m[15],

        array.m[12] * m[0] + array.m[13] * m[4] + array.m[14] * m[8] + array.m[15] * m[12],
        array.m[12] * m[1] + array.m[13] * m[5] + array.m[14] * m[9] + array.m[15] * m[13],
        array.m[12] * m[2] + array.m[13] * m[6] + array.m[14] * m[10] + array.m[15] * m[14],
        array.m[12] * m[3] + array.m[13] * m[7] + array.m[14] * m[11] + array.m[15] * m[15]
    };
}

MatrixND Matrix4x4::MultiplyMatrix(const MatrixND& mat) const
{
    std::vector<float> _m;
    if (mat.lines != 4)
        return MatrixND(0, 0, _m);

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < mat.columns; ++j)
        {
            _m.push_back(0.f);
            for (int k = 0; k < 4; ++k)
            {
                _m[i * mat.columns + j] += m[i * 4 + k] * mat.m[k * mat.columns + j];
            }
        }
    }
    return MatrixND(4, mat.columns, _m);
}

Vector4D Matrix4x4::MultiplyVector4D(const Vector4D& vec) const
{
    float _m[4] = {
        0.f, 0.f, 0.f, 0.f
    };

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            _m[i] += m[i * 4 + j] * vec[j];
        }
    }
    return Vector4D(_m[0], _m[1], _m[2], _m[3]);
}

float Matrix4x4::Determinant() const
{
    float determinant = 0.f;
    float det[4] = { 0.f, 0.f, 0.f, 0.f };

    det[0] = m[5]  * (m[10] * m[15] - m[14] * m[11])
           - m[9]  * (m[6]  * m[15] - m[14] * m[7])
           + m[13] * (m[6]  * m[11] - m[10] * m[7]);

    det[1] = m[1]  * (m[10] * m[15] - m[14] * m[11])
           - m[9]  * (m[2]  * m[15] - m[14] * m[3])
           + m[13] * (m[2]  * m[11] - m[10] * m[3]);

    det[2] = m[1]  * (m[6] * m[15] - m[14] * m[7])
           - m[5]  * (m[2] * m[15] - m[14] * m[3])
           + m[13] * (m[2] * m[7]  - m[6]  * m[3]);

    det[3] = m[1] * (m[6] * m[11] - m[10] * m[7])
           - m[5] * (m[2] * m[11] - m[10] * m[3])
           + m[9] * (m[2] * m[7]  - m[6]  * m[3]);

    determinant = m[0] * det[0] - m[4] * det[1] + m[8] * det[2] - m[12] * det[3];

    return determinant;
}

MatrixND Matrix4x4::ExpandRight(const Matrix4x4& mat) const
{
    std::vector<float> _m = {
        m[0],  m[1],  m[2],  m[3],  mat.m[0],  mat.m[1],  mat.m[2],  mat.m[3],
        m[4],  m[5],  m[6],  m[7],  mat.m[4],  mat.m[5],  mat.m[6],  mat.m[7],
        m[8],  m[9],  m[10], m[11], mat.m[8],  mat.m[9],  mat.m[10], mat.m[11],
        m[12], m[13], m[14], m[15], mat.m[12], mat.m[13], mat.m[14], mat.m[15]
    };

    return MatrixND(4, 8, _m);
}

MatrixND Matrix4x4::ExpandRight(const MatrixND& mat) const
{
    std::vector<float> _m;

    if (mat.lines != 4)
        return MatrixND(0, 0, _m);

    for (int i = 0; i < 4; ++i)
    {
        _m.push_back(m[i * 4]);
        _m.push_back(m[i * 4 + 1]);
        _m.push_back(m[i * 4 + 2]);

        for (int j = 0; j < mat.columns; ++j)
            _m.push_back(mat.m[i * mat.columns + j]);
    }

    return MatrixND(4, 4 + mat.columns, _m);
}

Matrix4x4 Matrix4x4::Pivot() const
{
    float _m[16] = {
        m[0],  m[1],  m[2],  m[3],
        m[4],  m[5],  m[6],  m[7],
        m[8],  m[9],  m[10], m[11],
        m[12], m[13], m[14], m[15]
    };

    int r = -1;
    for (int j = 0; j < 4; ++j)
    {
        int k = j;

        for (int i = j; i < 4; ++i)
            if (std::abs(_m[i * 4 + j]) > std::abs(_m[k * 4 + j]))
                k = i;

        if (IsEqualZero(_m[k * 4 + j]))
            continue;

        ++r;

        if (k != r)
            for (int i = 0; i < 4; ++i)
                std::swap(_m[r * 4 + i], _m[k * 4 + i]);

        float pivot = _m[r * 4 + j];
        if (!IsEqualZero(pivot))
            for (int i = 0; i < 4; ++i)
                _m[r * 4 + i] /= pivot;

        for (int i = 0; i < 4; ++i)
        {
            if (i != r)
            {
                float factor = _m[i * 4 + j];
                for (int l = 0; l < 4; ++l)
                    _m[i * 4 + l] -= factor * _m[r * 4 + l];
            }
        }
    }

    return Matrix4x4(_m);
}

Matrix4x4 Matrix4x4::Inverse() const
{
    if (IsEqualZero(Determinant()))
        return *this;

    MatrixND mat(4, 8, ExpandRight(Identity).m);
    mat = mat.Pivot();

    return {
        mat.m[4],  mat.m[5],  mat.m[6],  mat.m[7],
        mat.m[12], mat.m[13], mat.m[14], mat.m[15],
        mat.m[20], mat.m[21], mat.m[22], mat.m[23],
        mat.m[28], mat.m[29], mat.m[30], mat.m[31]
    };
}

Matrix4x4 Matrix4x4::Translate(Vector3D p) const
{
    return {
        1.f, 0.f, 0.f, p.x,
        0.f, 1.f, 0.f, p.y,
        0.f, 0.f, 1.f, p.z,
        0.f, 0.f, 0.f, 1.f
    };
}

Matrix4x4 Matrix4x4::TRS(const Vector3D& translate, const Vector3D& rotation, const Vector3D& scale)
{
    Matrix3x3 r = Matrix3x3::CreateRotation3DMatrix(rotation);

    return Matrix4x4(
        scale.x * r.m[0], scale.y * r.m[1], scale.z * r.m[2], translate.x,
        scale.x * r.m[3], scale.y * r.m[4], scale.z * r.m[5], translate.y,
        scale.x * r.m[6], scale.y * r.m[7], scale.z * r.m[8], translate.z,
        0.f, 0.f, 0.f, 1.f
    ).Transposite();
}

Matrix4x4 Matrix4x4::Perspective(float FOV, float aspect, float zNear, float zFar)
{
    Matrix4x4 result;

	const float tanHalfFov = tan(FOV / 2.f);

	result.m[0] = 1.f / (aspect * tanHalfFov);
	result.m[5] = 1.f / (tanHalfFov);
	result.m[10] = -(zFar + zNear) / (zFar - zNear);
	result.m[11] = -1.f;
	result.m[14] = -(2.f * zFar * zNear) / (zFar - zNear);

    return result;
}

Matrix4x4 Matrix4x4::Orthographic(float left, float right, float bottom, float top, float zNear, float zFar)
{
    Matrix4x4 result = Matrix4x4::Identity;
    result.m[0] = 2.f / (right - left);
    result.m[5] = 2.f / (top - bottom);
    result.m[10] = -2.f / (zFar - zNear);
    result.m[12] = -(right + left) / (right - left);
    result.m[13] = -(top + bottom) / (top - bottom);
    result.m[14] = -(zFar + zNear) / (zFar - zNear);
    return result;
}

Matrix4x4 Matrix4x4::LookAt(Vector3D position, Vector3D target, Vector3D up)
{
    Matrix4x4 result = Matrix4x4::Identity;

    Vector3D f = (target - position).Normalized();
    Vector3D s = f.CrossProduct(up).Normalized();
    Vector3D u = s.CrossProduct(f).Normalized();

    result.m[0] = s.x; result.m[1] = u.x; result.m[2] = -f.x; result.m[3] = 0.f;
    result.m[4] = s.y; result.m[5] = u.y; result.m[6] = -f.y; result.m[7] = 0.f;
    result.m[8] = s.z; result.m[9] = u.z; result.m[10] = -f.z; result.m[11] = 0.f;
    result.m[12] = -s.DotProduct(position); result.m[13] = -u.DotProduct(position); result.m[14] = f.DotProduct(position); result.m[15] = 1.f;

    return result;
}

Matrix4x4 Matrix4x4::CreateTranslationMatrix(const Vector3D& translation)
{
    Matrix4x4 mat = Matrix4x4::Identity;

    mat.m[3] = -translation.x;
    mat.m[7] = -translation.y;
    mat.m[11] = -translation.z;

    return mat.Transposite();
}

Matrix4x4 Matrix4x4::CreateScaleMatrix(const Vector3D& scale)
{
    Matrix4x4 mat = Matrix4x4::Identity;
    mat.m[0] = scale.x;
    mat.m[5] = scale.y;
    mat.m[10] = scale.z;
    mat.m[15] = 1.f;
    return mat.Transposite();

}

Matrix4x4 Matrix4x4::CreateXRotationMatrix(float angle)
{
    angle *= PI / 180.f;

    Matrix4x4 mat = Matrix4x4::Identity;
    mat.m[5] = cos(angle);
    mat.m[6] = -sin(angle);
    mat.m[9] = sin(angle);
    mat.m[10] = cos(angle);
    return mat.Transposite();

}

Matrix4x4 Matrix4x4::CreateYRotationMatrix(float angle)
{
    angle *= PI / 180.f;

    Matrix4x4 mat = Matrix4x4::Identity;
    mat.m[0] = cos(angle);
    mat.m[2] = sin(angle);
    mat.m[8] = -sin(angle);
    mat.m[10] = cos(angle);
    return mat.Transposite();

}

Matrix4x4 Matrix4x4::CreateZRotationMatrix(float angle)
{
    angle *= PI / 180.f;

    Matrix4x4 mat = Matrix4x4::Identity;
    mat.m[0] = cos(angle);
    mat.m[1] = -sin(angle);
    mat.m[4] = sin(angle);
    mat.m[5] = cos(angle);
    return mat.Transposite();

}

Matrix4x4 Core::Maths::Matrix4x4::CreateRotationMatrix(const Vector3D& rotation)
{
    return CreateZRotationMatrix(rotation.z) * CreateZRotationMatrix(rotation.y) * CreateZRotationMatrix(rotation.x);
}

void Matrix4x4::Print() const
{
    for (int i = 0; i < 16; ++i)
    {
        if (i % 4 == 0)
            std::cout << std::endl;
        std::cout << m[i] << " ";
    }
}

bool Matrix4x4::operator==(const Matrix4x4& mP)
{
    return IsEqual(m[0], mP.m[0]) && IsEqual(m[1], mP.m[1]) && IsEqual(m[2], mP.m[2]) && IsEqual(m[3], mP.m[3]) &&
        IsEqual(m[4], mP.m[4]) && IsEqual(m[5], mP.m[5]) && IsEqual(m[6], mP.m[6]) && IsEqual(m[7], mP.m[7]) &&
        IsEqual(m[8], mP.m[8]) && IsEqual(m[9], mP.m[9]) && IsEqual(m[10], mP.m[10]) && IsEqual(m[11], mP.m[11]) &&
        IsEqual(m[12], mP.m[12]) && IsEqual(m[13], mP.m[13]) && IsEqual(m[14], mP.m[14]) && IsEqual(m[15], mP.m[15]);
}

float Matrix4x4::operator[](int index)
{
    if (index >= 0 && index <= 15)
        return m[index];
    else
        return m[15];
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& mP)
{ 
    return AddMatrix(mP);
}

Matrix4x4 Matrix4x4::operator+(const MatrixND& mP) 
{ 
    return AddMatrix(mP);
}

Matrix4x4 Matrix4x4::operator+(float x)
{
    return {
        m[0] + x,  m[1] + x,  m[2] + x,  m[3] + x,
        m[4] + x,  m[5] + x,  m[6] + x,  m[7] + x,
        m[8] + x,  m[9] + x,  m[10] + x, m[11] + x,
        m[12] + x, m[13] + x, m[14] + x, m[15] + x
    };
}

void Matrix4x4::operator+=(const Matrix4x4& mP)
{
    m[0] += mP.m[0];   m[1] += mP.m[1];   m[2] += mP.m[2];   m[3] += mP.m[3];
    m[4] += mP.m[4];   m[5] += mP.m[5];   m[6] += mP.m[6];   m[7] += mP.m[7];
    m[8] += mP.m[8];   m[9] += mP.m[9];   m[10] += mP.m[10]; m[11] += mP.m[11];
    m[12] += mP.m[12]; m[13] += mP.m[13]; m[14] += mP.m[14]; m[15] += mP.m[15];
}

void Matrix4x4::operator+=(const MatrixND& mP)
{
    if (mP.lines != 4 || mP.columns != 4) 
        return;

    m[0] += mP.m[0];   m[1] += mP.m[1];   m[2] += mP.m[2];   m[3] += mP.m[3];
    m[4] += mP.m[4];   m[5] += mP.m[5];   m[6] += mP.m[6];   m[7] += mP.m[7];
    m[8] += mP.m[8];   m[9] += mP.m[9];   m[10] += mP.m[10]; m[11] += mP.m[11];
    m[12] += mP.m[12]; m[13] += mP.m[13]; m[14] += mP.m[14]; m[15] += mP.m[15];
}

void Matrix4x4::operator+=(float x)
{
    m[0] += x;  m[1] += x, m[2] += x, m[3] += x,
        m[4] += x, m[5] += x, m[6] += x, m[7] += x,
        m[8] += x, m[9] += x, m[10] += x, m[11] += x,
        m[12] += x, m[13] += x, m[14] += x, m[15] += x;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& mP)
{
    return {
        m[0] - mP.m[0], m[1] - mP.m[1], m[2] - mP.m[2], m[3] - mP.m[3],
        m[4] - mP.m[4], m[5] - mP.m[5], m[6] - mP.m[6], m[7] - mP.m[7],
        m[8] - mP.m[8], m[9] - mP.m[9], m[10] - mP.m[10], m[11] - mP.m[11],
        m[12] - mP.m[12], m[13] - mP.m[13], m[14] - mP.m[14], m[15] - mP.m[15]
    };
}

Matrix4x4 Matrix4x4::operator-(const MatrixND& mat)
{
    if (mat.lines != 4 || mat.columns != 4) 
        return Matrix4x4::Zero;

    return {
        m[0] - mat.m[0], m[1] - mat.m[1], m[2] - mat.m[2], m[3] - mat.m[3],
        m[4] - mat.m[4], m[5] - mat.m[5], m[6] - mat.m[6], m[7] - mat.m[7],
        m[8] - mat.m[8], m[9] - mat.m[9], m[10] - mat.m[10], m[11] - mat.m[11],
        m[12] - mat.m[12], m[13] - mat.m[13], m[14] - mat.m[14], m[15] - mat.m[15]
    };
}

Matrix4x4 Matrix4x4::operator-(float x)
{
    return {
        m[0] - x,  m[1] - x,  m[2] - x,  m[3] - x,
        m[4] - x,  m[5] - x,  m[6] - x,  m[7] - x,
        m[8] - x,  m[9] - x,  m[10] - x, m[11] - x,
        m[12] - x, m[13] - x, m[14] - x, m[15] - x
    };
}

void Matrix4x4::operator-=(const Matrix4x4& mP)
{
    m[0] -= mP.m[0];   m[1] -= mP.m[1];   m[2] -= mP.m[2];   m[3] -= mP.m[3];
    m[4] -= mP.m[4];   m[5] -= mP.m[5];   m[6] -= mP.m[6];   m[7] -= mP.m[7];
    m[8] -= mP.m[8];   m[9] -= mP.m[9];   m[10] -= mP.m[10]; m[11] -= mP.m[11];
    m[12] -= mP.m[12]; m[13] -= mP.m[13]; m[14] -= mP.m[14]; m[15] -= mP.m[15];
}

void Matrix4x4::operator-=(const MatrixND& mP)
{
    if (mP.lines != 4 || mP.columns!= 4)
        return;

    m[0] -= mP.m[0];   m[1] -= mP.m[1];   m[2] -= mP.m[2];   m[3] -= mP.m[3];
    m[4] -= mP.m[4];   m[5] -= mP.m[5];   m[6] -= mP.m[6];   m[7] -= mP.m[7];
    m[8] -= mP.m[8];   m[9] -= mP.m[9];   m[10] -= mP.m[10]; m[11] -= mP.m[11];
    m[12] -= mP.m[12]; m[13] -= mP.m[13]; m[14] -= mP.m[14]; m[15] -= mP.m[15];
}

void Matrix4x4::operator-=(float x)
{
    m[0] -= x;  m[1] -= x, m[2] -= x, m[3] -= x,
        m[4] -= x, m[5] -= x, m[6] -= x, m[7] -= x,
        m[8] -= x, m[9] -= x, m[10] -= x, m[11] - x,
        m[12] -= x, m[13] - x, m[14] - x, m[15] - x;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& mP) 
{ 
    return MultiplyMatrix(mP); 
}

MatrixND Matrix4x4::operator*(const MatrixND& mP) 
{ 
    return MultiplyMatrix(mP); 
}

Vector4D Matrix4x4::operator*(const Vector4D& v) 
{ 
    return MultiplyVector4D(v); 
}

Vector4D Matrix4x4::operator*(Vector4D& v) 
{ 
    return MultiplyVector4D(v); 
}

Matrix4x4 Matrix4x4::operator*(float x) 
{ 
    return MultiplyScalar(x); 
}

void Matrix4x4::operator*=(const Matrix4x4& mP)
{
    m[0] *= mP.m[0];   m[1] *= mP.m[1];   m[2] *= mP.m[2];   m[3] *= mP.m[3];
    m[4] *= mP.m[4];   m[5] *= mP.m[5];   m[6] *= mP.m[6];   m[7] *= mP.m[7];
    m[8] *= mP.m[8];   m[9] *= mP.m[9];   m[10] *= mP.m[10]; m[11] *= mP.m[11];
    m[12] *= mP.m[12]; m[13] *= mP.m[13]; m[14] *= mP.m[14]; m[15] *= mP.m[15];
}

void Matrix4x4::operator*=(float x)
{
    m[0] *= x;  m[1] *= x, m[2] *= x, m[3] *= x,
        m[4] *= x, m[5] *= x, m[6] *= x, m[7] *= x,
        m[8] *= x, m[9] *= x, m[10] *= x, m[11] *= x,
        m[12] *= x, m[13] *= x, m[14] *= x, m[15] *= x;
}

Matrix4x4 Matrix4x4::operator/(float x)
{
    if (IsEqualZero(x)) return Matrix4x4::Zero;
    return {
        m[0] / x,  m[1] / x,  m[2] / x,  m[3] / x,
        m[4] / x,  m[5] / x,  m[6] / x,  m[7] / x,
        m[8] / x,  m[9] / x,  m[10] / x, m[11] / x,
        m[12] / x, m[13] / x, m[14] / x, m[15] / x
    };
}

Matrix4x4 Matrix4x4::operator/(const Matrix4x4& mP)
{
    if (IsEqualZero(mP.m[0]) || IsEqualZero(mP.m[1]) || IsEqualZero(mP.m[2]) || IsEqualZero(mP.m[3]) ||
        IsEqualZero(mP.m[4]) || IsEqualZero(mP.m[5]) || IsEqualZero(mP.m[6]) || IsEqualZero(mP.m[7]) ||
        IsEqualZero(mP.m[8]) || IsEqualZero(mP.m[9]) || IsEqualZero(mP.m[10]) || IsEqualZero(mP.m[11]) ||
        IsEqualZero(mP.m[12]) || IsEqualZero(mP.m[13]) || IsEqualZero(mP.m[14]) || IsEqualZero(mP.m[15]))
        return Matrix4x4::Zero;

    return {
        m[0] / mP.m[0], m[1] / mP.m[1], m[2] / mP.m[2], m[3] / mP.m[3],
        m[4] / mP.m[4], m[5] / mP.m[5], m[6] / mP.m[6], m[7] / mP.m[7],
        m[8] / mP.m[8], m[9] / mP.m[9], m[10] / mP.m[10], m[11] / mP.m[11],
        m[12] / mP.m[12], m[13] / mP.m[13], m[14] / mP.m[14], m[15] / mP.m[15]
    };
}

void Matrix4x4::operator/=(float x)
{
    if (IsEqualZero(x)) 
        return;

    m[0] /= x;  m[1] /= x, m[2] /= x, m[3] /= x,
        m[4] /= x, m[5] /= x, m[6] /= x, m[7] /= x,
        m[8] /= x, m[9] /= x, m[10] /= x, m[11] / x,
        m[12] /= x, m[13] / x, m[14] / x, m[15] / x;
}

void Matrix4x4::operator/=(const Matrix4x4& mP)
{
    if (IsEqualZero(mP.m[0]) || IsEqualZero(mP.m[1]) || IsEqualZero(mP.m[2]) || IsEqualZero(mP.m[3]) ||
        IsEqualZero(mP.m[4]) || IsEqualZero(mP.m[5]) || IsEqualZero(mP.m[6]) || IsEqualZero(mP.m[7]) ||
        IsEqualZero(mP.m[8]) || IsEqualZero(mP.m[9]) || IsEqualZero(mP.m[10]) || IsEqualZero(mP.m[11]) ||
        IsEqualZero(mP.m[12]) || IsEqualZero(mP.m[13]) || IsEqualZero(mP.m[14]) || IsEqualZero(mP.m[15]))
        return;

    m[0] /= mP.m[0];   m[1] /= mP.m[1];   m[2] /= mP.m[2];   m[3] /= mP.m[3];
    m[4] /= mP.m[4];   m[5] /= mP.m[5];   m[6] /= mP.m[6];   m[7] /= mP.m[7];
    m[8] /= mP.m[8];   m[9] /= mP.m[9];   m[10] /= mP.m[10]; m[11] /= mP.m[11];
    m[12] /= mP.m[12]; m[13] /= mP.m[13]; m[14] /= mP.m[14]; m[15] /= mP.m[15];
}

void Matrix4x4::RoundMatrix()
{
    if (NearZero(m[0]))  m[0] = 0.f;
    if (NearZero(m[1]))  m[1] = 0.f;
    if (NearZero(m[2]))  m[2] = 0.f;
    if (NearZero(m[3]))  m[3] = 0.f;
    if (NearZero(m[4]))  m[4] = 0.f;
    if (NearZero(m[5]))  m[5] = 0.f;
    if (NearZero(m[6]))  m[6] = 0.f;
    if (NearZero(m[7]))  m[7] = 0.f;
    if (NearZero(m[8]))  m[8] = 0.f;
    if (NearZero(m[9]))  m[9] = 0.f;
    if (NearZero(m[10])) m[10] = 0.f;
    if (NearZero(m[11])) m[11] = 0.f;
    if (NearZero(m[12])) m[12] = 0.f;
    if (NearZero(m[13])) m[13] = 0.f;
    if (NearZero(m[14])) m[14] = 0.f;
    if (NearZero(m[15])) m[15] = 0.f;
}

bool Matrix4x4::NearZero(float num) const
{
    if (std::fabs(num) < 0.00001f)
        return true;
    else
        return false;
}
#pragma endregion

#pragma region MatrixND

MatrixND::MatrixND(int _lines, int _columns, std::vector<float> _m) : lines(_lines), columns(_columns), m(_m), size(lines * columns)
{
    RoundMatrix();
}

MatrixND::MatrixND(int _lines, int _columns) : lines(_lines), columns(_columns), size(lines* columns)
{
    m.reserve(size);
    RoundMatrix();
}

float MatrixND::Trace() const
{
    float trace = 0.f;
    int index = 0;

    for (int i = 0; i < lines; ++i)
    {
        index = i * columns + i;
        if (index < size)
            trace += m[index];
        else
            return trace;
    }
    return trace;
}

MatrixND MatrixND::Opposite() const
{
    std::vector<float> _m;

    for (float f : m)
        _m.push_back(-f);

    return MatrixND(lines, columns, _m);
}

MatrixND MatrixND::Transposite() const
{
    std::vector<float> _m;

    for (int i = 0; i < columns; ++i)
        for (int j = 0; j < lines; ++j)
            _m.push_back(m[j * columns + i]);

    return MatrixND(columns, lines, _m);
}

MatrixND MatrixND::AddMatrix(const MatrixND& mat) const
{
    if (mat.lines != lines || mat.columns != columns)
        return *this;

    std::vector<float> _m;

    for (int i = 0; i < size; ++i)
        _m[i] = m[i] + mat.m[i];

    return MatrixND(lines, columns, _m);
}

MatrixND MatrixND::AddMatrix(const Matrix2x2& mat) const
{
    if (lines != 2 || columns != 2)
        return *this;

    std::vector<float> _m;

    for (int i = 0; i < 4; ++i)
        _m.push_back(m[i] + mat.m[i]);

    return MatrixND(lines, columns, _m);
}

MatrixND MatrixND::AddMatrix(const Matrix3x3& mat) const
{
    if (lines != 3 || columns != 3)
        return *this;

    std::vector<float> _m;

    for (int i = 0; i < 9; ++i)
        _m.push_back(m[i] + mat.m[i]);

    return MatrixND(lines, columns, _m);
}

MatrixND MatrixND::AddMatrix(const Matrix4x4& mat) const
{
    if (lines != 4 || columns != 4)
        return *this;

    std::vector<float> _m;

    for (int i = 0; i < 16; ++i)
        _m.push_back(m[i] + mat.m[i]);

    return MatrixND(lines, columns, _m);
}

MatrixND MatrixND::ExpandRight(const MatrixND& mat) const
{
    if (mat.lines != lines)
        return *this;

    std::vector<float> _m;

    for (int i = 0; i < lines; ++i)
    {
        for (int j = 0; j < columns; ++j)
            _m.push_back(m[i * columns + j]);

        for (int j = 0; j < mat.columns; ++j)
            _m.push_back(mat.m[i * mat.columns + j]);
    }

    return MatrixND(lines, columns + mat.columns, _m);
}

MatrixND MatrixND::Identity(int lines, int columns)
{
    std::vector<float> coords;
    int index = 0;

    for (int i = 0; i < lines; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            index = i * columns + i;

            if (i * columns + j == index)
                coords.push_back(1.f);
            else
                coords.push_back(0.f);
        }
    }
    return MatrixND(lines, columns, coords);
}

MatrixND Core::Maths::MatrixND::Zero(int lines, int columns)
{
    std::vector<float> coords;
    int index = 0;

    for (int i = 0; i < lines; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            coords.push_back(0.f);
        }
    }

    return MatrixND(lines, columns, coords);
}

MatrixND MatrixND::Pivot() const
{
    std::vector<float> _m = m;

    int r = -1;
    for (int j = 0; j < std::min(lines, columns); ++j)
    {
        int k = j;

        for (int i = j; i < lines; ++i)
            if (std::abs(_m[i * columns + j]) > std::abs(_m[k * columns + j]))
                k = i;

        if (IsEqualZero(_m[k * columns + j]))
            continue;

        ++r;

        if (k != r)
            for (int i = 0; i < columns; ++i)
                std::swap(_m[r * columns + i], _m[k * columns + i]);

        float pivot = _m[r * columns + j];
        if (!IsEqualZero(pivot))
            for (int i = 0; i < columns; ++i)
                _m[r * columns + i] /= pivot;

        for (int i = 0; i < lines; ++i)
        {
            if (i != r)
            {
                float factor = _m[i * columns + j];
                for (int l = 0; l < columns; ++l)
                    _m[i * columns + l] -= factor * _m[r * columns + l];
            }
        }
    }

    return MatrixND(lines, columns, _m);
}

MatrixND MatrixND::Inverse() const
{
    if (lines != columns || IsEqualZero(Determinant()))
        return *this;

    std::vector<float> _m;
    int width = columns * 2;

    MatrixND mat(lines, width, ExpandRight(Identity(lines, columns)).m);
    mat = mat.Pivot();

    for (int i = 0; i < lines; ++i)
    {
        for (int j = columns; j < width; ++j)
            _m.push_back(mat.m[i * width + j]);
    }

    return MatrixND(lines, columns, _m);
}

void MatrixND::Print() const
{
    for (int i = 0; i < size; ++i)
    {
        if ((i+1) % columns == 1 && i != 0)
            std::cout << std::endl;
        std::cout << m[i] << " ";
    }
}

void MatrixND::RoundMatrix()
{
    for (int i = 0; i < size; ++i)
        if (NearZero(m[i]))
            m[i] = 0.f;
}

bool MatrixND::NearZero(float num) const
{
    if (std::fabs(num) < 0.00001f)
        return true;
    else
        return false;
}

MatrixND MatrixND::MultiplyScalar(float f) const
{
    std::vector<float> _m;

    for (int i = 0; i < size; ++i)
        _m.push_back(m[i] * f);

    return MatrixND(lines, columns, _m);
}

MatrixND MatrixND::MultiplyMatrix(const MatrixND& mat) const
{
    if (mat.lines != columns)
        return *this;

    std::vector<float> _m;

    for (int i = 0; i < lines; ++i)
    {
        for (int j = 0; j < mat.columns; ++j)
        {
            _m.push_back(0.f);
            for (int k = 0; k < columns; ++k)
            {
                _m[i * mat.columns + j] += m[i * columns + k] * mat.m[k * mat.columns + j];
            }
        }
    }
    return MatrixND(lines, mat.columns, _m);
}

MatrixND MatrixND::MultiplyMatrix(const Matrix2x2& mat) const
{
    if (columns != 2)
        return *this;

    std::vector<float> _m;

    for (int i = 0; i < lines; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            _m.push_back(0.f);
            for (int k = 0; k < columns; ++k)
            {
                _m[i * 2 + j] += m[i * 2 + k] * mat.m[k * 2 + j];
            }
        }
    }
    return MatrixND(lines, 2, _m);
}

MatrixND MatrixND::MultiplyMatrix(const Matrix3x3& mat) const
{
    if (columns != 3)
        return *this;

    std::vector<float> _m;

    for (int i = 0; i < lines; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            _m.push_back(0.f);
            for (int k = 0; k < columns; ++k)
            {
                _m[i * 3 + j] += m[i * 3 + k] * mat.m[k * 3 + j];
            }
        }
    }
    return MatrixND(lines, 3, _m);
}

MatrixND MatrixND::MultiplyMatrix(const Matrix4x4& mat) const
{
    if (columns != 4)
        return *this;

    std::vector<float> _m;

    for (int i = 0; i < lines; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            _m.push_back(0.f);
            for (int k = 0; k < columns; ++k)
            {
                _m[i * 4 + j] += m[i * 4 + k] * mat.m[k * 4 + j];
            }
        }
    }
    return MatrixND(lines, 2, _m);
}

MatrixND MatrixND::ReduceMatrix(int line, int column) const
{
    std::vector<float> _m;

    for (int i = 0; i < lines; ++i)
    {
        if (i == line)
            continue;

        for (int j = 0; j < columns; ++j)
        {
            if (j == column)
                continue;

            _m.push_back(m[i * columns + j]);
        }
    }
    return MatrixND(lines - 1, columns - 1, _m);
}

float MatrixND::Determinant() const
{
    if (lines == 2)
        return m[0] * m[3] - m[2] * m[1];
       
    float det = 0.f;
    for (int i = 0; i < lines; ++i)
    {
        MatrixND matReduced = ReduceMatrix(i, 0);
        det += (i % 2 == 0 ? 1 : -1) * m[i * columns] * matReduced.Determinant();
    }
    return det;
}

bool MatrixND::operator==(const MatrixND& mPrime)
{
    if (lines != mPrime.lines || columns != mPrime.columns)
        return false;

    for (int i = 0; i < size; ++i)
    {
        if (!IsEqual(m[i], mPrime.m[i]))
            return false;
    }
    return true;
}

float MatrixND::operator[](int index)
{
    if (index < 0 || index >= size)
        return 0.0f;

    return m[index];
}

MatrixND MatrixND::operator+(const MatrixND& mPrime)
{
    return AddMatrix(mPrime);
}

MatrixND MatrixND::operator+(float x)
{
    MatrixND result(lines, columns);
    for (int i = 0; i < size; ++i)
        result.m[i] = m[i] + x;
    return result;
}

void MatrixND::operator+=(const MatrixND& mPrime)
{
    if (lines != mPrime.lines || columns != mPrime.columns)
        return;

    for (int i = 0; i < size; ++i)
        m[i] += mPrime.m[i];
}

void MatrixND::operator+=(float x)
{
    for (int i = 0; i < size; ++i)
        m[i] += x;
}

MatrixND MatrixND::operator-(const MatrixND& mPrime)
{
    if (lines != mPrime.lines || columns != mPrime.columns)
        return MatrixND::Zero(lines, columns);

    MatrixND result(lines, columns);
    for (int i = 0; i < size; ++i)
        result.m[i] = m[i] - mPrime.m[i];
    return result;
}

MatrixND MatrixND::operator-(float x)
{
    MatrixND result(lines, columns);
    for (int i = 0; i < size; ++i)
        result.m[i] = m[i] - x;
    return result;
}

void MatrixND::operator-=(const MatrixND& mPrime)
{
    if (lines != mPrime.lines || columns != mPrime.columns)
        return;

    for (int i = 0; i < size; ++i)
        m[i] -= mPrime.m[i];
}

void MatrixND::operator-=(float x)
{
    for (int i = 0; i < size; ++i)
        m[i] -= x;
}

MatrixND MatrixND::operator*(const MatrixND& mPrime)
{
    return MultiplyMatrix(mPrime);
}

MatrixND MatrixND::operator*(float x)
{
    MatrixND result(lines, columns);
    for (int i = 0; i < size; ++i)
        result.m[i] = m[i] * x;
    return result;
}

void MatrixND::operator*=(float x)
{
    for (int i = 0; i < size; ++i)
        m[i] *= x;
}

MatrixND MatrixND::operator/(float x)
{
    if (IsEqualZero(x))
        return MatrixND::Zero(lines, columns);

    MatrixND result(lines, columns);
    for (int i = 0; i < size; ++i)
        result.m[i] = m[i] / x;
    return result;
}

void MatrixND::operator/=(float x)
{
    if (IsEqualZero(x))
        return;

    for (int i = 0; i < size; ++i)
        m[i] /= x;
}

MatrixND MatrixND::operator/(const MatrixND& mPrime)
{
    if (lines != mPrime.lines || columns != mPrime.columns)
        return MatrixND::Zero(lines, columns);

    MatrixND result(lines, columns);
    for (int i = 0; i < size; ++i)
    {
        if (IsEqualZero(mPrime.m[i])) 
            return MatrixND::Zero(lines, columns);
        result.m[i] = m[i] / mPrime.m[i];
    }
    return result;
}

#pragma endregion