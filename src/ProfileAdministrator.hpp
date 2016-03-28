#pragma once

#include "Profile.hpp"
#include "AddressAuth.hpp"
#include "AddressAuthKey.hpp"

#include "detail/types.hpp"
#include "detail/KeyAdapter.hpp"


namespace BitProfile{


class ProfileAdministrator
{
    public:
        template<class Key>
        ProfileAdministrator(const Profile &, const Key &);

        bool set(const std::string &key, const std::string &value, const std::string &password);

        template<class Callback>
        void set(const std::string &key, const std::string &value, const std::string &password, const Callback &);


        bool changeAuth(const AddressAuth &, const std::string &password);

        template<class Callback>
        void changeAuth(const AddressAuth &, const std::string &password, const Callback &);


        const Profile & getProfile() const;

    private:
        template<class Callback>
        class ChangeAuthCallback;

    private:
        Profile _profile;
        KeyAdapter _key;
};


}
