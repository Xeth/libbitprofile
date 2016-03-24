#pragma once

#include <boost/bind.hpp>

#include "Auth.hpp"
#include "detail/Contract.hpp"
#include "detail/ContractFactory.hpp"


namespace BitProfile{


class AddressAuth :
    public Contract
{
    public:
        AddressAuth(Provider &, const address_t &address);

        bool set(const address_t &address, Auth::Permission);
        bool remove(const address_t &address);

        template<class Callback>
        void set(const address_t &address, Auth::Permission, const Callback &);

        template<class Callback>
        void remove(const address_t &address, const Callback &callback);

        bool authenticate(const address_t &address, Auth::Permission);

    private:
        bool checkAuth(address_t, Auth::Permission, bool active);
};

DECLARE_CONTRACT_FACTORY(AddressAuthFactory, AddressAuth, BitProfile::ContractCode::AddressAuth);


}

#include "AddressAuth.ipp"
