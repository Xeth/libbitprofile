#pragma once 


#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"


#include "detail/types.hpp"


namespace BitProfile{


class AddressAuthKey
{
    public:

        AddressAuthKey(const address_t &);

        const address_t & getAddress() const;
        std::pair<bool, std::string> getAuthData(const std::string &password) const;


    private:
        address_t _address;
};



}
