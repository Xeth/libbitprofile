#include "AddressAuthKey.hpp"


namespace BitProfile{


AddressAuthKey::AddressAuthKey(const address_t & address) : 
    _address(address)
{}

const address_t & AddressAuthKey::getAddress() const
{
    return _address;
}


std::pair<bool, std::string> AddressAuthKey::getAuthData(const std::string &password) const
{
    return std::make_pair(true, "");
}





}
