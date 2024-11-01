#include <assert.h>
#include <cyclone/particle.h>

using namespace cyclone;

void Particle::integrate(real duration)
{
    if (inverseMass <= 0.0f)
        return;

    assert(duration > 0.0);

    // update linear position from velocity.
    // ignore acceleration in position update.
    position.addScaledVector(velocity, duration);

    // calculate acceleratino from force.
    Vector3 resultingAcceleration = acceleration;
    // update linear velocity from acceleration.
    velocity.addScaledVector(resultingAcceleration, duration);

    // apply drag.
    velocity *= real_pow(damping, duration);

    // clear forces.
    clearAccumulator();
}

Vector3 Particle::getPosition() const 
{
    return position;
}

void Particle::setPosition(const Vector3 &position) 
{
    Particle::position = position;
}

Vector3 Particle::getVelocity() const
{
    return velocity;
}

void Particle::setVelocity(const Vector3 &velocity)
{
    Particle::velocity = velocity;
}

Vector3 Particle::getAcceleration() const 
{
    return acceleration;
}

void Particle::setAcceleration(const Vector3 &acceleration)
{
    Particle::acceleration = acceleration;
}

real Particle::getMass() const 
{
    if (inverseMass == 0) {
        return REAL_MAX;
    } else {
        return ((real) 1.0) / inverseMass;
    }
}

void Particle::setMass(const real mass) 
{
    assert(mass != 0);
    this->inverseMass = ((real) 1.0) / mass;
}

real Particle::getInverseMass() const 
{
    return inverseMass;
}

void Particle::setInverseMass(const real inverseMass) 
{
    Particle::inverseMass = inverseMass;
}

real Particle::getDamping() const 
{
    return damping;
}

void Particle::setDamping(const real damping)
{
    Particle::damping = damping;
}

void Particle::clearAccumulator()
{
    forceAccum.clear();
}