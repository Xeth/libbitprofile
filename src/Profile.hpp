#pragma once

#include "Auth.hpp"
#include "detail/Contract.hpp"
#include "detail/ContractFactory.hpp"


namespace BitProfile{


class Profile : public Contract
{
    public:
        Profile(Provider &provider, const std::string &addres);

        bool set(const std::string &key, const std::string &value);
        bool clear(const std::string &key);
        std::string get(const std::string &key);

        address_t getPaymentAddress();
        bool setPaymentAddress(const address_t &);

        bool authenticate(const address_t &, Auth::Permission);
        address_t getAuth();

        bool transfer(const address_t &);

        template<class Callback>
        void set(const std::string &key, const std::string &value, const Callback &);

        template<class Callback>
        void clear(const std::string &key, const Callback &);

        template<class Callback>
        void setPaymentAddress(const address_t &, const Callback &);

        template<class Callback>
        void transfer(const address_t &, const Callback &);

        txid_t setPermission(const std::string &key, Auth::Permission);
        txid_t kill();

    private:
        bool checkKey(std::string key, std::string value);
        bool checkOwner(address_t);
};


DECLARE_CONTRACT_FACTORY(ProfileFactory, Profile, ContractCode::Profile);

}

#include "Profile.ipp"
