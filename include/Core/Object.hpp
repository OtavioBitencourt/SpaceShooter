#pragma once
#include <string>

#define CLASS_NAME(name)\
public:\
static std::string StaticClassName() \
{\
    return #name;\
}\
virtual std::string GetClassName() const \
{\
    return #name;\
}

class Object
{
public: 
    virtual ~Object() = default;

    virtual std::string GetClassName() const
    {
        return "Object";
    }
};