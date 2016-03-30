#pragma once 

#include "detail/Contract.hpp"
#include "detail/RegistrarURI.hpp"

#include "Profile.hpp"

namespace BitProfile{


class Registrar : public Contract
{
    public:
        typedef RegistrarURI URI;

    public:
        Registrar(Provider &provider, const std::string &address);
        Registrar(Provider &provider, const std::string &addres, const URI &uri);

        bool create(const std::string &name, const std::string &authData="");

        template<class Callback>
        void create(const std::string &name, const std::string &authData, const Callback &);

        bool create(const std::string &name, const address_t &address, const std::string &authData="");

        template<class Callback>
        void create(const std::string &name, const address_t &address, const std::string &authData, const Callback &);

        bool link(const std::string &, const address_t &address, const std::string &authData="");

        template<class Callback>
        void link(const std::string &, const address_t &address, const std::string &authData, const Callback &);

        bool unlink(const std::string &, const std::string &authData="");

        template<class Callback>
        void unlink(const std::string &, const std::string &authData, const Callback &);

        bool contains(const std::string &);
        Profile get(const std::string &);

        const URI & getURI() const;

        address_t getProfileFactory() const;

    private:
        bool checkProfile(std::string, address_t owner, bool active);

    private:
        URI _uri;

};


}

#include "Registrar.ipp"
