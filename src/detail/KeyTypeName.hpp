#pragma once 

#include <stdexcept>
#include <string>

#include "../AddressAuthKey.hpp"


namespace BitProfile{


template<class Key>
std::string KeyTypeName()
{
    throw std::runtime_error("not implemented");
}


template<>
std::string KeyTypeName<AddressAuthKey>();


}

