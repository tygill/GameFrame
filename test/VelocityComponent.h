#pragma once
#ifndef idD2C01928_FB57_49F4_8AD6A181D038E2F4
#define idD2C01928_FB57_49F4_8AD6A181D038E2F4

#include <gf/EntityComponent.h>

class VelocityComponent : public gf::EntityComponent {
public:
    VelocityComponent();
    
    double velocity() const;
    void setVelocity(double vel);
    // Direction is measured in radians! It will be mod'ed.
    double direction() const;
    void setDirection(double dir);
    
private:
    double speed;
    double angle;
    
};

#endif // header
