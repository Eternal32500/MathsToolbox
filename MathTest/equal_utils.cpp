#include "equal_utils.h"
#include "utility.h"

void EXPECT_VEC2_EQ(const Vector2D& myVec, const glm::vec2& glmVec)
{
    EXPECT_FLOAT_EQ(myVec.x, glmVec.x);
    EXPECT_FLOAT_EQ(myVec.y, glmVec.y);
}

void EXPECT_VEC3_EQ(const Vector3D& myVec, const glm::vec3& glmVec)
{
    EXPECT_NEAR(myVec.x, glmVec.x, 1e-06);
    EXPECT_NEAR(myVec.y, glmVec.y, 1e-06);
    EXPECT_NEAR(myVec.z, glmVec.z, 1e-06);
}

void EXPECT_VEC4_EQ(const Vector4D& myVec, const glm::vec4& glmVec)
{
    EXPECT_FLOAT_EQ(myVec.x, glmVec.x);
    EXPECT_FLOAT_EQ(myVec.y, glmVec.y);
    EXPECT_FLOAT_EQ(myVec.z, glmVec.z);
    EXPECT_FLOAT_EQ(myVec.w, glmVec.w);
}

void EXPECT_MAT2_EQ(const Matrix2x2& myMat, const glm::mat2& glmMat)
{
    EXPECT_FLOAT_EQ(myMat.m[0], glmMat[0][0]);
    EXPECT_FLOAT_EQ(myMat.m[1], glmMat[0][1]);
    EXPECT_FLOAT_EQ(myMat.m[2], glmMat[1][0]);
    EXPECT_FLOAT_EQ(myMat.m[3], glmMat[1][1]);
}

void EXPECT_MAT3_EQ(const Matrix3x3& myMat, const glm::mat3& glmMat)
{
    EXPECT_NEAR(myMat.m[0], glmMat[0][0], 1e-05);
    EXPECT_NEAR(myMat.m[1], glmMat[0][1], 1e-05);
    EXPECT_NEAR(myMat.m[2], glmMat[0][2], 1e-05);

    EXPECT_NEAR(myMat.m[3], glmMat[1][0], 1e-05);
    EXPECT_NEAR(myMat.m[4], glmMat[1][1], 1e-05);
    EXPECT_NEAR(myMat.m[5], glmMat[1][2], 1e-05);

    EXPECT_NEAR(myMat.m[6], glmMat[2][0], 1e-05);
    EXPECT_NEAR(myMat.m[7], glmMat[2][1], 1e-05);
    EXPECT_NEAR(myMat.m[8], glmMat[2][2], 1e-05);
}

void EXPECT_MAT4_EQ(const Matrix4x4& myMat, const glm::mat4& glmMat)
{
    EXPECT_FLOAT_EQ(myMat.m[0],  glmMat[0][0]);
    EXPECT_FLOAT_EQ(myMat.m[1],  glmMat[0][1]);
    EXPECT_FLOAT_EQ(myMat.m[2],  glmMat[0][2]);
    EXPECT_FLOAT_EQ(myMat.m[3],  glmMat[0][3]);
    EXPECT_FLOAT_EQ(myMat.m[4],  glmMat[1][0]);
    EXPECT_FLOAT_EQ(myMat.m[5],  glmMat[1][1]);
    EXPECT_FLOAT_EQ(myMat.m[6],  glmMat[1][2]);
    EXPECT_FLOAT_EQ(myMat.m[7],  glmMat[1][3]);
    EXPECT_FLOAT_EQ(myMat.m[8],  glmMat[2][0]);
    EXPECT_FLOAT_EQ(myMat.m[9],  glmMat[2][1]);
    EXPECT_FLOAT_EQ(myMat.m[10], glmMat[2][2]);
    EXPECT_FLOAT_EQ(myMat.m[11], glmMat[2][3]);
    EXPECT_FLOAT_EQ(myMat.m[12], glmMat[3][0]);
    EXPECT_FLOAT_EQ(myMat.m[13], glmMat[3][1]);
    EXPECT_FLOAT_EQ(myMat.m[14], glmMat[3][2]);
    EXPECT_FLOAT_EQ(myMat.m[15], glmMat[3][3]);
}
