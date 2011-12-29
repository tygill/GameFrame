#pragma once
#ifndef id7533F2D8_5E80_4B45_902AF88DD7836049
#define id7533F2D8_5E80_4B45_902AF88DD7836049

#include "gf/Global.h"

// Some helper macros to hide the implementation of declaring and
// registering component types in component classes

// This should go in the body of the declaration of the new component class
#define GF_DECLARE_COMPONENT \
    public:\
        gf::ComponentType type() const;\
        static gf::ComponentType staticType();\
    private:\
        static gf::ComponentType staticComponentType;\
    public:
// This should be placed in the .cpp file for the component class, and will
// do the static registration of the type without RTTI
#define GF_REGISTER_COMPONENT(componentClass) \
    gf::ComponentType componentClass::type() const {\
        return staticComponentType;\
    }\
    gf::ComponentType componentClass::staticType() {\
        return staticComponentType;\
    }\
    gf::ComponentType componentClass::staticComponentType = gf::EntityComponent::registerType();

namespace gf {
    
    class EntityComponent {
    public:
        EntityComponent();
        virtual ~EntityComponent();
        
        // This will reimplment the virtual functions for type identifiation,
        // and add the public static type 
        // GF_DECLARE_COMPONENT;
        
        // If this implmentation is every called, a MethodNotDefinedException will be thrown.
        // The GF_*_COMPONENT macros should define this function virtually.
        virtual ComponentType type() const;

    public:
        // Static type registration
        static ComponentType registerType();

    private:
        static ComponentType nextRegistrationType;

    };
    
}

#endif // header
