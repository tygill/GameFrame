#include "gf/sdl/WindowSystem.h"

#include "gf/sdl/Sprite.h"

#include "gf/GameFrame.h"
#include "gf/sdl/PositionComponent.h"
#include "gf/sdl/RenderableComponent.h"

namespace gf {

    namespace sdl {

        WindowSystem::WindowSystem(GameFrame* frame) :
            EntitySystem(frame),
            screen(NULL)
        {
            types.insert(componentType<PositionComponent>());
            types.insert(componentType<RenderableComponent>());
            framework->entityManager().registerEntityCache(types);
            screen = SDL_SetVideoMode(800, 600, 0, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_RESIZABLE);
        }

        WindowSystem::~WindowSystem() {
            if (screen) {
                // This is already either deleted, or will be deleted by the call to SDL_Quit()
                // All surfaces created by SDL will be automatically cleaned up then.
                //SDL_FreeSurface(screen);
            }
        }

        void WindowSystem::update(boost::chrono::milliseconds delta) {
            if (screen) {
                SDL_FillRect(screen, NULL, 0);
                //std::cout << "Updating screen" << std::endl;
                Entities ents = framework->entityManager().getEntities(types);
                for (Entities::iterator itr = ents.begin(); itr != ents.end(); itr++) {
                    boost::shared_ptr<RenderableComponent> renderable = itr->getComponent<RenderableComponent>();
                    boost::shared_ptr<PositionComponent> position = itr->getComponent<PositionComponent>();
                    ConstSpritePtr sprite = framework->resourceManager().get<Sprite>(renderable->sprite());
                    
                    SDL_Rect rect;
                    rect.x = position->x();
                    rect.y = position->y();

                    SDL_BlitSurface(sprite->surface(), 0, screen, &rect);
                }

                SDL_Flip(screen);
                //std::cout << "Screen updated" << std::endl;
            }
        }
    }

}
