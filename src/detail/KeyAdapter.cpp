#include "KeyAdapter.hpp"


namespace BitProfile{


const address_t & KeyAdapter::getAddress() const
{
    return _holder->getAddress();
}


std::pair<bool, std::string> KeyAdapter::authenticate(Provider &provider, const std::string &password)
{
    return _holder->authenticate(provider, password);
}


std::string KeyAdapter::getTypeName() const
{
    return _holder->getTypeName();
}



}
