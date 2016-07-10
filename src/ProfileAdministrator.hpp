#pragma once

#include "ethrpc/BlockChain.hpp"

#include "Profile.hpp"
#include "Registrar.hpp"
#include "AddressAuth.hpp"
#include "AddressAuthKey.hpp"
#include "ProfileDescriptor.hpp"
#include "Resolver.hpp"

#include "detail/types.hpp"
#include "detail/KeyAdapter.hpp"


namespace BitProfile{


class ProfileAdministrator
{
    public:
        template<class Key>
        ProfileAdministrator(const Profile &, const Key &);

        ProfileAdministrator(const Profile &, const KeyAdapter &);

        void setGasPrice(const BigInt &);
        void setGasLimit(const BigInt &);

        template<class Permit>
        bool set(const std::string &key, const std::string &value, const Permit &);

        template<class Permit, class Callback>
        void set(const std::string &key, const std::string &value, const Permit &, const Callback &);

        template<class Permit>
        bool setPaymentAddress(const address_t &, const Permit &);

        template<class Permit, class Callback>
        void setPaymentAddress(const address_t &, const Permit &, const Callback &);

        template<class Permit>
        bool changeAuth(const AddressAuth &, const Permit &);

        template<class Permit, class Callback>
        void changeAuth(const AddressAuth &, const Permit &, const Callback &);

        template<class Permit>
        bool link(Registrar &, const std::string &name, const Permit &);

        template<class Permit>
        bool unlink(Registrar &, const Permit &);

        template<class Permit, class Callback>
        void link(Registrar &, const std::string &name, const Permit &, const Callback &);

        template<class Permit, class Callback>
        void unlink(Registrar &, const Permit &, const Callback &);

        template<class Permit>
        bool move(Registrar &, const std::string &name, const Permit &, const BigInt &gas);

        template<class Permit>
        static ProfileAdministrator CreateProfile(Registrar &, const std::string &name, const Permit &);

        template<class Permit>
        static ProfileAdministrator CreateProfile(Registrar &, const std::string &name, const address_t &, const Permit &);

        template<class Permit, class Callback>
        static void CreateProfileAsync(Registrar &, const std::string &name, const Permit &, const Callback &);

        template<class Permit, class Callback>
        static void CreateProfileAsync(Registrar &, const std::string &name, const address_t &, const Permit &, const Callback &);

        template<class Key, class Permit>
        static ProfileAdministrator CreateProfile(Registrar &, const std::string &name, const Key &, const Permit &);

        template<class Key, class Permit, class Callback>
        static void CreateProfileAsync(Registrar &, const std::string &name, const Key &, const Permit &, const Callback &);

        static ProfileAdministrator FromDescriptor(Provider &, const ProfileDescriptor &);

        const KeyAdapter & getKey() const;
        const Profile & getProfile() const;
        bool isNull() const;

    private:
        template<class Callback, class Key>
        class ChangeAuthCallback;

        template<class Callback, class Key>
        class CreateProfileCallback;

        template<class Callback, class Permit>
        class RenameProfileCallback;

    private:
        Profile _profile;
        KeyAdapter _key;
};


}

#include "ProfileAdministrator.ipp"
