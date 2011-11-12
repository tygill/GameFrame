#pragma once
#ifndef id6215D338_5C6B_4478_9F4BA99C36A70E9B
#define id6215D338_5C6B_4478_9F4BA99C36A70E9B

#include "gf/Global.h"

#include <exception>

namespace gf {
    
    // Parent class for all GameFrame exceptions
    class GameFrameException : public std::exception {
    public:
        GameFrameException() throw();
        GameFrameException(const std::string& msg) throw();
        ~GameFrameException() throw();
        
        const char* what() const throw();
        
    protected:
        void setMessage(const std::string& msg) throw();
        
    private:
        std::string message;

    };
    
    class EntityNotFoundException : public GameFrameException {
    public:
        EntityNotFoundException(EntityId desiredId) throw();
        ~EntityNotFoundException() throw();
        
        EntityId id() const throw();
        
    private:
        EntityId entId;

    };

    class EntitySetNotCachedException : public GameFrameException {
    public:
        EntitySetNotCachedException(const ComponentTypes& t) throw();
        ~EntitySetNotCachedException() throw();

        ComponentTypes types() const throw();

    private:
        ComponentTypes cTypes;

    };
    
}

#endif // header
