#include "gf/EntitySystemThread.h"
#include "gf/EntitySystem.h"

#include <boost/chrono.hpp>

namespace gf {
    
    void EntitySystemThread::operator()() {
        boost::chrono::nanoseconds delta;
        boost::chrono::steady_clock::time_point then;
        boost::chrono::steady_clock::time_point now;
        while (true) {
            now = boost::chrono::steady_clock::now();
            delta = now - then;
            then = now;
            for (EntitySystems::iterator itr = systems.begin(); itr != systems.end(); itr++) {
                (*itr)->update(delta);
            }
        }
    }
    
}
