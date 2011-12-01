#include "gf/core/CoreSystem.h"
#include "gf/GameFrame.h"
#include "gf/core/CoreMessages.h"

#include <SDL.h>

namespace gf {

    namespace core {

        CoreSystem::CoreSystem(GameFrame* frame) : EntitySystem(frame) {
            framework->messageManager().registerSystem(this, messageType<gf::core::QuitMessage>());
        }

        CoreSystem::~CoreSystem() {
            //
        }

        void CoreSystem::receive(MessagePtr message) {
            if (message->type() == messageType<QuitMessage>()) {
                framework->stop();
            }
            
        }

    }

}
