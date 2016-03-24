#pragma once

#include "Auth.hpp"
#include "detail/Contract.hpp"
#include "detail/ContractFactory.hpp"


namespace BitProfile{


class AddressAuth :
    public Contract
{
    public:
        AddressAuth(Provider &, const address_t &address);

        txid_t set(const address_t &address, Auth::Permission);
        txid_t remove(const address_t &address);

        bool authenticate(const address_t &address, Auth::Permission);
};

DECLARE_CONTRACT_FACTORY(AddressAuthFactory, AddressAuth, BitProfile::ContractCode::AddressAuth);


}
