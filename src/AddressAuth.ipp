namespace BitProfile{

template<class Permit>
bool AddressAuth::set(const address_t &address, BitProfile::Auth::Permission permission, const Permit &auth)
{
    return executeConfirm
    (
        "set(address,uint8)", 
        CONTRACT_ARGUMENTS(ABI_ADDRESS(address), permission), 
        auth,
        boost::bind(&AddressAuth::checkAuth, this, address, BitProfile::Auth::Edit, true)
    );
}


template<class Permit>
bool AddressAuth::remove(const address_t &address, const Permit &auth)
{
    return executeConfirm
    (
        "remove(address)", 
        CONTRACT_ARGUMENTS(ABI_ADDRESS(address)), 
        auth,
        boost::bind(&AddressAuth::checkAuth, this, address, BitProfile::Auth::Edit, false)
    );
}


template<class Permit, class Callback>
void AddressAuth::set(const address_t &address, BitProfile::Auth::Permission permission, const Permit &auth, const Callback &callback)
{
    return executeConfirm
    (
        "set(address,uint8)", 
        CONTRACT_ARGUMENTS(ABI_ADDRESS(address), permission), 
        auth,
        boost::bind(&AddressAuth::checkAuth, this, address, permission, true), 
        callback
    );
}


template<class Permit, class Callback>
void AddressAuth::remove(const address_t &address, const Permit &auth, const Callback &callback)
{
    return executeConfirm
    (
        "remove(address)", 
        CONTRACT_ARGUMENTS(ABI_ADDRESS(address)),
        auth,
        boost::bind(&AddressAuth::checkAuth, this, address, BitProfile::Auth::Edit, false),
        callback
    );
}


}
