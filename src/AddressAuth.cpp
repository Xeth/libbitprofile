#include "AddressAuth.hpp"


namespace BitProfile{


AddressAuth::AddressAuth(Provider &provider, const address_t &address) :
    Contract(provider, address)
{}


txid_t AddressAuth::set(const address_t &address, Auth::Permission permission)
{
    return execute("set(address,uint8)", CONTRACT_ARGUMENTS(address, permission));
}


txid_t AddressAuth::remove(const address_t &address)
{
    return execute("remove(address)", CONTRACT_ARGUMENTS(address));
}


bool AddressAuth::authenticate(const address_t &address, Auth::Permission permission)
{
    return call<bool>("authenticate(address,string,uint8)", CONTRACT_ARGUMENTS(address, "", permission));
}


}
