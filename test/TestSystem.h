#pragma once
#ifndef idD622BFCC_9E17_4151_95767DDB5C74D7D4
#define idD622BFCC_9E17_4151_95767DDB5C74D7D4

#include <gf/EntitySystem.h>

class TestSystem : public gf::EntitySystem {
public:
    TestSystem(void);
    ~TestSystem(void);

    void added(gf::ConstEntityPtr entity);
    void removed(gf::ConstEntityPtr entity);

    void receive(gf::MessagePtr message);

    int entityCount() const;
    int messageCount() const;

private:
    int entitiesReceived;
    int messagesReceived;

};

#endif
