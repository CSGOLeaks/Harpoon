#pragma once

#include <cmath>
#define M_PI 3.14

class matrix3x4;
#include <numbers>
#include "Utils.h"
struct Vector {
    constexpr auto notNull() const noexcept
    {
        return x || y || z;
    }
    
    constexpr auto operator==(const Vector& v) const noexcept
    {
        return x == v.x && y == v.y && z == v.z;
    }

    constexpr auto operator!=(const Vector& v) const noexcept
    {
        return !(*this == v);
    }

    constexpr Vector& operator=(const float array[3]) noexcept
    {
        x = array[0];
        y = array[1];
        z = array[2];
        return *this;
    }

    constexpr Vector& operator+=(const Vector& v) noexcept
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    constexpr Vector& operator+=(float f) noexcept
    {
        x += f;
        y += f;
        z += f;
        return *this;
    }

    constexpr Vector& operator*=(float f) noexcept
    {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    constexpr Vector& operator-=(const Vector& v) noexcept
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    constexpr Vector& operator-=(float f) noexcept
    {
        x -= f;
        y -= f;
        z -= f;
        return *this;
    }

    constexpr auto operator-(const Vector& v) const noexcept
    {
        return Vector{ x - v.x, y - v.y, z - v.z };
    }

    constexpr auto operator-() const noexcept
    {
        return Vector{ -x , -y, -z};
    }

    constexpr auto operator+(const Vector& v) const noexcept
    {
        return Vector{ x + v.x, y + v.y, z + v.z };
    }
    
    constexpr auto operator*(const Vector& v) const noexcept
    {
        return Vector{ x * v.x, y * v.y, z * v.z };
    }


    constexpr Vector& operator/=(float div) noexcept
    {
        x /= div;
        y /= div;
        z /= div;
        return *this;
    }

    constexpr auto operator/(float div) const noexcept
    {
        return Vector{ x / div, y ,z };
    }

    constexpr auto operator*(float mul) const noexcept
    {
        return Vector{ x * mul, y * mul, z * mul };
    }

    constexpr auto operator-(float sub) const noexcept
    {
        return Vector{ x - sub, y - sub, z - sub };
    }

    constexpr auto operator+(float add) const noexcept
    {
        return Vector{ x + add, y + add, z + add };
    }

    constexpr void normalize() noexcept
    {
        x = std::isfinite(x) ? std::remainder(x, 360.0f) : 0.0f;
        y = std::isfinite(y) ? std::remainder(y, 360.0f) : 0.0f;
        z = 0.0f;
    }

    auto NormalizeInPlace() noexcept
    {
        float radius = std::sqrt(x * x + y * y + z * z);
        float iradius = 1.f / (radius + 1.192092896e-07F /* FLT_EPSILON */);

        x *= iradius;
        y *= iradius;
        z *= iradius;

        return radius;
    }

    Vector CrossProduct(const Vector& a, const Vector& b)noexcept
    {
        return Vector{ a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
    }

    constexpr void CrossProduct(const Vector a)noexcept
    {
        y = a.y* z - a.z * y;
        x = a.z * x - a.x * z;
        z = a.x * y - a.y * x;
        return;
    }

    Vector toAngle()
    {
        Vector Ang;
        float	tmp, yaw, pitch;

        if (y == 0 && x == 0)
        {
            yaw = 0;
            if (z > 0)
                pitch = 270;
            else
                pitch = 90;
        }
        else
        {
            yaw = (atan2(y, x) * 180 / M_PI);
            if (yaw < 0)
                yaw += 360;

            tmp = sqrt(x * x + y * y);
            pitch = (atan2(-z, tmp) * 180 / M_PI);
            if (pitch < 0)
                pitch += 360;
        }

        Ang.x = pitch;
        Ang.y = yaw;
        Ang.z = 0;

        return Ang;
    }

    static auto fromAngle(const Vector& angle) noexcept
    {
        return Vector{ std::cos(degreesToRadians(angle.x)) * std::cos(degreesToRadians(angle.y)),
                       std::cos(degreesToRadians(angle.x)) * std::sin(degreesToRadians(angle.y)),
                      -std::sin(degreesToRadians(angle.x)) };
    }

    void VectorVectors(const Vector& forward, Vector& right, Vector& up)
    {
        Vector tmp;

        if (forward.x == 0 && forward.y == 0)
        {
            // pitch 90 degrees up/down from identity
            right.x = 0;
            right.y = -1;
            right.z = 0;
            up.x = -forward.y;
            up.y = 0;
            up.z = 0;
        }
        else
        {
            tmp.x = 0; tmp.y = 0; tmp.z = 1.0;
            right = CrossProduct(forward, tmp);
            right.normalize();
            up = CrossProduct(right, forward);
            up.normalize();
        }
    }


    //auto toMatrix();

    auto length() const noexcept
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    auto length2D() const noexcept
    {
        return std::sqrt(x * x + y * y);
    }

    constexpr auto squareLength() const noexcept
    {
        return x * x + y * y + z * z;
    }

    constexpr auto dotProduct(const Vector& v) const noexcept
    {
        return x * v.x + y * v.y + z * v.z;
    }

    constexpr auto dotProduct(const float* v) const noexcept
    {
        return x * v[0] + y * v[1] + z * v[2];
    }
    constexpr auto transform(const matrix3x4& mat) const noexcept;

    auto distTo(const Vector& v) const noexcept
    {
        return (*this - v).length();
    }

    auto rotate(float degrees, int Axis) {





        return *this;
    }













    float x, y, z;
};

#include "Matrix3x4.h"
constexpr auto Vector::transform(const matrix3x4& mat) const noexcept
{
    return Vector{ dotProduct({ mat[0][0], mat[0][1], mat[0][2] }) + mat[0][3],
                   dotProduct({ mat[1][0], mat[1][1], mat[1][2] }) + mat[1][3],
                   dotProduct({ mat[2][0], mat[2][1], mat[2][2] }) + mat[2][3] };
}


struct VectorAndDamage
{
    Vector vec;
    float damage;
};


/*
constexpr auto Vector::transform(float in2[3][4], Vector& out) const noexcept
{
    out[0] = dotProduct( {in2[0][0], in2[0][1], in2[0][2]}) + in2[0][3];
    out[1] = dotProduct( {in2[1][0], in2[1][1], in2[1][2]}) + in2[1][3];
    out[2] = dotProduct( {in2[2][0], in2[2][1], in2[2][2]}) + in2[2][3];
}
*/

