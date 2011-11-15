#include "DummyResourceTemplate.h"
#include "DummyResource.h"

gf::ResourcePtr DummyResourceTemplate::create() {
    gf::ResourcePtr res(new DummyResource());
    return res;
}
