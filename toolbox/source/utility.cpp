#include "../include/utility.h"
#include <iostream>

bool Core::Maths::IsEqualZero(float num)
{
    return std::fabs(num) < tolerance;
}

bool Core::Maths::IsEqual(float a, float b)
{
    return std::fabs(a - b) < tolerance;
}