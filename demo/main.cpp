#include <gf/GameFrame.h>
#include <gf/sdl/GameFrameSDL.h>
#include <gf/sdl/SDLEventSystem.h>
#include <gf/core/CoreSystem.h>


int main(int argc, char* argv[]) {
    
    gf::GameFrame frame;

    frame.addSystem<gf::core::CoreSystem>();
    frame.addSystem<gf::sdl::WindowSystem>();
    frame.addSystem<gf::sdl::SDLEventSystem>();

    gf::ResourceTemplatePtr image(new gf::sdl::ImageTemplate("./vgfm.logo.png"));
    gf::ResourceId sprite = frame.resourceManager().define<gf::sdl::Sprite>(image);
    std::cout << "Loading sprite" << std::endl;
    frame.resourceManager().load<gf::sdl::Sprite>(sprite);
    std::cout << "Sprite loaded" << std::endl;

    gf::EntityId ent = frame.entityManager().create();
    
    auto pos = frame.entityManager().addComponent<gf::sdl::PositionComponent>(ent);
    pos->setX(50);
    pos->setY(50);
    
    auto rend = frame.entityManager().addComponent<gf::sdl::RenderableComponent>(ent);

    rend->setSprite(sprite);

    frame.run();
    
    frame.resourceManager().unload<gf::sdl::Sprite>(sprite);
    return 0;
}
    