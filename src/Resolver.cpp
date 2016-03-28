#include "Resolver.hpp"


namespace BitProfile{


Resolver::Resolver(Provider &provider) :
    _master(provider),
    _provider(provider)
{}



Resolver::Resolver(Provider &provider, Network net) :
    _master(provider, net),
    _provider(provider)
{}



Profile Resolver::lookupProfile(const std::string &uri)
{
    try
    {
        size_t offset = uri.find(':');
        if(offset!=std::string::npos)
        {
            Registrar registrar = lookupRegistrar(uri.data(), offset);
            std::string name = uri.substr(offset+1);
            if(registrar.isNull())
            {
                return Profile(_provider, "");
            }
            return registrar.get(name);
        }
    }
    catch(...)
    {}

    return Profile(_provider, "");
}


Registrar Resolver::lookupRegistrar(const std::string &uri)
{
    return lookupRegistrar(uri.data(), uri.size());
}


Registrar Resolver::lookupRegistrar(const char *uri, size_t size)
{
    if(uri[0]!='b')
    {
        return Registrar(_provider, "");
    }
    size_t index = boost::lexical_cast<size_t>(std::string(uri+1, size-1));
    return _master.get(index);
}


}
