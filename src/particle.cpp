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

void Particle::getPosition(Vector3 *position)
{
    *position = Particle::position;
}

void Particle::setPosition(const Vector3 &position) 
{
    Particle::position = position;
}

void Particle::setPosition(const real x, const real y, const real z) 
{
    position.x = x;
    position.y = y; 
    position.z = z;
}

Vector3 Particle::getVelocity() const
{
    return velocity;
}

void Particle::getVelocity(Vector3 *velocity) 
{
    *velocity = Particle::velocity;
};

void Particle::setVelocity(const Vector3 &velocity)
{
    Particle::velocity = velocity;
}

void Particle::setVelocity(const real x, const real y, const real z) 
{
    velocity.x = x;
    velocity.y = y;
    velocity.z = z;
}

Vector3 Particle::getAcceleration() const 
{
    return acceleration;
}

void Particle::setAcceleration(const Vector3 &acceleration)
{
    Particle::acceleration = acceleration;
}

void Particle::setAcceleration(const real x, const real y, const real z)
{
    acceleration.x = x;
    acceleration.y = y;
    acceleration.z = z;
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

bool Particle::hasFiniteMass() const 
{
    return inverseMass > 0.0f;
}

void Particle::clearAccumulator()
{
    forceAccum.clear();
}

void Particle::addForce(const Vector3 &force) 
{
    forceAccum += force;
} 