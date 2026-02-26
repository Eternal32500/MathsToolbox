#pragma once

#include "vector.h"

namespace Core
{
	namespace Maths
	{
		class Matrix3x3;
		class Matrix4x4;
		class MatrixND;

		class Matrix2x2
		{
		public:
			float m[4] = {
				0.0f, 0.0f,
				0.0f, 0.0f
			};

			static const Matrix2x2 Identity;
			static const Matrix2x2 Zero;

			Matrix2x2();
			Matrix2x2(float _m[4]);
			Matrix2x2(std::vector<float> vertex);
			Matrix2x2(const Vector2D& v1, const Vector2D& v2);
			Matrix2x2(float n1, float n2, float n3, float n4);
			Matrix2x2(float components);

			float Trace() const;
			float Determinant() const;
			Vector2D Diagonal() const;
			Matrix2x2 Opposite() const;
			Matrix2x2 Transposite() const;
			Matrix2x2 AddMatrix(const Matrix2x2& mat) const;
			Matrix2x2 AddMatrix(const MatrixND& mat) const;
			Matrix2x2 MultiplyScalar(float f) const;
			Matrix2x2 MultiplyMatrix(const Matrix2x2& mat) const;
			MatrixND MultiplyMatrix(const MatrixND& mat) const;
			Vector2D MultriplyVector2D(const Vector2D& vec) const;
			MatrixND ExpandRight(const Matrix2x2& mat) const;
			MatrixND ExpandRight(const MatrixND& mat) const;
			Matrix2x2 Pivot() const;
			Matrix2x2 Inverse() const;
			Matrix3x3 Translate(Vector3D p);
			Matrix2x2 Rotate2DOrigin(float angle) const;
			Matrix3x3 Rotate2DPoint(float angle, Vector2D p);

			void Print() const;

			Vector2D operator*(Vector2D& v);

			bool operator==(const Matrix2x2&);
			float operator[](int);

			Matrix2x2 operator+(const Matrix2x2&);
			Matrix2x2 operator+(const MatrixND&);
			Matrix2x2 operator+(float);
			void operator+=(const Matrix2x2&);
			void operator+=(const MatrixND&);
			void operator+=(float);

			Matrix2x2 operator-(const Matrix2x2&);
			Matrix2x2 operator-(const MatrixND&);
			Matrix2x2 operator-(float);
			void operator-=(const Matrix2x2&);
			void operator-=(const MatrixND&);
			void operator-=(float);

			Matrix2x2 operator*(const Matrix2x2&);
			MatrixND operator*(const MatrixND&);
			Vector2D operator*(const Vector2D&);
			Matrix2x2 operator*(float);
			void operator*=(const Matrix2x2&);
			void operator*=(float);

			Matrix2x2 operator/(float);
			Matrix2x2 operator/(const Matrix2x2&);
			void operator/=(float);
			void operator/=(const Matrix2x2&);

		private:
			void RoundMatrix();
			bool NearZero(float num) const;
		};

		class Matrix3x3
		{
		public:
			float m[9] {
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f
			};

			static const Matrix3x3 Identity;
			static const Matrix3x3 Zero;

			Matrix3x3();
			Matrix3x3(std::vector<float> vertex);
			Matrix3x3(float _m[9]);
			Matrix3x3(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);
			Matrix3x3(float n1, float n2, float n3,
				float n4, float n5, float n6,
				float n7, float n8, float n9);
			Matrix3x3(float components);
			Matrix3x3(Matrix4x4 mat);

			~Matrix3x3() = default;

			Vector3D Diagonal() const;
			float Trace() const;
			Matrix3x3 Opposite() const;
			Matrix3x3 Transposite() const;
			Matrix3x3 AddMatrix(const Matrix3x3& mat) const;
			Matrix3x3 AddMatrix(const MatrixND& mat) const;
			Matrix3x3 MultiplyScalar(float f) const;
			Matrix3x3 MultiplyMatrix(const Matrix3x3& mat) const;
			MatrixND MultiplyMatrix(const MatrixND& mat) const;
			Vector3D MultiplyVector3D(const Vector3D& vec) const;
			float Determinant() const;
			MatrixND ExpandRight(const Matrix3x3& mat) const;
			MatrixND ExpandRight(const MatrixND& mat) const;
			Matrix3x3 Pivot() const;
			Matrix3x3 Inverse() const;
			Matrix4x4 Translate(Vector3D p) const;
			Matrix3x3 Rotate3DOrigin(float x, float y, float z) const;
			Matrix4x4 Rotate3DPoint(Vector3D p, Vector3D axis, float angle);
			static Matrix3x3 CreateRotation3DMatrix(const Vector3D& rotation);

			void Print() const;

			bool operator==(const Matrix3x3&);
			float operator[](int);

			Matrix3x3 operator+(const Matrix3x3&);
			Matrix3x3 operator+(const MatrixND&);
			Matrix3x3 operator+(float);
			void operator+=(const Matrix3x3&);
			void operator+=(const MatrixND&);
			void operator+=(float);

			Matrix3x3 operator-(const Matrix3x3&);
			Matrix3x3 operator-(const MatrixND&);
			Matrix3x3 operator-(float);
			void operator-=(const Matrix3x3&);
			void operator-=(const MatrixND&);
			void operator-=(float);

			Matrix3x3 operator*(const Matrix3x3&);
			MatrixND operator*(const MatrixND&);
			Vector3D operator*(const Vector3D&);
			Vector3D operator*(Vector3D& v);
			Matrix3x3 operator*(float);
			void operator*=(const Matrix3x3&);
			void operator*=(float);

			Matrix3x3 operator/(float);
			Matrix3x3 operator/(const Matrix3x3&);
			void operator/=(float);
			void operator/=(const Matrix3x3&);

		private:
			void RoundMatrix();
			bool NearZero(float num) const;
			Matrix3x3 Rotate3DXOrigin(float angle) const;
			Matrix3x3 Rotate3DYOrigin(float angle) const;
			Matrix3x3 Rotate3DZOrigin(float angle) const;
			static Matrix3x3 CreateRotationXMatrix(float alpha);
			static Matrix3x3 CreateRotationYMatrix(float alpha);
			static Matrix3x3 CreateRotationZMatrix(float alpha);
		};

		class Matrix4x4
		{
		public:
			static const Matrix4x4 Identity;
			static const Matrix4x4 Zero;

			float m[16];

			Matrix4x4();
			Matrix4x4(std::vector<float> vertex);
			Matrix4x4(float array[16]);
			Matrix4x4(const Vector4D& v1, const Vector4D& v2, const Vector4D& v3, const Vector4D& v4);
			Matrix4x4(float n1, float n2, float n3, float n4,
				float n5, float n6, float n7, float n8,
				float n9, float n10, float n11, float n12,
				float n13, float n14, float n15, float n16);
			Matrix4x4(float components);
			Matrix4x4(const Matrix3x3&);

			Vector4D Diagonal() const;
			float Trace() const;
			Matrix4x4 Opposite() const;
			Matrix4x4 Transposite() const;
			Matrix4x4 AddMatrix(const Matrix4x4& mat) const;
			Matrix4x4 AddMatrix(const MatrixND& mat) const;
			Matrix4x4 MultiplyScalar(float f) const;
			Matrix4x4 MultiplyMatrix(const Matrix4x4& mat) const;
			MatrixND MultiplyMatrix(const MatrixND& mat) const;
			Vector4D MultiplyVector4D(const Vector4D& vec) const;
			float Determinant() const;
			MatrixND ExpandRight(const Matrix4x4& mat) const;
			MatrixND ExpandRight(const MatrixND& mat) const;
			Matrix4x4 Pivot() const;
			Matrix4x4 Inverse() const;
			Matrix4x4 Translate(Vector3D p) const;
			static Matrix4x4 TRS(const Vector3D& position, const Vector3D& rotation, const Vector3D& scale);
			static Matrix4x4 Perspective(float FOV, float aspect, float zNear, float zFar);
			static Matrix4x4 Orthographic(float left, float right, float bottom, float top, float zNear, float zFar);
			static Matrix4x4 LookAt(Vector3D position, Vector3D target, Vector3D up);

			static Matrix4x4 CreateTranslationMatrix(const Vector3D& translation);
			static Matrix4x4 CreateScaleMatrix(const Vector3D& scale);
			static Matrix4x4 CreateXRotationMatrix(float angle);
			static Matrix4x4 CreateYRotationMatrix(float angle);
			static Matrix4x4 CreateZRotationMatrix(float angle);
			static Matrix4x4 CreateRotationMatrix(const Vector3D& rotation);

			void Print() const;

			bool operator==(const Matrix4x4&);
			float operator[](int);

			Matrix4x4 operator+(const Matrix4x4&);
			Matrix4x4 operator+(const MatrixND&);
			Matrix4x4 operator+(float);
			void operator+=(const Matrix4x4&);
			void operator+=(const MatrixND&);
			void operator+=(float);

			Matrix4x4 operator-(const Matrix4x4&);
			Matrix4x4 operator-(const MatrixND&);
			Matrix4x4 operator-(float);
			void operator-=(const Matrix4x4&);
			void operator-=(const MatrixND&);
			void operator-=(float);

			Matrix4x4 operator*(const Matrix4x4&);
			MatrixND operator*(const MatrixND&);
			Vector4D operator*(const Vector4D&);
			Vector4D operator*(Vector4D& v);
			Matrix4x4 operator*(float);
			void operator*=(const Matrix4x4&);
			void operator*=(float);

			Matrix4x4 operator/(float);
			Matrix4x4 operator/(const Matrix4x4&);
			void operator/=(float);
			void operator/=(const Matrix4x4&);

		private:
			void RoundMatrix();
			bool NearZero(float num) const;
		};

		class MatrixND
		{
		public:

			std::vector<float> m;
			int lines = 0;
			int columns = 0;
			int size = 0;

			MatrixND(int _lines, int _columns, std::vector<float> _m);
			MatrixND(int _lines, int _columns);
			~MatrixND() = default;

			float Trace() const;
			MatrixND Opposite() const;
			MatrixND Transposite() const;
			MatrixND AddMatrix(const MatrixND& mat) const;
			MatrixND AddMatrix(const Matrix2x2& mat) const;
			MatrixND AddMatrix(const Matrix3x3& mat) const;
			MatrixND AddMatrix(const Matrix4x4& mat) const;
			MatrixND MultiplyScalar(float f) const;
			MatrixND MultiplyMatrix(const MatrixND& mat) const;
			MatrixND MultiplyMatrix(const Matrix2x2& mat) const;
			MatrixND MultiplyMatrix(const Matrix3x3& mat) const;
			MatrixND MultiplyMatrix(const Matrix4x4& mat) const;
			float Determinant() const;
			MatrixND ExpandRight(const MatrixND& mat) const;
			static MatrixND Identity(int lines, int columns);
			static MatrixND Zero(int lines, int columns);
			MatrixND Pivot() const;
			MatrixND Inverse() const;

			void Print() const;

			bool operator==(const MatrixND& mPrime);
			float operator[](int index);

			MatrixND operator+(const MatrixND& mPrime);
			MatrixND operator+(float x);
			void operator+=(const MatrixND& mPrime);
			void operator+=(float x);

			MatrixND operator-(const MatrixND& mPrime);
			MatrixND operator-(float x);
			void operator-=(const MatrixND& mPrime);
			void operator-=(float x);

			MatrixND operator*(const MatrixND& mPrime);
			MatrixND operator*(float x);
			void operator*=(float x);

			MatrixND operator/(float x);
			MatrixND operator/(const MatrixND& mPrime);
			void operator/=(float x);

		private:
			void RoundMatrix();
			bool NearZero(float num) const;
			MatrixND ReduceMatrix(int line, int column) const;
		};
	}
}