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

ParticleGravity::ParticleGravity(const Vector3& gravity) : gravity(gravity)
{

}

void ParticleGravity::updateForce(Particle *particle, real duration)
{
    // check that particle has finite mass.
    if (!particle->hasFiniteMass()) return;

    // apply force to particle.
    particle->addForce(gravity * particle->getMass()); 
}

ParticleDrag::ParticleDrag(real k1, real k2) : k1(k1), k2(k2)
{
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

ParticleSpring::ParticleSpring(Particle *other, real springConstant, real restLength) : other(other), springConstant(springConstant), restLength(restLength)
{
}

void ParticleSpring::updateForce(Particle* particle, real duration)
{
    // hook law: f = -k * deleta_l
    Vector3 force;
    particle->getPosition(&force);
    force -= other->getPosition();

    // force maginatude
    real magnitude = force.magnitude();
    magnitude = springConstant * (magnitude - restLength);

    force.normalize();
    force *= -magnitude;
    particle->addForce(force);

}

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3 *anchor, real springConstant, real restLength) : anchor(anchor), springConstant(sc), restlength(restLength)
{
}

void ParticleAnchoredSpring::updateForce(Particle *particle, real duration)
{
    Vector3 force;
    particle->getPosition(&force);
    force -= *anchor; 

    // force maginatude
    real magnitude = force.magnitude();
    magnitude = springConstant * (magnitude - restLength);

    force.normalize();
    force *= -magnitude;
    particle->addForce(force);
};

ParticleBungee::ParticleBungee(Particle *other, real springConstant, real restLength) : other(other), springConstant(springConstant), restLength(restLength)
{
}

void ParticleBungee::updateForce(Particle *particle, real duration)
{
    Vector3 force;
    particle->getPosition(&force);
    force -= other->getPosition(); 

    // force maginatude
    real magnitude = force.magnitude();
    // check if bungee is compressed
    if (magnitude <= restLength) return;

    magnitude = springConstant * (magnitude - restLength);

    force.normalize();
    force *= -magnitude;
    particle->addForce(force);
};

void ParticleAnchoredBungee::updateForce(Particle* particle, real duration)
{
    Vector3 force;
    particle->getPosition(&force);
    force -= *anchor;

    real magnitude = force.magnitude();
    if (magnitude < restLength) return;

    magnitude = springConstant * (magnitude - restLength);

    force.normalize();
    force *= - magnitude;
    particle->addForce(force);
}

ParticleBuoyancy::ParticleBuoyancy(real maxDepth, real volume, real waterHeight, real liquidDensity) : maxDepth(maxDepth), volume(volume), waterHeight(waterHeight), liquidDensity(liquidDensity)
{
}

void ParticleBuoyancy::updateForce(Particle* particle, real duration) 
{
    real depth = particle->getPosition().y;

    // out of water.
    if (depth >= waterHeight + maxDepth) return;

    Vector3 force;

    // at maximum depth.
    if (depth <= waterHeight - maxDepth) 
    {
        force.y = liquidDensity * volume;
        particle->addForce(force);
        return;
    }

    // partly submerged.
    force.y = liquidDensity * volume * (depth + maxDepth - waterHeight) / (2 * maxDepth);
    particle->addForce(force);
}


ParticleFakeSpring::ParticleFakeSpring(Vector3 *anchor, real springConstant, real damping) : anchor(anchor), springConstant(springConstant), damping(damping)
{
}

void ParticleFakeSpring::updateForce(Particle* particle, real duration) 
{
    if (!particle->hasFiniteMass()) return;

    // position relative to anchor.
    Vector3 position;
    particle->getPosition(&position);
    position -= *anchor;

    // calculate constant
    real gamma = 0.5f * real_sqrt(4 * springConstant - damping*damping);
    if (gamma == 0.0f) return;
    Vector3 c = position * (damping / (2.0f * gamma)) + particle->getVelocity() * (1.0 / gamma);

    // target position
    Vector3 target = position * real_cos(gamma * duration) + c * real_sin(gamma * duration);
    target *= real_exp(-0.5f * duration * damping);
    
    Vector3 accel = (target - position) * (1.0f / duration*duration) - particle->getVelocity() * duration;
    particle->addForce(accel * particle->getMass());
}