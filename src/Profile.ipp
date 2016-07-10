namespace BitProfile{


template<class Permit, class Callback>
void Profile::set(const std::string &key, const std::string &value, const std::string &authData, const Permit &auth, const Callback &callback)
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
            auth,
            boost::bind(&Profile::checkKey, this, key, value),
            callback
        );
    }
}


template<class Permit, class Callback>
void Profile::clear(const std::string &key, const std::string &authData, const Permit &auth, const Callback &callback)
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
            auth,
            boost::bind(&Profile::checkKey, this, key, ""),
            callback
        );
    }
}


template<class Permit, class Callback>
void Profile::setPaymentAddress(const address_t &address, const std::string &authData, const Permit &auth, const Callback &callback)
{
    return set("payments", address, authData, auth, callback);
}


template<class Permit, class Callback>
void Profile::transfer(const address_t &address, const std::string &authData, const Permit &auth, const Callback &callback)
{
    return executeConfirm
    (
        "transfer(address,bytes)",
        CONTRACT_ARGUMENTS(address, authData),
        auth,
        boost::bind(&Profile::checkOwner, this, address),
        callback
    );
}


//

template<class Permit>
bool Profile::set(const std::string &key, const std::string &value, const std::string &authData, const Permit &auth)
{
    if(!validateKey(key))
    {
        return false;
    }
    return executeConfirm
    (
        "set(bytes32,bytes,bytes)", 
        CONTRACT_ARGUMENTS(ABI_FIXED(key), value, authData),
        auth,
        boost::bind(&Profile::checkKey, this, key, value)
    );
}

template<class Permit>
bool Profile::clear(const std::string &key, const std::string &authData, const Permit &auth)
{
    if(!validateKey(key))
    {
        return false;
    }
    return executeConfirm
    (
        "clear(bytes32,bytes)", 
        CONTRACT_ARGUMENTS(ABI_FIXED(key), authData),
        auth,
        boost::bind(&Profile::checkKey, this, key, "")
    );
}

template<class Permit>
bool Profile::setPaymentAddress(const address_t &address, const std::string &authData, const Permit &auth)
{
    return set("payments", address, authData, auth);
}


template<class Permit>
txid_t Profile::setPermission(const std::string &key, BitProfile::Auth::Permission permission, const std::string &authData, const Permit &auth)
{
    if(!validateKey(key))
    {
        return "";
    }
    return execute("setPermission(bytes32,uint8,bytes)", CONTRACT_ARGUMENTS(ABI_FIXED(key), permission, authData), auth);
}


template<class Permit>
bool Profile::transfer(const address_t &address, const std::string &authData, const Permit &auth)
{
    return executeConfirm
    (
        "transfer(address,bytes)",
        CONTRACT_ARGUMENTS(ABI_ADDRESS(address), authData),
        auth,
        boost::bind(&Profile::checkOwner, this, address)
    );
}


template<class Permit>
txid_t Profile::kill(const std::string &authData, const Permit &auth)
{
    return execute("kill(bytes)", CONTRACT_ARGUMENTS(authData), auth);
}




}
