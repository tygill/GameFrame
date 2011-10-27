#include "VelocityComponent.h"

VelocityComponent::VelocityComponent() :
    speed(0.0d),
    angle(0.0d)
{
}

double VelocityComponent::velocity() const {
    return speed;
}

void VelocityComponent::setVelocity(double vel) {
    speed = vel;
}

double VelocityComponent::direction() const {
    return angle;
}

void VelocityComponent::setDirection(double dir) {
    angle = dir;
}
