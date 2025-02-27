/*
This file is a part of: Lina Engine
https://github.com/inanevin/LinaEngine

Author: Inan Evin
http://www.inanevin.com

Copyright (c) [2018-2020] [Inan Evin]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#define NOMINMAX

#include "Math/Vector.hpp"

#include "Math/Quaternion.hpp"
#include "glm/gtx/projection.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/transform.hpp"

namespace Lina
{

    Vector4   Vector4::Zero    = Vector4(0.0f);
    Vector4   Vector4::One     = Vector4(1.0f);
    Vector3   Vector3::Zero    = Vector3(0.0f);
    Vector3   Vector3::One     = Vector3(1.0f);
    Vector3   Vector3::Forward = Vector3(0.0f, 0.0f, 1.0f);
    Vector3   Vector3::Up      = Vector3(0.0f, 1.0f, 0.0f);
    Vector3   Vector3::Right   = Vector3(1.0f, 0.0f, 0.0f);
    Vector3   Vector3::Back    = Vector3(0.0f, 0.0f, -1.0f);
    Vector3   Vector3::Down    = Vector3(0.0f, -1.0f, 0.0f);
    Vector3   Vector3::Left    = Vector3(-1.0f, 0.0f, 0.0f);
    Vector2   Vector2::Zero    = Vector2(0.0f);
    Vector2   Vector2::One     = Vector2(1.0f);
    Vector2ui Vector2ui::Zero  = Vector2ui(0);
    Vector2ui Vector2ui::One   = Vector2ui(1);
    Vector2i  Vector2i::Zero   = Vector2i(0);
    Vector2i  Vector2i::One    = Vector2i(1);

    Vector4 Vector4::Abs() const
    {
        return Vector4(glm::abs(x), glm::abs(y), glm::abs(z), glm::abs(w));
    }

    Vector4 Vector4::Min(const Vector4& other) const
    {
        return length() < other.length() ? glm::vec4(*this) : other;
    }

    Vector4 Vector4::Max(const Vector4& other) const
    {
        return length() > other.length() ? glm::vec4(*this) : other;
    }

    Vector4 Vector4::Normalized() const
    {
        glm::vec4 norm = glm::normalize(glm::vec4(*this));
        return norm;
    }

    Vector4 Vector4::Project(const Vector4& normal) const
    {
        return glm::proj(glm::vec4(*this), glm::vec4(normal));
    }

    Vector4 Vector4::Rotate(const Quaternion& rotation) const
    {
        return glm::rotate(glm::quat(rotation), glm::vec4(*this));
    }

    Vector4 Vector4::Rotate(const Vector3& axis, float angle) const
    {
        return glm::rotate(glm::vec4(*this), angle, glm::vec3(axis));
    }

    Vector4 Vector4::Reflect(const Vector4& normal) const
    {
        return glm::reflect(glm::vec4(*this), glm::vec4(normal));
    }

    Vector4 Vector4::Refract(const Vector4& normal, float indexOfRefraction) const
    {
        return glm::refract(glm::vec4(*this), glm::vec4(normal), indexOfRefraction);
    }

    float Vector4::Dot(const Vector4& other) const
    {
        return glm::dot<4, float, glm::qualifier::highp>(glm::vec4(*this), glm::vec4(other));
    }

    float Vector4::Distance(const Vector4& other) const
    {
        return glm::distance(glm::vec4(*this), glm::vec4(other));
    }

    float Vector4::Magnitude() const
    {
        return glm::length(glm::vec4(*this));
    }

    float Vector4::MagnitudeSqrt() const
    {
        return glm::length2(glm::vec4(*this));
    }

    float Vector4::Max() const
    {
        return glm::max(x, glm::max(y, glm::max(z, w)));
    }

    float Vector4::Min() const
    {
        return glm::min(x, glm::min(y, glm::min(z, w)));
    }

    float Vector4::Avg() const
    {
        return (x + y + z + w) / 4.0f;
    }

    void Vector4::Normalize()
    {
        *this = glm::normalize(*this);
    }

    //////////////////////////////////////////////////////////////////////////

    Vector3 Vector3::Lerp(const Vector3& from, const Vector3& to, float t)
    {
        return Vector3(from.x + (to.x - from.x) * t, from.y + (to.y - from.y) * t, from.z + (to.z - from.z) * t);
    }

    Vector3 Vector3::Cross(const Vector3& other) const
    {
        return glm::cross(glm::vec3(*this), glm::vec3(other));
    }

    Vector3 Vector3::Abs() const
    {
        return glm::vec3(glm::abs(x), glm::abs(y), glm::abs(z));
    }

    Vector3 Vector3::Min(const Vector3& other) const
    {
        return length() < other.length() ? glm::vec3(*this) : glm::vec3(other);
    }

    Vector3 Vector3::Max(const Vector3& other) const
    {
        return length() > other.length() ? glm::vec3(*this) : glm::vec3(other);
    }

    Vector3 Vector3::Normalized() const
    {
        glm::vec3 norm = glm::normalize(*this);
        return norm;
    }

    Vector3 Vector3::Project(const Vector3& normal) const
    {
        return glm::proj(glm::vec3(*this), glm::vec3(normal));
    }

    Vector3 Vector3::Rotate(const Vector3& axis, float angle) const
    {
        return glm::rotate(glm::vec3(*this), angle, glm::vec3(axis));
    }

    Vector3 Vector3::Rotate(const Quaternion& rotation) const
    {
        return glm::rotate(glm::quat(rotation), glm::vec3(*this));
    }

    Vector3 Vector3::Reflect(const Vector3& normal) const
    {
        return glm::reflect(glm::vec3(*this), glm::vec3(normal));
    }

    Vector3 Vector3::Refract(const Vector3& normal, float indexOfRefraction) const
    {
        return glm::refract(glm::vec3(*this), glm::vec3(normal), indexOfRefraction);
    }

    float Vector3::Dot(const Vector3& other) const
    {
        return glm::dot<3, float, glm::qualifier::highp>(glm::vec3(*this), glm::vec3(other));
    }

    float Vector3::Distance(const Vector3& other) const
    {
        return glm::distance(glm::vec3(*this), glm::vec3(other));
    }

    float Vector3::Magnitude() const
    {
        glm::vec3 vec = *this;
        float     len = glm::length(vec);
        return len;
    }

    float Vector3::MagnitudeSqrt() const
    {
        return glm::length(glm::vec3(*this));
    }

    float Vector3::Max() const
    {
        return glm::max(x, glm::max(y, z));
    }

    float Vector3::Min() const
    {
        return glm::min(x, glm::min(y, z));
    }

    float Vector3::Avg() const
    {
        return (x + y + z) / 3.0f;
    }

    void Vector3::Normalize()
    {
        *this = glm::normalize(*this);
    }

    //////////////////////////////////////////////

    Vector2 Vector2::Abs() const
    {
        return Vector2(glm::abs(x), glm::abs(y));
    }

    Vector2 Vector2::Min(const Vector2& other) const
    {
        return length() < other.length() ? glm::vec2(*this) : glm::vec2(other);
    }

    Vector2 Vector2::Max(const Vector2& other) const
    {
        return length() > other.length() ? glm::vec2(*this) : glm::vec2(other);
    }

    Vector2 Vector2::Normalized() const
    {
        glm::vec2 norm = glm::normalize(glm::vec2(*this));
        return norm;
    }

    Vector2 Vector2::Project(const Vector2& normal) const
    {
        return glm::proj(glm::vec2(*this), glm::vec2(normal));
    }

    Vector2 Vector2::Rotate(const Vector2& axis, float angle) const
    {
        return glm::rotate(glm::vec2(axis), angle);
    }

    Vector2 Vector2::Reflect(const Vector2& normal) const
    {
        return glm::reflect(glm::vec2(*this), glm::vec2(normal));
    }

    Vector2 Vector2::Refract(const Vector2& normal, float indexOfRefraction) const
    {
        return glm::refract(glm::vec2(*this), glm::vec2(normal), indexOfRefraction);
    }

    float Vector2::Dot(const Vector2& other) const
    {
        return glm::dot<2, float, glm::qualifier::highp>(glm::vec2(*this), glm::vec2(other));
    }

    float Vector2::Distance(const Vector2& other) const
    {
        return glm::distance(glm::vec2(*this), glm::vec2(other));
    }

    float Vector2::Magnitude() const
    {
        return glm::length(glm::vec2(*this));
    }

    float Vector2::MagnitudeSqrt() const
    {
        return glm::length2(glm::vec2(*this));
    }

    float Vector2::Max() const
    {
        return glm::max(x, y);
    }

    float Vector2::Min() const
    {
        return glm::min(x, y);
    }

    float Vector2::Avg() const
    {
        return (x + y) / 2.0f;
    }

    void Vector2::Normalize()
    {
        *this = glm::normalize(glm::vec2(*this));
    }

} // namespace Lina
