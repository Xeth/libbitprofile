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

address_t Registrar::getProfileFactory() const
{
    return call<address_t, Address_Type>("getFactory()");
}


bool Registrar::create(const std::string &name, const std::string &authData)
{
    return create(name, getSenderAddress(), authData);
}

bool Registrar::create(const std::string &name, const address_t &address, const std::string &authData)
{
    if(contains(name))
    {
        return false;
    }

    return executeConfirm
    (
        "register(bytes32,bytes)",
        CONTRACT_ARGUMENTS(ABI_FIXED(name), authData),
        boost::bind(&Registrar::checkProfile, this, name, address.size()?address:getSenderAddress(), true)
    );
}


bool Registrar::link(const std::string &name, const address_t &address, const std::string &authData)
{
    if(contains(name))
    {
        return false;
    }

    return executeConfirm
    (
        "link(bytes32,address,bytes)",
        CONTRACT_ARGUMENTS(ABI_FIXED(name), address, authData),
        boost::bind(&Registrar::checkProfile, this, name, address, true)
    );
}


bool Registrar::unlink(const std::string &name, const std::string &authData)
{
    if(!contains(name))
    {
        return true;
    }
    return executeConfirm
    (
        "unlink(bytes32,bytes)",
        CONTRACT_ARGUMENTS(ABI_FIXED(name), authData),
        boost::bind(&Registrar::checkProfile, this, name, getSenderAddress(), false)
    );
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
    return profile.authenticate(address, Auth::Owner) == active;
}


}
