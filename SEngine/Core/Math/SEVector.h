#pragma once

#include <iostream>
#include <limits>
#include <cmath>
#include <algorithm>

#include "Platform/Assert.h"
#include "SEMathCommon.h"

namespace SingularEngine
{
    template<typename T, size_t SizeOfArray>
    constexpr size_t ElementCount(T(&)[SizeOfArray]) { return SizeOfArray; }

    template<typename T>
    struct Vector2Type
    {
        union {
            T data[2];
            struct { T x, y; };
            struct { T u, v; };
            struct { T r, g; };
        };

        Vector2Type<T>() {};
        Vector2Type<T>(const T& _v) : x(_v), y(_v) {};
        Vector2Type<T>(const T& _x, const T& _y) : x(_x), y(_y) {};

        T& operator[](int rowIndex)
        {
            SINGULAR_ASSERT(rowIndex < 2);
            return data[rowIndex];
        }

        bool operator==(const Vector2Type<T>& rhs) const {

            auto c1 = comparison_traits<T>::equal(x, rhs.x);
            auto c2 = comparison_traits<T>::equal(y, rhs.y);
            return c1 && c2;
        }

        bool operator!=(const Vector2Type<T>& rhs) const {
            auto ret = *this == rhs;
            return !ret;
        }

        Vector2Type<T> operator+(const Vector2Type<T>& rhs) const {

            Vector2Type<T> ret;
            ret.x = x + rhs.x;
            ret.y = y + rhs.y;
            return ret;
        }

        Vector2Type<T> operator-(const Vector2Type<T>& rhs) const {

            Vector2Type<T> ret;
            ret.x = x - rhs.x;
            ret.y = y - rhs.y;
            return ret;
        }

        Vector2Type<T> operator*(T scale)  const
        {
            Vector2Type<T> ret;
            ret.x = x * scale;
            ret.y = y * scale;
            return ret;
        }

        T Length() const {

            return sqrt(x * x + y * y);
        }

        void Normalize() {
            float lengthScale = 1.0 / max(Length(), 1e-6);

            for (size_t i = 0; i < 2; ++i) {
                data[i] = data[i] * lengthScale;
            }
        }

        Vector2Type<float> Normalize() const {
            Vector2Type<float> ret;
            float lengthScale = 1.0 / max(Length(), 1e-6);
            for (size_t i = 0; i < 2; ++i)
            {
                ret.data[i] = data[i] * lengthScale;
            }
            return ret;
        }

        T Dot(const Vector2Type<T>& lhs) const {

            T ret = 0;
            for (size_t i = 0; i < 2; ++i) {
                ret += data[i] * lhs.data[i];
            }
            return ret;
        }
    };


    template<typename T>
    struct Vector3Type
    {
        union {
            T data[3];
            struct { T x, y, z; };
            struct { T r, g, b; };
        };

        Vector3Type<T>() {};
        Vector3Type<T>(const T& _v) : x(_v), y(_v), z(_v) {};
        Vector3Type<T>(const T& _x, const T& _y, const T& _z) : x(_x), y(_y), z(_z) {};

        T& operator[](int rowIndex)
        {
            SINGULAR_ASSERT(rowIndex < 3);
            return data[rowIndex];
        }

        bool operator==(const Vector3Type<T>& rhs) const {

            auto c1 = comparison_traits<T>::equal(x, rhs.x);
            auto c2 = comparison_traits<T>::equal(y, rhs.y);
            auto c3 = comparison_traits<T>::equal(z, rhs.z);
            return c1 && c2 && c3;
        }

        bool operator!=(const Vector3Type<T>& rhs) const {

            auto ret = *this == rhs;
            return !ret;
        }

        Vector3Type<T> operator+(const Vector3Type<T>& rhs) const {

            Vector3Type<T> ret;
            ret.x = x + rhs.x;
            ret.y = y + rhs.y;
            ret.z = z + rhs.z;
            return ret;
        }

        Vector3Type<T> operator-(const Vector3Type<T>& rhs) const {

            Vector3Type<T> ret;
            ret.x = x - rhs.x;
            ret.y = y - rhs.y;
            ret.z = z - rhs.z;
            return ret;
        }

        Vector3Type<T> operator*(T scale)  const {

            Vector3Type<T> ret;
            ret.x = x * scale;
            ret.y = y * scale;
            ret.z = z * scale;
            return ret;
        }

        Vector3Type<T> operator*(const Vector3Type<T>& rhs) const {

            Vector3Type<T> ret;
            ret.x = x * rhs.x;
            ret.y = y * rhs.y;
            ret.z = z * rhs.z;
            return ret;
        }

        T Length() const {

            return sqrt(x * x + y * y + z * z);
        }

        void Normalize() {

            float lengthScale = 1.0 / max(Length(), 1e-6);

            for (size_t i = 0; i < 3; ++i) {
                data[i] = data[i] * lengthScale;
            }
        }

        Vector3Type<float> Normalize() const {

            Vector3Type<float> ret;
            float lengthScale = 1.0 / max(Length(), 1e-6);

            for (size_t i = 0; i < 3; ++i) {
                ret.data[i] = data[i] * lengthScale;
            }

            return ret;
        }

        T Dot(const Vector3Type<T>& lhs) const {

            T ret = 0;
            for (size_t i = 0; i < 3; ++i) {
                ret += data[i] * lhs.data[i];
            }

            return ret;
        }

        Vector3Type<T> Cross(const Vector3Type<T>& lhs) const {

            Vector3Type<T> ret;
            ret[0] = data[1] * lhs.data[2] - data[2] * lhs.data[1];
            ret[1] = data[2] * lhs.data[0] - data[0] * lhs.data[2];
            ret[2] = data[0] * lhs.data[1] - data[1] * lhs.data[0];
            return ret;
        }
    };

    template<typename T>
    struct Vector4Type
    {
        union {
            T data[3];
            struct { T x, y, z, w; };
            struct { T r, g, b, a; };
        };

        Vector4Type<T>() {};
        Vector4Type<T>(const T& _v) : x(_v), y(_v), z(_v), w(_v) {};
        Vector4Type<T>(const T& _x, const T& _y, const T& _z, const T& _w) : x(_x), y(_y), z(_z), w(_w) {};
        Vector4Type<T>(const Vector3Type<T>& v3) : x(v3.x), y(v3.y), z(v3.z), w(1.0f) {};
        Vector4Type<T>(const Vector3Type<T>& v3, const T& _w) : x(v3.x), y(v3.y), z(v3.z), w(_w) {};

        T& operator[](int rowIndex)
        {
            SINGULAR_ASSERT(rowIndex < 4);
            return data[rowIndex];
        }

        bool operator==(const Vector4Type<T>& rhs) const {

            auto c1 = comparison_traits<T>::equal(x, rhs.x);
            auto c2 = comparison_traits<T>::equal(y, rhs.y);
            auto c3 = comparison_traits<T>::equal(z, rhs.z);
            auto c4 = comparison_traits<T>::equal(w, rhs.w);
            return c1 && c2 && c3 && c4;
        }

        bool operator!=(const Vector4Type<T>& rhs) const {

            auto ret = *this == rhs;
            return !ret;
        }

        Vector4Type<T> operator+(const Vector4Type<T>& rhs) const {

            Vector4Type<T> ret;
            ret.x = x + rhs.x;
            ret.y = y + rhs.y;
            ret.z = z + rhs.z;
            ret.w = w + rhs.w;
            return ret;
        }

        Vector4Type<T> operator-(const Vector4Type<T>& rhs) const {

            Vector4Type<T> ret;
            ret.x = x - rhs.x;
            ret.y = y - rhs.y;
            ret.z = z - rhs.z;
            ret.w = w - rhs.w;
            return ret;
        }

        Vector4Type<T> operator*(T scale)  const {

            Vector4Type<T> ret;
            ret.x = x * scale;
            ret.y = y * scale;
            ret.z = z * scale;
            ret.w = w * scale;
            return ret;
        }

        Vector4Type<T> operator*(const Vector4Type<T>& rhs)  const {

            Vector4Type<T> ret;

            ret.x = x * rhs.x;
            ret.y = y * rhs.y;
            ret.z = z * rhs.z;
            ret.w = w * rhs.w;
            return ret;
        }

        T Length() const {

            return sqrt(x * x + y * y + z * z + w * w);
        }

        void Normalize() {

            float lengthScale = 1.0 / max(Length(), 1e-6);

            for (size_t i = 0; i < 4; ++i) {
                data[i] = data[i] * lengthScale;
            }
        }

        Vector4Type<float> Normalize() const {

            Vector4Type<float> ret;
            float lengthScale = 1.0 / max(Length(), 1e-6);

            for (size_t i = 0; i < 4; ++i) {
                ret.data[i] = data[i] * lengthScale;
            }

            return ret;
        }

        T Dot(const Vector4Type<T>& lhs) const {

            T ret = 0;
            for (size_t i = 0; i < 4; ++i) {
                ret += data[i] * lhs.data[i];
            }

            return ret;
        }
    };

    typedef Vector2Type<float> Vector2f;

    typedef Vector3Type<float> Vector3f;
    typedef Vector3Type<int> Vector3i;

    typedef Vector4Type<float> Vector4f;
    typedef Vector4Type<int> Vector4i;
    typedef Vector4Type<float> Color;
    typedef Vector4Type<uint8_t> R8G8B8A8Unorm;
}