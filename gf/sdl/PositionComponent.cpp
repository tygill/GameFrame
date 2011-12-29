#include "gf/sdl/PositionComponent.h"

namespace gf {

    namespace sdl {

        GF_REGISTER_COMPONENT(PositionComponent);

        PositionComponent::PositionComponent() :
            xPos(0),
            yPos(0)
        {
        }

        PositionComponent::~PositionComponent() {
        }

        double PositionComponent::x() const {
            return xPos;
        }

        void PositionComponent::setX(double newX) {
            xPos = newX;
        }

        void PositionComponent::moveX(double deltaX) {
            xPos += deltaX;
        }

        double PositionComponent::y() const {
            return yPos;
        }

        void PositionComponent::setY(double newY) {
            yPos = newY;
        }

        void PositionComponent::moveY(double deltaY) {
            yPos += deltaY;
        }

    }

}
