#include "gf/EntitySystemThread.h"
#include "gf/EntitySystem.h"
#include "gf/GameFrame.h"

#include <boost/thread.hpp>
#include <boost/chrono.hpp>

namespace gf {

    EntitySystemThread::EntitySystemThread(GameFrame* frame) :
        framework(frame)
    {
    }

    EntitySystemThread::~EntitySystemThread() {
        // nothing...
    }
    
    void EntitySystemThread::operator()() {
        boost::chrono::milliseconds delta;
        boost::chrono::steady_clock::time_point then;
        boost::chrono::steady_clock::time_point now;
        while (framework->isRunning()) {
            now = boost::chrono::steady_clock::now();
            delta = boost::chrono::duration_cast<boost::chrono::milliseconds>(now - then);
            then = now;
            //std::cout << "Delta: " << delta << std::endl;
            for (EntitySystems::iterator itr = systems.begin(); itr != systems.end(); itr++) {
                (*itr)->update(delta);
            }
            
            boost::this_thread::sleep(boost::posix_time::milliseconds(50)); 
        }
    }
    
}
