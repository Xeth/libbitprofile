#include "KeyAdapter.hpp"


namespace BitProfile{


const address_t & KeyAdapter::getAddress() const
{
    return _holder->getAddress();
}


std::pair<bool, std::string> KeyAdapter::getAuthData(const std::string &password)
{
    return _holder->getAuthData(password);
}


std::string KeyAdapter::getTypeName() const
{
    return _holder->getTypeName();
}



}
