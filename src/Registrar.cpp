#include "Registrar.hpp"


namespace BitProfile{

Registrar::Registrar(Provider &provider, const address_t &address) :
    Contract(provider, address)
{}


Registrar::Registrar(Provider &provider, const address_t &address, const URI &uri, Network net) :
    Contract(provider, address),
    _uri(uri),
    _net(net)
{}


Network Registrar::getNetwork() const
{
    return _net;
}

bool Registrar::validateName(const std::string &name) const
{
    if(name.size()>32)
    {
        return false;
    }

    for(std::string::const_iterator it=name.begin(), end=name.end(); it!=end; ++it)
    {
        char c = *it;
        if(c<48||c>122||(c!=95&&c>57&&c<97))
        {
            return false;
        }
    }
    return true;
}

const Registrar::URI & Registrar::getURI() const
{
    return _uri;
}

address_t Registrar::getProfileFactory() const
{
    return call<address_t, Address_Type>("getFactory()");
}





bool Registrar::contains(const std::string &name)
{
    return call<bool, Bool_Type>("contains(bytes32)", CONTRACT_ARGUMENTS(ABI_FIXED(name)));
}


Profile Registrar::get(const std::string &name)
{
    return Profile(getProvider(), call<address_t, Address_Type>("getProfile(bytes32)", CONTRACT_ARGUMENTS(ABI_FIXED(name))), ProfileURI(_uri, name));
}



bool Registrar::checkProfile(std::string name, address_t address, bool active)
{
    Profile profile = get(name);
    return profile.authenticate(address, BitProfile::Auth::Owner) == active;
}


}
