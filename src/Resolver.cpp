#include "Resolver.hpp"


namespace BitProfile{


Resolver::Resolver(Provider &provider) :
    _master(provider),
    _provider(provider)
{}



Resolver::Resolver(Provider &provider, MasterRegistrar::Network net) :
    _master(provider, net),
    _provider(provider)
{}



Profile Resolver::lookup(const std::string &uri)
{
    try
    {
        size_t offset = uri.find(':');
        if(uri[0]=='b' && offset!=std::string::npos)
        {
            size_t index = boost::lexical_cast<size_t>(uri.substr(1, offset-1));
            std::string name = uri.substr(offset+1);
            Registrar registrar = _master.get(index);
            return registrar.get(name);
        }
    }
    catch(...)
    {}

    return Profile(_provider, "");
}


}
