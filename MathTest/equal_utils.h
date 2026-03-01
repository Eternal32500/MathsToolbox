#pragma once

#include <gtest/gtest.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include "vector.h"

using namespace Core::Maths;

void EXPECT_VEC2_EQ(const Vector2D& myVec, const glm::vec2& glmVec);
void EXPECT_VEC3_EQ(const Vector3D& myVec, const glm::vec3& glmVec);
void EXPECT_VEC4_EQ(const Vector4D& myVec, const glm::vec4& glmVec);
