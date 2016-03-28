#pragma once

#include <boost/shared_ptr.hpp>

#include "MasterRegistrar.hpp"
#include "Network.hpp"


namespace BitProfile{


class Resolver
{
    public:

        Resolver(Provider &);
        Resolver(Provider &, Network);

        Profile lookupProfile(const std::string &name);
        Registrar lookupRegistrar(const std::string &name);


    private:
        Registrar lookupRegistrar(const char *, size_t);

    private:
        MasterRegistrar _master;
        Provider &_provider;
};


}
