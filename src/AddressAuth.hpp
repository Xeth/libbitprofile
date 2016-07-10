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

        template<class Permit>
        bool set(const address_t &address, BitProfile::Auth::Permission, const Permit &);

        template<class Permit>
        bool remove(const address_t &address, const Permit &);

        template<class Permit, class Callback>
        void set(const address_t &address, BitProfile::Auth::Permission, const Permit &, const Callback &);

        template<class Permit, class Callback>
        void remove(const address_t &address, const Permit &, const Callback &callback);


        bool authenticate(const address_t &address, BitProfile::Auth::Permission);

    private:
        bool checkAuth(address_t, BitProfile::Auth::Permission, bool active);
};

DECLARE_CONTRACT_FACTORY(AddressAuthFactory, AddressAuth, BitProfile::ContractCode::AddressAuth);


}

#include "AddressAuth.ipp"
