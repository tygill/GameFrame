#include "PositionComponent.h"

PositionComponent::PositionComponent() :
    xPos(0.0d),
    yPos(0.0d)
{
}

double PositionComponent::x() const {
    return xPos;
}

void PositionComponent::setX(double newX) {
    xPos = newX;
}

double PositionComponent::y() const {
    return yPos;
}

void PositionComponent::setY(double newY) {
    yPos = newY;
}