#include "AddressAuthKey.hpp"


namespace BitProfile{


AddressAuthKey::AddressAuthKey(const address_t & address) : 
    _address(address)
{}

const address_t & AddressAuthKey::getAddress() const
{
    return _address;
}


std::pair<bool, std::string> AddressAuthKey::authenticate(Provider &provider, const std::string &password)
{
    Ethereum::Connector::Wallet wallet(provider);
    return std::make_pair(wallet.unlockAccount(_address, password, 5), "");
}




}
