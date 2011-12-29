#include "VelocityComponent.h"

GF_REGISTER_COMPONENT(VelocityComponent);

VelocityComponent::VelocityComponent() :
    speed(0.0),
    angle(0.0)
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
