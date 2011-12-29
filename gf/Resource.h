#pragma once
#ifndef id50D8F1FA_1EA6_4573_9BEF3B720902FB13
#define id50D8F1FA_1EA6_4573_9BEF3B720902FB13

#include "gf/Global.h"

// Some helper macros to hide the implementation of declaring and
// registering resource types in resource classes

// This should go in the body of the declaration of the new resource class
#define GF_DECLARE_RESOURCE \
    public:\
        gf::ResourceType type() const;\
        static gf::ResourceType staticType();\
    private:\
        static gf::ResourceType staticResourceType;\
    public:
// This should be placed in the .cpp file for the resource class, and will
// do the static registration of the type without RTTI
#define GF_REGISTER_RESOURCE(resourceClass) \
    gf::ResourceType resourceClass::type() const {\
        return staticResourceType;\
    }\
    gf::ResourceType resourceClass::staticType() {\
        return staticResourceType;\
    }\
    gf::ResourceType resourceClass::staticResourceType = gf::Resource::registerType();

namespace gf {
    
    class Resource {
    public:
        Resource();
        virtual ~Resource();
        
        // This will reimplment the virtual functions for type identifiation,
        // and add the public static type 
        // GF_DECLARE_RESOURCE;
        
        // If this implmentation is every called, a MethodNotDefinedException will be thrown.
        // The GF_*_RESOURCE macros should define this function virtually.
        virtual ResourceType type() const;

    public:
        // Static type registration
        static ResourceType registerType();

    private:
        static ResourceType nextRegistrationType;
        
    };
    
}

#endif // header
