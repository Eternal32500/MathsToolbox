#include "../include/equal_utils.h"

Matrix2x2 m2 = Matrix2x2(2.f, 3.f, 4.f, 5.f);
Matrix2x2 m2_2 = Matrix2x2(6.f, 7.f, 8.f, 9.f);
Vector2D v2m = Vector2D(2.f, 3.f);

glm::mat2 g2 = glm::mat2(2.f, 3.f, 4.f, 5.f);
glm::mat2 g2_2 = glm::mat2(6.f, 7.f, 8.f, 9.f);
glm::vec2 v2g = glm::vec2(2.f, 3.f);


Matrix3x3 m3 = Matrix3x3(2.f, 3.f, 1.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
Matrix3x3 m3_2 = Matrix3x3(12.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f);
Vector3D v3m = Vector3D(2.f, 3.f, 4.f);

glm::mat3 g3 = glm::mat3(2.f, 3.f, 1.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
glm::mat3 g3_2 = glm::mat3(12.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f);
glm::vec3 v3g = glm::vec3(2.f, 3.f, 4.f);


Matrix4x4 m4 = Matrix4x4(2.f, 3.f, 4.f, 2.f, 5.f, 6.f, 7.f, 8.f, 1.f, 10.f, 11.f, 12.f, 12.f, 14.f, 10.f, 16.f);
Matrix4x4 m4_2 = Matrix4x4(19.f, 18.f, 17.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f, 32.f);
Vector4D v4m = Vector4D(2.f, 3.f, 4.f, 5.f);

glm::mat4 g4 = glm::mat4(2.f, 3.f, 4.f, 2.f, 5.f, 6.f, 7.f, 8.f, 1.f, 10.f, 11.f, 12.f, 12.f, 14.f, 10.f, 16.f);
glm::mat4 g4_2 = glm::mat4(19.f, 18.f, 17.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f, 32.f);
glm::vec4 v4g = glm::vec4(2.f, 3.f, 4.f, 5.f);


float f = 2.8f;
float alpha = 45.f;

#pragma region Matrix2x2Tests

TEST(Matrix2x2Test, Trace)
{
    EXPECT_FLOAT_EQ(m2.Trace(), g2[0][0] + g2[1][1]);
}

TEST(Matrix2x2Test, Determinant)
{
    EXPECT_FLOAT_EQ(m2.Determinant(), glm::determinant(g2));
}

TEST(Matrix2x2Test, Diagonal)
{
    EXPECT_VEC2_EQ(m2.Diagonal(), glm::vec2(g2[0][0], g2[1][1]));
}

TEST(Matrix2x2Test, Opposite)
{
    EXPECT_MAT2_EQ(m2.Opposite(), -g2);
}

TEST(Matrix2x2Test, Transposite)
{
    EXPECT_MAT2_EQ(m2.Transposite(), glm::transpose(g2));
}

TEST(Matrix2x2Test, Inverse)
{
    EXPECT_MAT2_EQ(m2_2.Inverse(), glm::inverse(g2_2));
}

TEST(Matrix2x2Test, Transforms)
{
    glm::mat2 scaleMatrix = glm::mat2(2.0f, 0.0f,
                            0.0f, 0.5f);

    glm::mat3 rot3 = glm::rotate(glm::mat4(1.0f), glm::radians(alpha), glm::vec3(0.f, 0.f, 1.f));
    glm::mat2 rotationMatrix = glm::mat2(rot3);

    EXPECT_MAT2_EQ(Matrix2x2::ScaleMatrix(2.f, 0.5f), scaleMatrix);
    EXPECT_MAT2_EQ(Matrix2x2::RotateMatrix(alpha), rotationMatrix);
}

TEST(Matrix2x2Test, Operators)
{
    EXPECT_MAT2_EQ(m2 + m2_2, g2 + g2_2);
    EXPECT_MAT2_EQ(m2 - m2_2, g2 - g2_2);
    EXPECT_MAT2_EQ(m2 * m2_2, g2 * g2_2);
    EXPECT_MAT2_EQ(m2 / m2_2, g2 / g2_2);

    EXPECT_MAT2_EQ(m2 + f, g2 + f);
    EXPECT_MAT2_EQ(m2 - f, g2 - f);
    EXPECT_MAT2_EQ(m2 * f, g2 * f);
    EXPECT_MAT2_EQ(m2 / f, g2 / f);

    EXPECT_VEC2_EQ(m2 * v2m, g2 * v2g);

    EXPECT_FLOAT_EQ(m2[1], g2[0][1]);

    EXPECT_MAT2_EQ(-m2, -g2);

    EXPECT_MAT2_EQ(Matrix2x2::Identity, glm::mat2(1.f));
    EXPECT_MAT2_EQ(Matrix2x2::Zero, glm::mat2(0.f));
}

TEST(Matrix2x2Test, Constants)
{
    EXPECT_MAT2_EQ(Matrix2x2::Identity, glm::mat2(1.f));
    EXPECT_MAT2_EQ(Matrix2x2::Zero, glm::mat2(0.f));
}

#pragma endregion

#pragma region Matrix2x2Tests

TEST(Matrix3x3Test, Trace)
{
    EXPECT_FLOAT_EQ(m3.Trace(), g3[0][0] + g3[1][1] + g3[2][2]);
}

TEST(Matrix3x3Test, Determinant)
{
    EXPECT_FLOAT_EQ(m3.Determinant(), glm::determinant(g3));
}

TEST(Matrix3x3Test, Diagonal)
{
    EXPECT_VEC3_EQ(m3.Diagonal(), glm::vec3(g3[0][0], g3[1][1], g3[2][2]));
}

TEST(Matrix3x3Test, Opposite)
{
    EXPECT_MAT3_EQ(m3.Opposite(), -g3);
}

TEST(Matrix3x3Test, Transposite)
{
    EXPECT_MAT3_EQ(m3.Transposite(), glm::transpose(g3));
}

TEST(Matrix3x3Test, Inverse)
{
    EXPECT_MAT3_EQ(m3.Inverse(), glm::inverse(g3));
}

TEST(Matrix3x3Test, Transforms)
{
    EXPECT_MAT3_EQ(Matrix3x3::TranslateMatrix((1.f, 1.f, 1.f)), glm::translate(glm::mat4(1.f), glm::vec3(1.f, 1.f, 1.f)));

    EXPECT_MAT3_EQ(Matrix3x3::RotationXMatrix(alpha), glm::rotate(glm::mat4(1.f), glm::radians(alpha), glm::vec3(1.f, 0.f, 0.f)));
    EXPECT_MAT3_EQ(Matrix3x3::RotationYMatrix(alpha), glm::rotate(glm::mat4(1.f), glm::radians(alpha), glm::vec3(0.f, 1.f, 0.f)));
    EXPECT_MAT3_EQ(Matrix3x3::RotationZMatrix(alpha), glm::rotate(glm::mat4(1.f), glm::radians(alpha), glm::vec3(0.f, 0.f, 1.f)));

    float alphaY = 30.f;
    float alphaZ = 90.f;

    glm::mat4 rotation = glm::rotate(glm::mat4(1.f), glm::radians(alpha), glm::vec3(1.f, 0.f, 0.f));
    rotation = glm::rotate(rotation, glm::radians(alphaY), glm::vec3(0.f, 1.f, 0.f));
    rotation = glm::rotate(rotation, glm::radians(alphaZ), glm::vec3(0.f, 0.f, 1.f));

    EXPECT_MAT3_EQ(Matrix3x3::RotationMatrixEuler(alpha, alphaY, alphaZ), rotation);
    EXPECT_MAT3_EQ(Matrix3x3::ScaleMatrix(5.f, 7.f, 2.f), glm::scale(glm::mat4(1.f), glm::vec3(5.f, 7.f, 2.f)));
}

TEST(Matrix3x3Test, Operators)
{
    EXPECT_MAT3_EQ(m3 + m3_2, g3 + g3_2);
    EXPECT_MAT3_EQ(m3 - m3_2, g3 - g3_2);
    EXPECT_MAT3_EQ(m3 * m3_2, g3 * g3_2);
    EXPECT_MAT3_EQ(m3 / m3_2, g3 / g3_2);

    EXPECT_MAT3_EQ(m3 + f, g3 + f);
    EXPECT_MAT3_EQ(m3 - f, g3 - f);
    EXPECT_MAT3_EQ(m3 * f, g3 * f);
    EXPECT_MAT3_EQ(m3 / f, g3 / f);

    EXPECT_VEC3_EQ(m3 * v3m, g3 * v3g);

    EXPECT_FLOAT_EQ(m3[2], g3[0][2]);

    EXPECT_MAT3_EQ(-m3, -g3);
}

TEST(Matrix3x3Test, Constants)
{
    EXPECT_MAT3_EQ(Matrix3x3::Identity, glm::mat3(1.f));
    EXPECT_MAT3_EQ(Matrix3x3::Zero, glm::mat3(0.f));
}

#pragma endregion

#pragma region Matrix4x4Tests

TEST(Matrix4x4Test, Trace)
{
    EXPECT_FLOAT_EQ(m4.Trace(), g4[0][0] + g4[1][1] + g4[2][2] + g4[3][3]);
}

TEST(Matrix4x4Test, Determinant)
{
    EXPECT_FLOAT_EQ(m4.Determinant(), glm::determinant(g4));
}

TEST(Matrix4x4Test, Diagonal)
{
    EXPECT_VEC4_EQ(m4.Diagonal(), glm::vec4(g4[0][0], g4[1][1] ,g4[2][2] ,g4[3][3]));
}

TEST(Matrix4x4Test, Opposite)
{
    EXPECT_MAT4_EQ(m4.Opposite(), -g4);
}

TEST(Matrix4x4Test, Transposite)
{
    EXPECT_MAT4_EQ(m4.Transposite(), glm::transpose(g4));
}

TEST(Matrix4x4Test, Inverse)
{
    EXPECT_MAT4_EQ(m4.Inverse(), glm::inverse(g4));
}

TEST(Matrix4x4Test, Perspective)
{
    EXPECT_MAT4_EQ(Matrix4x4::Perspective(45.f, 1920.f/1080.f, 0.01f, 1000.f), glm::perspective(45.f, 1920.f / 1080.f, 0.01f, 1000.f));
}

TEST(Matrix4x4Test, Orthographic)
{
    EXPECT_MAT4_EQ(Matrix4x4::Orthographic(-1.f, 1.f, -1.f, 1.f, 0.01f, 1000.f), glm::ortho(-1.f, 1.f, -1.f, 1.f, 0.01f, 1000.f));
}

TEST(Matrix4x4Test, LookAt)
{
    EXPECT_MAT4_EQ(Matrix4x4::LookAt(Vector3D(2.f, 5.f, 7.f), Vector3D(0.f, 0.f, 0.f), Vector3D::Up), glm::lookAt(glm::vec3(2.f, 5.f, 7.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f)));
}

TEST(Matrix4x4Test, Transforms)
{
    EXPECT_MAT4_EQ(Matrix4x4::TranslateMatrix((1.f, 1.f, 1.f)), glm::translate(glm::mat4(1.f), glm::vec3(1.f, 1.f, 1.f)));

    EXPECT_MAT4_EQ(Matrix4x4::RotationXMatrix(alpha), glm::rotate(glm::mat4(1.f), glm::radians(alpha), glm::vec3(1.f, 0.f, 0.f)));
    EXPECT_MAT4_EQ(Matrix4x4::RotationYMatrix(alpha), glm::rotate(glm::mat4(1.f), glm::radians(alpha), glm::vec3(0.f, 1.f, 0.f)));
    EXPECT_MAT4_EQ(Matrix4x4::RotationZMatrix(alpha), glm::rotate(glm::mat4(1.f), glm::radians(alpha), glm::vec3(0.f, 0.f, 1.f)));
    
    float alphaY = 30.f;
    float alphaZ = 90.f;
    
    glm::mat4 rotation = glm::rotate(glm::mat4(1.f), glm::radians(alpha), glm::vec3(1.f, 0.f, 0.f));
    rotation = glm::rotate(rotation, glm::radians(alphaY), glm::vec3(0.f, 1.f, 0.f));
    rotation = glm::rotate(rotation, glm::radians(alphaZ), glm::vec3(0.f, 0.f, 1.f));
    
    EXPECT_MAT4_EQ(Matrix4x4::RotationMatrixEuler(alpha, alphaY, alphaZ), rotation);
    EXPECT_MAT4_EQ(Matrix4x4::ScaleMatrix(5.f, 7.f, 2.f), glm::scale(glm::mat4(1.f), glm::vec3(5.f, 7.f, 2.f)));
}

TEST(Matrix4x4Test, TRS)
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(1.f, 1.f, 1.f));

    float alphaY = 30.f;
    float alphaZ = 90.f;

    model = glm::rotate(model, glm::radians(alpha), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(alphaY), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(alphaZ), glm::vec3(0, 0, 1));

    model = glm::scale(model, glm::vec3(5.f, 7.f, 2.f));

    EXPECT_MAT4_EQ(Matrix4x4::TRS(Vector3D(1.f, 1.f, 1.f), Vector3D(alpha, alphaY, alphaZ), Vector3D(5.f, 7.f, 2.f)), model);
}

TEST(Matrix4x4Test, Operators)
{
    EXPECT_MAT4_EQ(m4 + m4_2, g4 + g4_2);
    EXPECT_MAT4_EQ(m4 - m4_2, g4 - g4_2);
    EXPECT_MAT4_EQ(m4 * m4_2, g4 * g4_2);
    EXPECT_MAT4_EQ(m4_2 / m4, g4_2 / g4);
    
    EXPECT_MAT4_EQ(m4 + f, g4 + f);
    EXPECT_MAT4_EQ(m4 - f, g4 - f);
    EXPECT_MAT4_EQ(m4 * f, g4 * f);
    EXPECT_MAT4_EQ(m4 / f, g4 / f);
    
    EXPECT_VEC4_EQ(m4 * v4m, g4 * v4g);
    
    EXPECT_FLOAT_EQ(m4[2], g4[0][2]);

    EXPECT_MAT4_EQ(-m4, -g4);
}

TEST(Matrix4x4Test, Constants)
{
    EXPECT_MAT4_EQ(Matrix4x4::Identity, glm::mat4(1.f));
    EXPECT_MAT4_EQ(Matrix4x4::Zero, glm::mat4(0.f));
}

#pragma endregion