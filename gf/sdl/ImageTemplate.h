#pragma once
#ifndef id06024399_11B8_40E8_BE0737A166914FED
#define id06024399_11B8_40E8_BE0737A166914FED

#include "gf/ResourceTemplate.h"

namespace gf {

    namespace sdl {
    
        class ImageTemplate : public gf::ResourceTemplate {
        public:
            ImageTemplate(std::string file);

        private:
            ResourcePtr create();

            std::string filename;

        };
    
    }

}

#endif // header
