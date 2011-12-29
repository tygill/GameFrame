#include "gf/Exceptions.h"

#include <sstream>

namespace gf {
    
    GameFrameException::GameFrameException() throw() :
        message("An exception has occured inside the GameFrame framework")
    {
    }
    
    GameFrameException::GameFrameException(const std::string& msg) throw() :
        message(msg)
    {
    }
    
    GameFrameException::~GameFrameException() throw() {
    }
    
    const char* GameFrameException::what() const throw() {
        return message.c_str();
    }
    
    void GameFrameException::setMessage(const std::string& msg) throw() {
        message = msg;
    }

    // MethodNotDefinedException
    // -------------------------

    MethodNotDefinedException::MethodNotDefinedException(const std::string& msg) :
        GameFrameException(msg)
    {
    }

    MethodNotDefinedException::~MethodNotDefinedException() {
    }
    
    // EntityNotFoundException
    // -----------------------

    EntityNotFoundException::EntityNotFoundException(EntityId desiredId) throw() :
        entId(desiredId)
    {
        std::stringstream str;
        str << "Entity '" << entId << "' was not found";
        setMessage(str.str());
    }
    
    EntityNotFoundException::~EntityNotFoundException() throw() {
    }
    
    EntityId EntityNotFoundException::id() const throw() {
        return entId;
    }
    
    // EntitySetNotCachedException
    // ---------------------------

    EntitySetNotCachedException::EntitySetNotCachedException(const ComponentTypes& t) throw() :
        GameFrameException("The set of entities requested was not registered to be cached."),
        cTypes(t.begin(), t.end())
    {
    }

    EntitySetNotCachedException::~EntitySetNotCachedException() throw() {
    }

    ComponentTypes EntitySetNotCachedException::types() const throw() {
        return cTypes;
    }

    // ResourceNotFoundException
    // -------------------------

    ResourceNotFoundException::ResourceNotFoundException(ResourceType t, ResourceId i) throw() :
        resType(t),
        resId(i)
    {
    }

    ResourceNotFoundException::~ResourceNotFoundException() throw() {
    }

    ResourceType ResourceNotFoundException::type() const throw() {
        return resType;
    }

    ResourceId ResourceNotFoundException::id() const throw() {
        return resId;
    }
}
