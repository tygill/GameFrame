#pragma once
#ifndef id7C1B513E_1F02_4740_B9C28266A08A15EF
#define id7C1B513E_1F02_4740_B9C28266A08A15EF

#include "gf/Global.h"

// Some helper macros to hide the implementation of declaring and
// registering message types in message classes

// This should go in the body of the declaration of the new message class
#define GF_DECLARE_MESSAGE \
    public:\
        gf::MessageType type() const;\
        static gf::MessageType staticType();\
    private:\
        static gf::MessageType staticMessageType;\
    public:
// This should be placed in the .cpp file for the message class, and will
// do the static registration of the type without RTTI
#define GF_REGISTER_MESSAGE(messageClass) \
    gf::MessageType messageClass::type() const {\
        return staticMessageType;\
    }\
    gf::MessageType messageClass::staticType() {\
        return staticMessageType;\
    }\
    gf::MessageType messageClass::staticMessageType = gf::Message::registerType();

namespace gf {
    
    class Message {
    public:
        Message();
        virtual ~Message();

        // This will reimplment the virtual functions for type identifiation,
        // and add the public static type 
        // GF_DECLARE_MESSAGE;
        
        // If this implmentation is every called, a MethodNotDefinedException will be thrown.
        // The GF_*_MESSAGE macros should define this function virtually.
        virtual MessageType type() const;

    public:
        // Static type registration
        static MessageType registerType();

    private:
        static MessageType nextRegistrationType;
        
    };
    
}

#endif // header
