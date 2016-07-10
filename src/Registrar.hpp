#pragma once 

#include "detail/Contract.hpp"
#include "detail/RegistrarURI.hpp"

#include "Network.hpp"
#include "Profile.hpp"


namespace BitProfile{


class Registrar : public Contract
{
    public:
        typedef RegistrarURI URI;

    public:
        Registrar(Provider &provider, const std::string &address);
        Registrar(Provider &provider, const std::string &addres, const URI &uri, Network net);

        template<class Permit>
        bool create(const std::string &name, const std::string &authData, const Permit &);

        template<class Permit>
        bool link(const std::string &, const address_t &address, const std::string &authData, const Permit &);

        template<class Permit>
        bool unlink(const std::string &, const std::string &authData, const Permit &);

        template<class Permit, class Callback>
        void create(const std::string &name, const std::string &authData, const Permit &, const Callback &);

        template<class Permit, class Callback>
        void link(const std::string &, const address_t &address, const std::string &authData, const Permit &, const Callback &);

        template<class Permit, class Callback>
        void unlink(const std::string &, const std::string &authData, const Permit &, const Callback &);


        bool contains(const std::string &);
        Profile get(const std::string &);

        const URI & getURI() const;

        address_t getProfileFactory() const;
        Network getNetwork() const;

    private:
        bool validateName(const std::string &) const;
        bool checkProfile(std::string, address_t owner, bool active);

    private:
        URI _uri;
        Network _net;

};


}

#include "Registrar.ipp"
