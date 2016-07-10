#include "AddressAuth.hpp"


namespace BitProfile{


AddressAuth::AddressAuth(Provider &provider, const address_t &address) :
    Contract(provider, address)
{}


bool AddressAuth::authenticate(const address_t &address, BitProfile::Auth::Permission permission)
{
    return call<bool, Bool_Type>("authenticate(address,bytes,uint8)", CONTRACT_ARGUMENTS(ABI_ADDRESS(address), "", permission));
}


bool AddressAuth::checkAuth(address_t address, BitProfile::Auth::Permission permission, bool active)
{
    return active==authenticate(address, permission);
}


}
