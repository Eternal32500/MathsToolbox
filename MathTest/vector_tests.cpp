#include "equal_utils.h"
#include <glm/gtx/vector_angle.hpp>

Vector2D v_2(3.0f, 4.0f);
Vector2D v2_2(5.0f, 6.0f);

glm::vec2 g_2(3.0f, 4.0f);
glm::vec2 g2_2(5.0f, 6.0f);

float maxMagnitude = 1.0f;
float angle = 90.0f;
float scale = 5.0f;
float f = 2.5f;

Vector2D pivotV_2(1.0f, 1.0f);
glm::vec2 pivotG_2(1.0f, 1.0f);

TEST(Vector2DTest, Magnitude) 
{
    EXPECT_FLOAT_EQ(v_2.Magnitude(), glm::length(g_2));
    EXPECT_FLOAT_EQ(v_2.SquaredMagnitude(), glm::dot(g_2, g_2));
    Vector2D vClamped = v_2.ClampMagnitude(maxMagnitude);
    EXPECT_FLOAT_EQ(vClamped.Magnitude(), glm::clamp(glm::length(g_2), 0.f, maxMagnitude));
}

TEST(Vector2DTest, Normalization)
{
    Vector2D normalized = v_2.Normalized();
    EXPECT_VEC2_EQ(normalized, glm::normalize(g_2));
    
    Vector2D temp = v2_2;
    temp.Normalize();
    EXPECT_FLOAT_EQ(temp.Magnitude(), glm::length(glm::normalize(g_2)));
}

TEST(Vector2DTest, DotProduct) 
{
    EXPECT_FLOAT_EQ(v_2.DotProduct(v2_2), glm::dot(g_2, g2_2));
}

TEST(Vector2DTest, Transformations) 
{
    // Translate
    Vector2D newPosV = v_2.Translate(v2_2.x, v2_2.y);
    glm::vec2 newPosG = g_2 + g2_2;
    EXPECT_VEC2_EQ(newPosV, newPosG);
    Vector2D newPosV2 = v_2.Translate(v2_2);
    EXPECT_VEC2_EQ(newPosV2, newPosG);

    // Rotate
    Vector2D rot = v_2.Rotate(angle);
    glm::vec2 rotated;
    rotated.x = v_2.x * glm::cos(glm::radians(angle)) - v_2.y * glm::sin(glm::radians(angle));
    rotated.y = v_2.x * glm::sin(glm::radians(angle)) + v_2.y * glm::cos(glm::radians(angle));
    EXPECT_VEC2_EQ(rot, rotated);

    // Rotate Around
    glm::vec2 translated = g_2 - pivotG_2;
    rotated.x = translated.x * cos(glm::radians(angle)) - translated.y * sin(glm::radians(angle));
    rotated.y = translated.x * sin(glm::radians(angle)) + translated.y * cos(glm::radians(angle));

    EXPECT_VEC2_EQ(v_2.RotateAround(angle, pivotV_2), glm::vec2(rotated.x + pivotG_2.x, rotated.y + pivotG_2.y));

    // Scale
    Vector2D scaledV = v_2.Scale(scale);
    glm::vec2 scaledG = glm::vec2(g_2.x * scale, g_2.y * scale);
    EXPECT_VEC2_EQ(scaledV, scaledG);
    scaledV = v_2.Scale(Vector2D(scale, scale));
    EXPECT_VEC2_EQ(scaledV, scaledG);

    //Scale Around
    scaledV = v_2.ScaleAround(scale, pivotV_2);
    scaledG = (g_2 - pivotG_2) * scale + pivotG_2;
    EXPECT_VEC2_EQ(scaledV, scaledG);
    scaledV = v_2.ScaleAround(Vector2D(scale, scale), pivotV_2);
    EXPECT_VEC2_EQ(scaledV, scaledG);
}

TEST(Vector2DTest, Utils) 
{
    EXPECT_FLOAT_EQ(v_2.Distance(v2_2), glm::distance(g_2, g2_2));

    EXPECT_FLOAT_EQ(v_2.Angle(v2_2), glm::degrees(glm::angle(glm::normalize(g_2), glm::normalize(g2_2))));

    EXPECT_VEC2_EQ(v_2.Opposite(), -g_2);

    EXPECT_VEC2_EQ(Vector2D::Lerp(v_2, v2_2, 0.5f), glm::mix(g_2, g2_2, 0.5f));

    glm::vec2 mid = (g_2 + g2_2) * 0.5f;
    EXPECT_VEC2_EQ(v_2.MidPoint(v2_2), mid);
}

TEST(Vector2DTest, Operators) 
{
    EXPECT_VEC2_EQ(v_2 + v2_2, g_2 + g2_2);
    EXPECT_VEC2_EQ(v_2 + f, g_2 + f);

    EXPECT_VEC2_EQ(v_2 - v2_2, g_2 - g2_2);
    EXPECT_VEC2_EQ(v_2 - f, g_2 - f);

    EXPECT_VEC2_EQ(v_2 * v2_2, g_2 * g2_2);
    EXPECT_VEC2_EQ(v_2 * f, g_2 * f);

    EXPECT_VEC2_EQ(v_2 / v2_2, g_2 / g2_2);
    EXPECT_VEC2_EQ(v_2 / f, g_2 / f);

    EXPECT_VEC2_EQ(v_2 * f, g_2 * f);
    EXPECT_VEC2_EQ(f * v_2, f * g_2);

    EXPECT_VEC2_EQ(-v_2, -g_2);

    EXPECT_FLOAT_EQ(v_2[0], g_2[0]);
}

TEST(Vector2DTest, Constants) 
{
    EXPECT_VEC2_EQ(Vector2D::Zero, glm::vec2(0, 0));
    EXPECT_VEC2_EQ(Vector2D::One, glm::vec2(1, 1));
    EXPECT_VEC2_EQ(Vector2D::Up, glm::vec2(0, 1));
    EXPECT_VEC2_EQ(Vector2D::Down, glm::vec2(0, -1));
    EXPECT_VEC2_EQ(Vector2D::Left, glm::vec2(-1, 0));
    EXPECT_VEC2_EQ(Vector2D::Right, glm::vec2(1, 0));
}

Vector3D v_3(1.0f, 2.0f, 3.0f);
Vector3D v2_3(4.0f, 5.0f, 6.0f);

glm::vec3 g_3(1.0f, 2.0f, 3.0f);
glm::vec3 g2_3(4.0f, 5.0f, 6.0f);

Vector3D pivotV_3(1.0f, 1.0f, 1.0f);
glm::vec3 pivotG_3(1.0f, 1.0f, 1.0f);

TEST(Vector3DTest, Magnitude)
{
    EXPECT_FLOAT_EQ(v_3.Magnitude(), glm::length(g_3));
    EXPECT_FLOAT_EQ(v_3.SquaredMagnitude(), glm::dot(g_3, g_3));
    Vector3D vClamped = v_3.ClampMagnitude(maxMagnitude);
    EXPECT_FLOAT_EQ(vClamped.Magnitude(), glm::clamp(glm::length(g_3), 0.f, maxMagnitude));
}

TEST(Vector3DTest, Normalization)
{
    Vector3D normalized = v_3.Normalized();
    EXPECT_VEC3_EQ(normalized, glm::normalize(g_3));

    Vector3D temp = v_3;
    temp.Normalize();
    EXPECT_FLOAT_EQ(temp.Magnitude(), glm::length(glm::normalize(g_3)));
}

TEST(Vector3DTest, Products)
{
    EXPECT_FLOAT_EQ(v_3.DotProduct(v2_3), glm::dot(g_3, g2_3));
    EXPECT_VEC3_EQ(v_3.CrossProduct(v2_3), glm::cross(g_3, g2_3));
}

TEST(Vector3DTest, Transformations)
{
    // Translate
    EXPECT_VEC3_EQ(v_3.Translate(v2_3.x, v2_3.y, v2_3.z), g_3 + g2_3);
    EXPECT_VEC3_EQ(v_3.Translate(v2_3), g_3 + g2_3);

    // Rotate
    Vector3D axisV(0.0f, 1.0f, 0.0f);
    glm::vec3 axisG(0.0f, 1.0f, 0.0f);

    glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axisG);
    glm::vec3 rotatedG = glm::vec3(rotMat * glm::vec4(g_3, 1.0f));

    EXPECT_VEC3_EQ(v_3.Rotate(angle, axisV), rotatedG);

    // Rotate Around
    glm::vec3 transG = g_3 - pivotG_3;
    glm::vec3 rotAroundG = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(angle), axisG) * glm::vec4(transG, 1.0f)) + pivotG_3;
    EXPECT_VEC3_EQ(v_3.RotateAround(angle, axisV, pivotV_3), rotAroundG);

    // Scale
    EXPECT_VEC3_EQ(v_3.Scale(scale), g_3 * scale);
    EXPECT_VEC3_EQ(v_3.Scale(v2_3), g_3 * g2_3);

    // Scale Around
    glm::vec3 scaleAroundG = (g_3 - pivotG_3) * scale + pivotG_3;
    EXPECT_VEC3_EQ(v_3.ScaleAround(scale, pivotV_3), scaleAroundG);
}

TEST(Vector3DTest, Utils)
{
    EXPECT_FLOAT_EQ(v_3.Distance(v2_3), glm::distance(g_3, g2_3));

    float glmAngle = glm::angle(glm::normalize(g_3), glm::normalize(g2_3));
    EXPECT_FLOAT_EQ(v_3.Angle(v2_3), glm::degrees(glmAngle));

    EXPECT_VEC3_EQ(v_3.Opposite(), -g_3);
    EXPECT_VEC3_EQ(Vector3D::Lerp(v_3, v2_3, 0.5f), glm::mix(g_3, g2_3, 0.5f));
    EXPECT_VEC3_EQ(v_3.MidPoint(v2_3), (g_3 + g2_3) * 0.5f);
}

TEST(Vector3DTest, Operators)
{
    EXPECT_VEC3_EQ(v_3 + v2_3, g_3 + g2_3);
    EXPECT_VEC3_EQ(v_3 - v2_3, g_3 - g2_3);
    EXPECT_VEC3_EQ(v_3 * v2_3, g_3 * g2_3);
    EXPECT_VEC3_EQ(v_3 / v2_3, g_3 / g2_3);

    EXPECT_VEC3_EQ(v_3 * f, g_3 * f);
    EXPECT_VEC3_EQ(f * v_3, f * g_3);
    EXPECT_VEC3_EQ(v_3 / f, g_3 / f);

    EXPECT_TRUE(v_3 == Vector3D(1.0f, 2.0f, 3.0f));
    EXPECT_FLOAT_EQ(v_3[2], g_3[2]);
    EXPECT_VEC3_EQ(-v_3, -g_3);
}

TEST(Vector3DTest, Constants)
{
    EXPECT_VEC3_EQ(Vector3D::Zero, glm::vec3(0, 0, 0));
    EXPECT_VEC3_EQ(Vector3D::One, glm::vec3(1, 1, 1));
    EXPECT_VEC3_EQ(Vector3D::Up, glm::vec3(0, 1, 0));
    EXPECT_VEC3_EQ(Vector3D::Down, glm::vec3(0, -1, 0));
    EXPECT_VEC3_EQ(Vector3D::Left, glm::vec3(-1, 0, 0));
    EXPECT_VEC3_EQ(Vector3D::Right, glm::vec3(1, 0, 0));
}

Vector4D v_4(1.0f, 2.0f, 3.0f, 4.0f);
Vector4D v2_4(5.0f, 6.0f, 7.0f, 8.0f);

glm::vec4 g_4(1.0f, 2.0f, 3.0f, 4.0f);
glm::vec4 g2_4(5.0f, 6.0f, 7.0f, 8.0f);

TEST(Vector4DTest, Magnitude)
{
    EXPECT_FLOAT_EQ(v_4.Magnitude(), glm::length(g_4));
    EXPECT_FLOAT_EQ(v_4.SquaredMagnitude(), glm::dot(g_4, g_4));
}

TEST(Vector4DTest, Normalization)
{
    Vector4D normV = v_4.Normalized();
    glm::vec4 normG = glm::normalize(g_4);
    EXPECT_VEC4_EQ(normV, normG);

    Vector4D temp = v_4;
    temp.Normalize();
    EXPECT_FLOAT_EQ(temp.Magnitude(), glm::length(glm::normalize(g_4)));
    EXPECT_FLOAT_EQ(temp.x, normG.x);
}

TEST(Vector4DTest, DotProduct)
{
    EXPECT_FLOAT_EQ(v_4.DotProduct(v2_4), glm::dot(g_4, g2_4));
}

TEST(Vector4DTest, Utils)
{
    EXPECT_FLOAT_EQ(v_4.Distance(v2_4), glm::distance(g_4, g2_4));

    EXPECT_VEC4_EQ(v_4.Opposite(), -g_4);

    glm::vec4 midG = (g_4 + g2_4) * 0.5f;
    EXPECT_VEC4_EQ(v_4.MidPoint(v2_4), midG);

    EXPECT_VEC4_EQ(Vector4D::Lerp(v_4, v2_4, 0.5f), glm::mix(g_4, g2_4, 0.5f));
}

TEST(Vector4DTest, Transformations)
{
    // Translate
    Vector4D transV(1.f, 1.f, 1.f, 1.f);
    glm::vec4 transG(1.f, 1.f, 1.f, 1.f);

    EXPECT_VEC4_EQ(v_4.Translate(transV), g_4 + transG);
    EXPECT_VEC4_EQ(v_4.Translate(1.f, 1.f, 1.f, 1.f), g_4 + transG);

    // Scale
    EXPECT_VEC4_EQ(v_4.Scale(scale), g_4 * scale);

    Vector4D scaleVecV(2.f, 0.5f, 2.f, 1.f);
    glm::vec4 scaleVecG(2.f, 0.5f, 2.f, 1.f);
    EXPECT_VEC4_EQ(v_4.Scale(scaleVecV), g_4 * scaleVecG);
}

TEST(Vector4DTest, Operators)
{
    EXPECT_VEC4_EQ(v_4 + v2_4, g_4 + g2_4);
    EXPECT_VEC4_EQ(v_4 - v2_4, g_4 - g2_4);
    EXPECT_VEC4_EQ(v_4 * v2_4, g_4 * g2_4);
    EXPECT_VEC4_EQ(v_4 / v2_4, g_4 / g2_4);

    EXPECT_VEC4_EQ(v_4 + f, g_4 + f);
    EXPECT_VEC4_EQ(v_4 - f, g_4 - f);
    EXPECT_VEC4_EQ(v_4 * f, g_4 * f);
    EXPECT_VEC4_EQ(f * v_4, f * g_4);
    EXPECT_VEC4_EQ(v_4 / f, g_4 / f);

    EXPECT_VEC4_EQ(-v_4, -g_4);

    EXPECT_FLOAT_EQ(v_4[0], g_4.x);
    EXPECT_FLOAT_EQ(v_4[3], g_4.w);

    EXPECT_TRUE(v_4 == Vector4D(1.0f, 2.0f, 3.0f, 4.0f));
}

TEST(Vector4DTest, Constants)
{
    EXPECT_VEC4_EQ(Vector4D::Zero, glm::vec4(0, 0, 0, 0));
    EXPECT_VEC4_EQ(Vector4D::One, glm::vec4(1, 1, 1, 1));
}