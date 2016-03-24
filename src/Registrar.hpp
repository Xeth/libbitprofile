#pragma once 

#include "detail/Contract.hpp"
#include "Profile.hpp"

namespace BitProfile{


class Registrar : public Contract
{
    public:
        Registrar(Provider &provider, const std::string &addres);

        bool create(const std::string &);

        template<class Callback>
        void create(const std::string &, const Callback &);

        bool link(const std::string &, const address_t &address);

        template<class Callback>
        void link(const std::string &, const address_t &address, const Callback &);

        bool unlink(const std::string &);

        template<class Callback>
        void unlink(const std::string &, const Callback &);

        bool contains(const std::string &);
        Profile get(const std::string &);

    private:
        bool checkProfile(std::string, address_t owner, bool active);

};


}

#include "Registrar.ipp"
