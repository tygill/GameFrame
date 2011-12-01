#pragma once
#ifndef id08AEA933_8019_4B32_9FF334AF6DF9D0FA
#define id08AEA933_8019_4B32_9FF334AF6DF9D0FA

#include "gf/EntitySystem.h"

namespace gf {

    namespace core {
    
        class CoreSystem : public EntitySystem {
        public:
            CoreSystem(GameFrame* frame);
            ~CoreSystem();

            void receive(MessagePtr message);

        };
    
    }

}

#endif // header
