#include "gf/sdl/SDLEventSystem.h"
#include "gf/GameFrame.h"
#include "gf/core/CoreMessages.h"
#include "gf/sdl/PositionComponent.h"

#include <SDL.h>

namespace gf {

    namespace sdl {

        SDLEventSystem::SDLEventSystem(GameFrame* frame) : EntitySystem(frame) {
            gf::sdl::init();
            framework->entityManager().registerEntityCache<gf::sdl::PositionComponent>();
        }

        SDLEventSystem::~SDLEventSystem() {
            gf::sdl::quit();
        }

        void SDLEventSystem::update(boost::chrono::milliseconds delta) {
            SDL_PumpEvents();

            //SDL_Delay(330);
            boost::this_thread::sleep(boost::posix_time::milliseconds(50));

            SDL_Event ev;
            while (SDL_PeepEvents(&ev, 1, SDL_GETEVENT, SDL_ALLEVENTS) > 0) {
                //quit somehow
                //std::cout << "Stoping!" << std::endl;
                //boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
                Entities ents = framework->entityManager().getEntities<gf::sdl::PositionComponent>();
                switch (ev.type) {
                case SDL_QUIT:
                    framework->messageManager().send<gf::core::QuitMessage>();
                    break;
                case SDL_KEYDOWN:
                    for (Entities::iterator itr = ents.begin(); itr != ents.end(); itr++) {
                        switch (ev.key.keysym.sym) {
                        case SDLK_UP:
                            framework->entityManager().getComponent<gf::sdl::PositionComponent>(itr->id())->moveY(-5);
                            break;
                        case SDLK_DOWN:
                            framework->entityManager().getComponent<gf::sdl::PositionComponent>(itr->id())->moveY(5);
                            break;
                        case SDLK_LEFT:
                            framework->entityManager().getComponent<gf::sdl::PositionComponent>(itr->id())->moveX(-5);
                            break;
                        case SDLK_RIGHT:
                            framework->entityManager().getComponent<gf::sdl::PositionComponent>(itr->id())->moveX(5);
                            break;
                        }
                    }
                    break;
                default:
                    //std::cout << "Other SDL event!" << std::endl;
                    break;
                }
            }
        }

    }

}
