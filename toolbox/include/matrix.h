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
			float m[4];

			static Matrix2x2 Identity();

			Matrix2x2(float _m[4]);
			~Matrix2x2() = default;

			Vector2D Diagonal() const;
			float Trace() const;
			Matrix2x2 Opposite() const;
			Matrix2x2 Transpose() const;
			Matrix2x2 AddMatrix(const Matrix2x2& mat) const;
			Matrix2x2 AddMatrix(const MatrixND& mat) const;
			Matrix2x2 MultiplyScalar(float f) const;
			Matrix2x2 MultiplyMatrix(const Matrix2x2& mat) const;
			MatrixND MultiplyMatrix(const MatrixND& mat) const;
			Vector2D MultriplyVector2D(Vector2D& vec) const;
			float Determinant() const;
			MatrixND ExpandRight(const Matrix2x2& mat) const;
			MatrixND ExpandRight(const MatrixND& mat) const;
			Matrix2x2 Pivot() const;
			Matrix2x2 Inverse() const;
			Matrix3x3 Translate(Vector3D p);
			Matrix2x2 Rotate2DOrigin(float angle) const;
			Matrix3x3 Rotate2DPoint(float angle, Vector2D p);

			void Print() const;

			Vector2D operator*(Vector2D& v);

		private:
			void RoundMatrix();
			bool NearZero(float num) const;
		};

		class Matrix3x3
		{
		public:
			float m[9];

			static Matrix3x3 Identity();

			Matrix3x3(float _m[9]);
			Matrix3x3(float, float, float, float, float, float, float, float, float);
			Matrix3x3(Matrix4x4 mat);
			~Matrix3x3() = default;

			Vector3D Diagonal() const;
			float Trace() const;
			Matrix3x3 Opposite() const;
			Matrix3x3 Transpose() const;
			Matrix3x3 AddMatrix(const Matrix3x3& mat) const;
			Matrix3x3 AddMatrix(const MatrixND& mat) const;
			Matrix3x3 MultiplyScalar(float f) const;
			Matrix3x3 MultiplyMatrix(const Matrix3x3& mat) const;
			MatrixND MultiplyMatrix(const MatrixND& mat) const;
			Vector3D MultriplyVector3D(Vector3D& vec) const;
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

			Vector3D operator*(Vector3D& v);
			Matrix3x3 operator*(const Matrix3x3& m);

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
			float m[16];

			static Matrix4x4 Identity();

			Matrix4x4();
			Matrix4x4(Matrix3x3 mat);
			Matrix4x4(float _m[16]);
			Matrix4x4(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
			~Matrix4x4() = default;

			Vector4D Diagonal() const;
			float Trace() const;
			Matrix4x4 Opposite() const;
			Matrix4x4 Transpose() const;
			Matrix4x4 AddMatrix(const Matrix4x4& mat) const;
			Matrix4x4 AddMatrix(const MatrixND& mat) const;
			Matrix4x4 MultiplyScalar(float f) const;
			Matrix4x4 MultiplyMatrix(const Matrix4x4& mat) const;
			MatrixND MultiplyMatrix(const MatrixND& mat) const;
			Vector4D MultriplyVector4D(Vector4D& vec) const;
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

			bool operator==(const Matrix4x4& other);

			Vector4D operator*(Vector4D& v);
			Matrix4x4 operator*(const Matrix4x4& v);

		private:
			void RoundMatrix();
			bool NearZero(float num) const;
		};
	}
}
