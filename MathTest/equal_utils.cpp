#include "equal_utils.h"

void EXPECT_VEC2_EQ(const Vector2D& myVec, const glm::vec2& glmVec)
{
    EXPECT_FLOAT_EQ(myVec.x, glmVec.x);
    EXPECT_FLOAT_EQ(myVec.y, glmVec.y);
}

void EXPECT_VEC3_EQ(const Vector3D& myVec, const glm::vec3& glmVec)
{
    EXPECT_FLOAT_EQ(myVec.x, glmVec.x);
    EXPECT_FLOAT_EQ(myVec.y, glmVec.y);
    EXPECT_FLOAT_EQ(myVec.z, glmVec.z);
}

void EXPECT_VEC4_EQ(const Vector4D& myVec, const glm::vec4& glmVec)
{
    EXPECT_FLOAT_EQ(myVec.x, glmVec.x);
    EXPECT_FLOAT_EQ(myVec.y, glmVec.y);
    EXPECT_FLOAT_EQ(myVec.z, glmVec.z);
    EXPECT_FLOAT_EQ(myVec.w, glmVec.w);
}