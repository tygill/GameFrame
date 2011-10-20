#pragma once
#ifndef id7C1B513E_1F02_4740_B9C28266A08A15EF
#define id7C1B513E_1F02_4740_B9C28266A08A15EF

#include "gf/Global.h"

namespace gf {
    
    class Message {
    public:
        Message() {}
        virtual ~Message() {}
        
        MessageType type() const;
        //template<class T> static MessageType getType();
    };
    
}

#endif // header
