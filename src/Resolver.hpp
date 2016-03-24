#pragma once

#include <boost/shared_ptr.hpp>

#include "MasterRegistrar.hpp"


namespace BitProfile{


class Resolver
{
    public:

        Resolver(Provider &);
        Resolver(Provider &, MasterRegistrar::Network);

        Profile resolve(const std::string &name);


    private:
        MasterRegistrar _master;
        Provider &_provider;
};


}
