#include "gf/Message.h"

namespace gf {
    
    MessageType Message::nextRegistrationType = 1;
    
    Message::Message()
    {
    }

    Message::~Message() {
    }

    MessageType Message::type() const {
        throw MethodNotDefinedException("Message::type() was not redefined in a subclass. Did a custom message class not have a GF_DECLARE_MESSAGE macro?");
    }
    
    MessageType Message::registerType() {
        return nextRegistrationType++;
    }
    
}
