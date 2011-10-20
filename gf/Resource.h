#pragma once
#ifndef id50D8F1FA_1EA6_4573_9BEF3B720902FB13
#define id50D8F1FA_1EA6_4573_9BEF3B720902FB13

#include "gf/Global.h"

namespace gf {
    
    class Resource {
    public:
        Resource() {}
        ~Resource() {}
        
        ResourceType type() const;
        //template<class T> static ResourceType getType();
    };
    
}

#endif // header
