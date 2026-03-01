#pragma once

#include <gtest/gtest.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "matrix.h"

using namespace Core::Maths;

void EXPECT_VEC2_EQ(const Vector2D& myVec, const glm::vec2& glmVec);
void EXPECT_VEC3_EQ(const Vector3D& myVec, const glm::vec3& glmVec);
void EXPECT_VEC4_EQ(const Vector4D& myVec, const glm::vec4& glmVec);

void EXPECT_MAT2_EQ(const Matrix2x2& myMat, const glm::mat2& glmMat);
void EXPECT_MAT3_EQ(const Matrix3x3& myMat, const glm::mat3& glmMat);
void EXPECT_MAT4_EQ(const Matrix4x4& myMat, const glm::mat4& glmMat);