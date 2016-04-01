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


bool Profile::set(const std::string &key, const std::string &value, const std::string &authData)
{
    if(!validateKey(key))
    {
        return false;
    }
    return executeConfirm
    (
        "set(bytes32,bytes,bytes)", 
        CONTRACT_ARGUMENTS(ABI_FIXED(key), value, authData),
        boost::bind(&Profile::checkKey, this, key, value)
    );
}

bool Profile::clear(const std::string &key, const std::string &authData)
{
    if(!validateKey(key))
    {
        return false;
    }
    return executeConfirm
    (
        "clear(bytes32,bytes)", 
        CONTRACT_ARGUMENTS(ABI_FIXED(key), authData),
        boost::bind(&Profile::checkKey, this, key, "")
    );
}

std::string Profile::get(const std::string &key) const
{
    return call<std::string, String_Type>("get(bytes32)", CONTRACT_ARGUMENTS(ABI_FIXED(key)));
}


address_t Profile::getPaymentAddress() const
{
    return get("payments");
}

bool Profile::setPaymentAddress(const address_t &address, const std::string &authData)
{
    return set("payments", address, authData);
}


txid_t Profile::setPermission(const std::string &key, Auth::Permission permission, const std::string &authData)
{
    if(!validateKey(key))
    {
        return "";
    }
    return execute("setPermission(bytes32,uint8,bytes)", CONTRACT_ARGUMENTS(ABI_FIXED(key), permission, authData));
}

bool Profile::authenticate(const address_t &address, Auth::Permission permission)
{
    return call<bool, Bool_Type>("authenticate(address,bytes,uint8)", CONTRACT_ARGUMENTS(ABI_ADDRESS(address), "", permission));
}

address_t Profile::getAuth() const
{
    return call<std::string, Address_Type>("auth()");
}

bool Profile::transfer(const address_t &address, const std::string &authData)
{
    return executeConfirm
    (
        "transfer(address,bytes)",
        CONTRACT_ARGUMENTS(ABI_ADDRESS(address), authData),
        boost::bind(&Profile::checkOwner, this, address)
    );
}

txid_t Profile::kill(const std::string &authData)
{
    return execute("kill(bytes)", CONTRACT_ARGUMENTS(authData));
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
