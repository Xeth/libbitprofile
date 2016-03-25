#include "Registrar.hpp"


namespace BitProfile{

Registrar::Registrar(Provider &provider, const address_t &address) :
    Contract(provider, address)
{}


Registrar::Registrar(Provider &provider, const address_t &address, const URI &uri) :
    Contract(provider, address),
    _uri(uri)
{}


const Registrar::URI & Registrar::getURI() const
{
    return _uri;
}


bool Registrar::create(const std::string &name)
{
    if(contains(name))
    {
        return false;
    }

    return executeConfirm
    (
        "register(string,string)",
        CONTRACT_ARGUMENTS(name, ""),
        boost::bind(&Registrar::checkProfile, this, name, getSenderAddress(), true)
    );
}


bool Registrar::link(const std::string &name, const address_t &address)
{
    if(contains(name))
    {
        return false;
    }

    return executeConfirm
    (
        "link(string,address,string)",
        CONTRACT_ARGUMENTS(name, address, ""),
        boost::bind(&Registrar::checkProfile, this, name, address, true)
    );
}


bool Registrar::unlink(const std::string &name)
{
    if(!contains(name))
    {
        return true;
    }
    return executeConfirm
    (
        "unlink(string,string)",
        CONTRACT_ARGUMENTS(name, ""),
        boost::bind(&Registrar::checkProfile, this, name, getSenderAddress(), false)
    );
}


bool Registrar::contains(const std::string &name)
{
    return call<bool, Bool_Type>("contains(string)", CONTRACT_ARGUMENTS(name));
}


Profile Registrar::get(const std::string &name)
{
    return Profile(getProvider(), call<address_t, Address_Type>("getProfile(string)", CONTRACT_ARGUMENTS(name)), ProfileURI(_uri, name));
}



bool Registrar::checkProfile(std::string name, address_t address, bool active)
{
    Profile profile = get(name);
    return profile.authenticate(address, Auth::Owner) == active;
}


}
