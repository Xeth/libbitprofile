#include "AddressAuth.hpp"


namespace BitProfile{


AddressAuth::AddressAuth(Provider &provider, const address_t &address) :
    Contract(provider, address)
{}


bool AddressAuth::set(const address_t &address, Auth::Permission permission)
{
    return executeConfirm
    (
        "set(address,uint8)", 
        CONTRACT_ARGUMENTS(address, permission), 
        boost::bind(&AddressAuth::checkAuth, this, address, Auth::Edit, true)
    );
}


bool AddressAuth::remove(const address_t &address)
{
    return executeConfirm
    (
        "remove(address)", 
        CONTRACT_ARGUMENTS(address), 
        boost::bind(&AddressAuth::checkAuth, this, address, Auth::Edit, false)
    );
}


bool AddressAuth::authenticate(const address_t &address, Auth::Permission permission)
{
    return call<bool>("authenticate(address,string,uint8)", CONTRACT_ARGUMENTS(address, "", permission));
}


bool AddressAuth::checkAuth(address_t address, Auth::Permission permission, bool active)
{
    return active==authenticate(address, permission);
}


}