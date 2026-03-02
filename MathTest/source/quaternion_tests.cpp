#include "../include/equal_utils.h"

Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
Quaternion q2(0.5f, -1.0f, 2.0f, -0.5f);

glm::quat g_q(q.w, q.x, q.y, q.z);
glm::quat g_q2(q2.w, q2.x, q2.y, q2.z);

TEST(QuaternionTest, Magnitude)
{
    EXPECT_FLOAT_EQ(q.Magnitude(), glm::length(g_q));
}

TEST(QuaternionTest, Normalization)
{
    Quaternion normQ = q.Normalized();
    Quaternion temp = q;
    temp.Normalize();

    glm::quat normG = glm::normalize(g_q);

    EXPECT_FLOAT_EQ(normQ.Magnitude(), glm::length(normG));
    EXPECT_FLOAT_EQ(temp.Magnitude(), glm::length(normG));
    EXPECT_QUAT_EQ(normQ, normG);
    EXPECT_QUAT_EQ(temp, normG);
}

TEST(QuaternionTest, DotProduct)
{
    EXPECT_FLOAT_EQ(q.Dot(q2), glm::dot(g_q, g_q2));
}

TEST(QuaternionTest, OppositeAndConjugate)
{
    EXPECT_QUAT_EQ(q.Opposite(), -g_q);
    EXPECT_QUAT_EQ(q.Conjugate(), glm::conjugate(g_q));
}

TEST(QuaternionTest, Inverse)
{
    Quaternion inv = q.Inverse();
    glm::quat expected = glm::inverse(g_q);
    EXPECT_QUAT_EQ(inv, expected);
}

TEST(QuaternionTest, AddMultiplyScalar)
{
    EXPECT_QUAT_EQ(q.Add(q2), g_q + g_q2);
    EXPECT_QUAT_EQ(q.Multiply(2.0f), g_q * 2.0f);
}

TEST(QuaternionTest, MultiplyQuaternion)
{
    Quaternion r = q.Multiply(q2);
    glm::quat rG = g_q * g_q2;
    EXPECT_QUAT_EQ(r, rG);
}

TEST(QuaternionTest, RotateVector)
{
    Vector3D v(1.0f, 0.0f, 0.0f);
    glm::vec3 g_v(v.x, v.y, v.z);

    Vector3D rotated = q.RotateVector(v);
    glm::vec3 rotatedG = glm::rotate(g_q, g_v);

    EXPECT_VEC3_EQ(rotated, rotatedG);
}

TEST(QuaternionTest, StaticConstructors)
{
    Vector3D axis(0.0f, 1.0f, 0.0f);
    float angleDeg = 90.0f;
    float angleRad = glm::radians(angleDeg);

    Quaternion qAxis = Quaternion::FromAxisAngle(axis, angleDeg);
    glm::quat gAxis = glm::angleAxis(angleRad, glm::vec3(axis.x, axis.y, axis.z));
    EXPECT_QUAT_EQ(qAxis, gAxis);

    Quaternion qRot = Quaternion::Qrotation(axis, angleDeg);
    EXPECT_QUAT_EQ(qRot, gAxis);

    Vector3D euler(90.0f, 0.0f, 0.0f);
    Quaternion qEuler = Quaternion::FromEuler(euler);
    glm::quat gEuler = glm::quat(glm::radians(glm::vec3(euler.x, euler.y, euler.z)));
    EXPECT_QUAT_EQ(qEuler, gEuler);
}

TEST(QuaternionTest, Interpolation)
{
    Quaternion slerpQ = Quaternion::Slerp(q, q2, 0.5f);
    Quaternion nlerpQ = Quaternion::Nlerp(q, q2, 0.5f);

    glm::quat slerpG = glm::slerp(g_q, g_q2, 0.5f);
    glm::quat nlerpG = glm::mix(g_q, g_q2, 0.5f);

    EXPECT_QUAT_EQ(slerpQ, slerpG);
    EXPECT_QUAT_EQ(nlerpQ, nlerpG);
}

TEST(QuaternionTest, Operators)
{
    EXPECT_QUAT_EQ(q + q2, g_q + g_q2);
    EXPECT_QUAT_EQ(q - q2, g_q - g_q2);
    EXPECT_QUAT_EQ(q * 2.0f, g_q * 2.0f);
}

TEST(QuaternionTest, Constants)
{
    EXPECT_QUAT_EQ(Quaternion::Identity, glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
}