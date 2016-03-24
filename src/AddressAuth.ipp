namespace BitProfile{


template<class Callback>
void AddressAuth::set(const address_t &address, Auth::Permission permission, const Callback &callback)
{
    return executeConfirm
    (
        "set(address,uint8)", 
        CONTRACT_ARGUMENTS(address, permission), 
        boost::bind(&AddressAuth::checkAuth, this, address, permission, true), 
        callback
    );
}


template<class Callback>
void AddressAuth::remove(const address_t &address, const Callback &callback)
{
    return executeConfirm
    (
        "remove(address)", 
        CONTRACT_ARGUMENTS(address),
        boost::bind(&AddressAuth::checkAuth, this, address, Auth::Edit, false),
        callback
    );
}

}
