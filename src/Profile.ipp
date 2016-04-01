namespace BitProfile{


template<class Callback>
void Profile::set(const std::string &key, const std::string &value, const std::string &authData, const Callback &callback)
{
    if(!validateKey(key))
    {
        callback(false);
    }
    else
    {
        return executeConfirm
        (
            "set(bytes32,bytes,bytes)", 
            CONTRACT_ARGUMENTS(ABI_FIXED(key), value, authData),
            boost::bind(&Profile::checkKey, this, key, value),
            callback
        );
    }
}


template<class Callback>
void Profile::clear(const std::string &key, const std::string &authData, const Callback &callback)
{
    if(!validateKey(key))
    {
        callback(false);
    }
    else
    {
        return executeConfirm
        (
            "clear(bytes32,bytes)", 
            CONTRACT_ARGUMENTS(ABI_FIXED(key), authData),
            boost::bind(&Profile::checkKey, this, key, ""),
            callback
        );
    }
}


template<class Callback>
void Profile::setPaymentAddress(const address_t &address, const std::string &authData, const Callback &callback)
{
    return set("payments", address, authData, callback);
}


template<class Callback>
void Profile::transfer(const address_t &address, const std::string &authData, const Callback &callback)
{
    return executeConfirm
    (
        "transfer(address,bytes)",
        CONTRACT_ARGUMENTS(address, authData),
        boost::bind(&Profile::checkOwner, this, address),
        callback
    );
}


}
