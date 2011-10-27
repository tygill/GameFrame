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
    
}
