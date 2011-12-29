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

    class MethodNotDefinedException : public GameFrameException {
    public:
        MethodNotDefinedException(const std::string& msg) throw();
        ~MethodNotDefinedException();
        
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

    class ResourceNotFoundException : public GameFrameException {
    public:
        ResourceNotFoundException(ResourceType t, ResourceId i) throw();
        ~ResourceNotFoundException() throw();

        ResourceType type() const throw();
        ResourceId id() const throw();

    private:
        ResourceType resType;
        ResourceId resId;

    };
    
}

#endif // header
