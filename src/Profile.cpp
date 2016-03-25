#include "Profile.hpp"


namespace BitProfile{


Profile::Profile(Provider &provider, const address_t &address) :
    Contract(provider, address)
{}


bool Profile::set(const std::string &key, const std::string &value)
{
    return executeConfirm
    (
        "set(string,string,string)", 
        CONTRACT_ARGUMENTS(key, value, ""),
        boost::bind(&Profile::checkKey, this, key, value)
    );
}

bool Profile::clear(const std::string &key)
{
    return executeConfirm
    (
        "clear(string,string)", 
        CONTRACT_ARGUMENTS(key, ""),
        boost::bind(&Profile::checkKey, this, key, "")
    );
}

std::string Profile::get(const std::string &key)
{
    return call<std::string, String_Type>("get(string)", CONTRACT_ARGUMENTS(key));
}


address_t Profile::getPaymentAddress()
{
    return get("payments");
}

bool Profile::setPaymentAddress(const address_t &address)
{
    return set("payments", address);
}


txid_t Profile::setPermission(const std::string &key, Auth::Permission permission)
{
    return execute("setPermission(string,uint8,string)", CONTRACT_ARGUMENTS(key, permission, ""));
}

bool Profile::authenticate(const address_t &address, Auth::Permission permission)
{
    return call<bool, Bool_Type>("authenticate(address,string,uint8)", CONTRACT_ARGUMENTS(ABI_ADDRESS(address), "", permission));
}

address_t Profile::getAuth()
{
    return call<std::string, Address_Type>("auth()");
}

bool Profile::transfer(const address_t &address)
{
    return executeConfirm
    (
        "transfer(address,string)",
        CONTRACT_ARGUMENTS(ABI_ADDRESS(address), ""),
        boost::bind(&Profile::checkOwner, this, address)
    );
}

txid_t Profile::kill()
{
    return execute("kill(string)", CONTRACT_ARGUMENTS(""));
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
