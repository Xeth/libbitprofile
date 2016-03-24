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



Profile Resolver::resolve(const std::string &uri)
{
    size_t offset = uri.find(':');
    if(uri[0]=='b' && offset==std::string::npos)
    {
        size_t index = boost::lexical_cast<size_t>(uri.substr(1, offset));
        std::string name = uri.substr(offset);

        Registrar registrar = _master.get(index);
        return registrar.get(name);
    }
    return Profile(_provider, "");
}


}
