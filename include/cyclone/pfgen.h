#ifndef CYCLONE_PFGEN_H
#define CYCLONE_PFGEN_H

#include "particle.h"
#include <vector>

namespace cyclone
{
    class ParticleForceGenerator
    {
    public:
        /**
         * Update the force applied to the given particle.
         */
        virtual void updateForce(Particle *particle, real duration) = 0;
    };

    class ParticleForceRegistry
    {
    protected:
        /**
         * Keeps track of one force gennerator and the particle it applies to.
         */
        struct ParticleForceRegistration
        {
            Particle *particle;
            ParticleForceGenerator *fg;
        };

        /**
         * Holds list of registrations.
         */
        typedef std::vector<ParticleForceRegistration> Registry;
        Registry registrations;

    public:
        /**
         * Registers the given force generator to apply to the given particle.
         */
        void add(Particle *particle, ParticleForceGenerator *fg);

        void remove(Particle *particle, ParticleForceGenerator *fg);

        /**
         * Clear all registrations from the registry.
         */
        void clear();

        /**
         * Calls all the force generators to update the foces of their corresponding particles.
         */
        void updateForces(real duration);
    };

    class ParticleGravity : public ParticleForceGenerator
    {
        /**
         * Acceleration due to gravity;
         */
        Vector3 gravity;

    public:
        ParticleGravity(const Vector3 &gravity);
        virtual void updateForce(Particle *particle, real duration);
    };

    class ParticleDrag : public ParticleForceGenerator
    {
        /** velocity drag coefficient. */
        real k1;
        /** velocity squared drag coefficient. */
        real k2;
    public:
        ParticleDrag(real k1, real k2);
        virtual void updateForce(Particle *particle, real duration);
    };
}

#endif;