#include <math.h>

#ifndef CYCLONE_CORE_H
#define CYCLONE_CORE_H

#include "precision.h"

namespace cyclone
{
    /**
     * Holds a vector in three dimensions.
     */
    class Vector3
    {
    public:
        /** value along the x axis. */
        real x;
        /** value along the y axis. */
        real y;
        /** value along the z axis. */
        real z;

    private:
        /** Padding to ensure four word alignment. */
        real pad;

    public:
        Vector3() : x(0), y(0), z(0) {}

        Vector3(const real x, const real y, const real z)
            : x(x), y(y), z(z) {}

        /** Flips all the components of the vector. */
        void invert()
        {
            x = -x;
            y = -y;
            z = -z;
        }

        /** Get magnitude of the vector. */
        real magnitude() const
        {
            return real_sqrt(x * x + y * y + z * z);
        }

        /** Get the squred magnitude of the vector. */
        real sqaureMagnitude() const
        {
            return x * x + y * y + z * z;
        }

        /** Turns non-zero vector into a unit vector.  */
        void normalize()
        {
            real l = magnitude();
            if (l > 0)
            {
                (*this) *= ((real)1) / l;
            }
        }

        /** Multiplies vector by a scalar. */
        void operator*=(const real value)
        {
            x *= value;
            y *= value;
            z *= value;
        }

        /** Returns a copy of the vector scaled by the value. */
        Vector3 operator*(const real value) const
        {
            return Vector3(x * value, y * value, z * value);
        }

        /** Add the given vector to this vector. */
        void operator+=(const Vector3 &v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
        }

        Vector3 operator+(const Vector3 &v) const
        {
            return Vector3(x + v.x, y + v.y, z + v.z);
        }

        /** Substracts the given vector from this vector. */
        void operator-=(const Vector3 &v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }

        Vector3 operator-(const Vector3 &v) const
        {
            return Vector3(x - v.x, y - v.y, z - v.z);
        }

        void addScaledVector(const Vector3 &vector, real scale)
        {
            x += vector.x * scale;
            y += vector.y * scale;
            z += vector.z * scale;
        }

        /** Calculates and returns a component-wise product of this vector with the given vector. */
        Vector3 componentProduct(const Vector3 &vector) const
        {
            return Vector3(x * vector.x, y * vector.y, z * vector.z);
        }

        void ComponentProductUpdate(const Vector3 &vector)
        {
            x *= vector.x;
            y *= vector.y;
            z *= vector.z;
        }

        /** Calculates scalar product of this vector with the given vector. */
        real scalarProduct(const Vector3 &vector) const
        {
            return x * vector.x + y * vector.y + z * vector.z;
        }

        real operator*(const Vector3 &vector) const
        {
            return scalarProduct(vector);
        }

        /** calculates vector product of this vector with the given vector. */
        Vector3 vectorProduct(const Vector3 &vector) const
        {
            return Vector3(y * vector.z - z * vector.y, z * vector.x - x * vector.z, x * vector.y - y * vector.x);
        }

        void operator%=(const Vector3 &vector)
        {
            *this = vectorProduct(vector);
        }

        Vector3 operator%(const Vector3 &vector) const
        {
            return vectorProduct(vector);
        }

        void clear()
        {
            x = y = z = 0;
        }
    };
}

#endif