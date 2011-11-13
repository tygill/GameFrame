#pragma once
#ifndef idA7FD5609_7D7E_4A52_BD148C7C991FB1E1
#define idA7FD5609_7D7E_4A52_BD148C7C991FB1E1

#include <gf/EntityTemplate.h>

class TestEntityTemplate : public gf::EntityTemplate {
public:
    gf::EntityId create(gf::EntityManager* manager);
};

#endif // header
