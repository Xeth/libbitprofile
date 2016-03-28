#pragma once 

#include <json/value.h>

#include "Profile.hpp"
#include "AddressAuthKey.hpp"
#include "detail/KeyAdapter.hpp"
#include "AddressAuthKey.hpp"


namespace BitProfile{


class ProfileDescriptor
{
    public:

        template<class Key>
        ProfileDescriptor(const Profile &, const Key &);

        ProfileDescriptor(const Json::Value &);

        std::string getURI() const;
        std::string getName() const;
        std::string getContext() const;
        address_t getAddress() const;

        std::string getAuthType() const;
        std::string getAuthAddress() const;

        KeyAdapter getProfileKey() const;

    private:
        Json::Value serializeKey(const Profile &, const AddressAuthKey &);

    private:
        Json::Value _data;
};



}

#include "ProfileDescriptor.ipp"
