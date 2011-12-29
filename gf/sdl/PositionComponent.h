#pragma once
#ifndef idED7D4EDE_D3C0_40CA_973B1972546212C0
#define idED7D4EDE_D3C0_40CA_973B1972546212C0

#include "gf/EntityComponent.h"

namespace gf {

    namespace sdl {
        
        class PositionComponent : public gf::EntityComponent {
        public:
            PositionComponent();
            ~PositionComponent();

            GF_DECLARE_COMPONENT;
            
            double x() const;
            void setX(double newX);
            void moveX(double deltaX);
            double y() const;
            void setY(double newY);
            void moveY(double deltaY);
            
        private:
            double xPos;
            double yPos;
            
        };

    }

}

#endif // header
