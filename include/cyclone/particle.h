#ifndef CYCLONE_PARTICLE_H
#define CYCLONE_PARTICLE_H

#include "core.h"

namespace cyclone
{
    class Particle
    {
    protected:
        /** Linear position of particle in world space. */
        Vector3 position;

        /** Linear velocity of particle in world space. */
        Vector3 velocity;

        /** Acceleration of particle. */
        Vector3 acceleration;

        /** Amount of damping applied to linear motion.
         * It is required to remove energy added through numerical instability in the integrator.
         */
        real damping;

        /** Inverse of mass of the particle.
         * Integration is simpler with inverse mass.
         * It is also useful for immovable objects.
         */
        real inverseMass;

        /**
         * Holds the accumulated force to be aplpied at the next simulation iteration.
         * It is zeroed at each integration step.
         */
        Vector3 forceAccum;

    public:
        /** Integrates particle forward in time.
         * This function uses newton-euler integration method.
         */
        void integrate(real duration);

        Vector3 getPosition() const;

        void getPosition(Vector3 *position);

        void setPosition(const Vector3 &position);

        void setPosition(const real x, const real y, const real z);

        Vector3 getVelocity() const;

        void getVelocity(Vector3 *velocity);

        void setVelocity(const Vector3 &velocity);

        void setVelocity(const real x, const real y, const real z);

        Vector3 getAcceleration() const;

        void setAcceleration(const Vector3 &acceleration);

        void setAcceleration(const real x, const real y, const real z);

        real getMass() const;

        void setMass(const real mass);

        real getInverseMass() const;

        void setInverseMass(const real inverseMass);

        real getDamping() const; 

        void setDamping(const real damping);

        /**
         * Returns true if mass of the particle is finite.
         */
        bool hasFiniteMass() const;

        /**
         * Clears the forces applied to the particle.
         */
        void clearAccumulator();
        
        /**
         * Adds the given force to the particle to be applied at the next iteration.
         */
        void addForce(const Vector3 &force);
    };
}

#endif