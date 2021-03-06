#pragma once
#ifndef id912BBB00_AC05_4BA4_A4FF343D50597D8F
#define id912BBB00_AC05_4BA4_A4FF343D50597D8F

#include "gf/Message.h"

namespace gf {
    
    namespace core {
        
        class CoreMessage : public Message {
        public:
            CoreMessage() {}
            ~CoreMessage() {}

            GF_DECLARE_MESSAGE;

        };

        class QuitMessage : public CoreMessage {
        public:
            QuitMessage() {}
            ~QuitMessage() {}

            GF_DECLARE_MESSAGE;

        };
        
    }
    
}

#endif // header
