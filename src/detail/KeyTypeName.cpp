#include "KeyTypeName.hpp"


namespace BitProfile{


template<>
std::string KeyTypeName<AddressAuthKey>()
{
    return "address";
}


}
