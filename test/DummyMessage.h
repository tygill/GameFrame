#pragma once
#ifndef id6C58201B_B4C5_4878_B92A47FD04A1EA46
#define id6C58201B_B4C5_4878_B92A47FD04A1EA46

#include <gf/Message.h>

class DummyMessage : public gf::Message {
public:
    DummyMessage() {}
    ~DummyMessage() {}

    gf::MessageType type() const {return gf::messageType<DummyMessage>();}

};

#endif // header
