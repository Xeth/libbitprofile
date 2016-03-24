#pragma once

#include "Auth.hpp"
#include "detail/Contract.hpp"
#include "detail/ContractFactory.hpp"


namespace BitProfile{


class Profile : public Contract
{
    public:
        Profile(Provider &provider, const std::string &addres);

        txid_t set(const std::string &key, const std::string &value);
        txid_t clear(const std::string &key);
        std::string get(const std::string &key);

        address_t getPaymentAddress();
        void setPaymentAddress(const address_t &);

        txid_t setPermission(const std::string &key, Auth::Permission);

        bool authenticate(const address_t &, Auth::Permission);
        address_t getAuth();

        txid_t transfer(const address_t &);
        txid_t kill();
};


DECLARE_CONTRACT_FACTORY(ProfileFactory, Profile, ContractCode::Profile);

}
