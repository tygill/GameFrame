#pragma once
#ifndef idDD09B9D0_4822_4B7E_98FE49787C773FD8
#define idDD09B9D0_4822_4B7E_98FE49787C773FD8

#include <gf/Message.h>

class EmptyMessage : public gf::Message {
public:
    EmptyMessage() {}
    ~EmptyMessage() {}

    //gf::MessageType type() const {return gf::messageType<EmptyMessage>();}

};

#endif // header
