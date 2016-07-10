#include "Profile.hpp"


namespace BitProfile{


Profile::Profile(Provider &provider, const address_t &address) :
    Contract(provider, address)
{}


Profile::Profile(Provider &provider, const address_t &address, const URI &uri) :
    Contract(provider, address),
    _uri(uri)
{}

bool Profile::validateKey(const std::string &key) const
{
    return key.size() < 33;
}

const Profile::URI & Profile::getURI() const
{
    return _uri;
}



std::string Profile::get(const std::string &key) const
{
    return call<std::string, String_Type>("get(bytes32)", CONTRACT_ARGUMENTS(ABI_FIXED(key)));
}


address_t Profile::getPaymentAddress() const
{
    return get("payments");
}

bool Profile::authenticate(const address_t &address, BitProfile::Auth::Permission permission)
{
    return call<bool, Bool_Type>("authenticate(address,bytes,uint8)", CONTRACT_ARGUMENTS(ABI_ADDRESS(address), "", permission));
}

address_t Profile::getAuth() const
{
    return call<std::string, Address_Type>("auth()");
}

bool Profile::checkKey(std::string key, std::string value)
{
    return get(key) == value;
}


bool Profile::checkOwner(address_t address)
{
    return getAuth() == address;
}

}
