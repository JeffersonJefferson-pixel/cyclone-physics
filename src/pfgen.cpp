#include <cyclone/pfgen.h>

using namespace cyclone;

void ParticleForceRegistry::updateForces(real duration)
{
    Registry::iterator i = registrations.begin();

    for (; i != registrations.end(); i++)
    {
        i->fg->updateForce(i->particle, duration);
    }
}

void ParticleForceRegistry::add(Particle *particle, ParticleForceGenerator *fg)
{
    ParticleForceRegistration registration = {particle, fg};

    registrations.push_back(registration);
}

void ParticleGravity::updateForce(Particle *particle, real duration)
{
    // check that particle has finite mass.
    if (!particle->hasFiniteMass()) return;

    // apply force to particle.
    particle->addForce(gravity * particle->getMass()); 
}

void ParticleDrag::updateForce(Particle *particle, real duration)
{
    Vector3 force;
    particle->getVelocity(&force);
    real speed = force.magnitude();

    real dragCoeff =  k1 * speed + k2 * speed * speed;

    force.normalize();
    force *= -dragCoeff;
    particle->addForce(force);

}