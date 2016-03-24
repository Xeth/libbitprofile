#include "Profile.hpp"


namespace BitProfile{


Profile::Profile(Provider &provider, const address_t &address) :
    Contract(provider, address)
{}


txid_t Profile::set(const std::string &key, const std::string &value)
{
    return execute("set(string,string,string)", CONTRACT_ARGUMENTS(key, value, ""));
}

txid_t Profile::clear(const std::string &key)
{
    return execute("clear(string,string)", CONTRACT_ARGUMENTS(key, ""));
}

std::string Profile::get(const std::string &key)
{
    return call<std::string>("get(string)", CONTRACT_ARGUMENTS(key));
}


address_t Profile::getPaymentAddress()
{
    return get("payments");
}

void Profile::setPaymentAddress(const address_t &address)
{
    set("payments", address);
}


txid_t Profile::setPermission(const std::string &key, Auth::Permission permission)
{
    return execute("setPermission(string,uint8,string)", CONTRACT_ARGUMENTS(key, permission, ""));
}

bool Profile::authenticate(const address_t &address, Auth::Permission permission)
{
    return call<bool>("authenticate(address,uint8,string)", CONTRACT_ARGUMENTS(address, permission, ""));
}

address_t Profile::getAuth()
{
    return call<std::string>("auth()");
}

txid_t Profile::transfer(const address_t &address)
{
    return execute("transfer(address,string)", CONTRACT_ARGUMENTS(address, ""));
}

txid_t Profile::kill()
{
    return execute("kill(string)", CONTRACT_ARGUMENTS(""));
}

}
