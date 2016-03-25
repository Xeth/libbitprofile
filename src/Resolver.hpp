#pragma once

#include <boost/shared_ptr.hpp>

#include "MasterRegistrar.hpp"


namespace BitProfile{


class Resolver
{
    public:

        Resolver(Provider &);
        Resolver(Provider &, MasterRegistrar::Network);

        Profile lookupProfile(const std::string &name);
        Registrar lookupRegistrar(const std::string &name);


    private:
        Registrar lookupRegistrar(const char *, size_t);

    private:
        MasterRegistrar _master;
        Provider &_provider;
};


}
