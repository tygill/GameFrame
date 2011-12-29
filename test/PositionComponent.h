#pragma once
#ifndef id0ECA160D_E728_4016_838809F212429646
#define id0ECA160D_E728_4016_838809F212429646

#include <gf/EntityComponent.h>

class PositionComponent : public gf::EntityComponent {
public:
    PositionComponent();

    GF_DECLARE_COMPONENT;
    
    double x() const;
    void setX(double newX);
    double y() const;
    void setY(double newY);
    
private:
    double xPos;
    double yPos;
    
};

#endif // header
