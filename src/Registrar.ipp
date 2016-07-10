namespace BitProfile{

template<class Permit, class Callback>
void Registrar::create(const std::string &name, const std::string &authData, const Permit &auth, const Callback &callback)
{
    if(!validateName(name))
    {
        callback(false);
    }
    else
    {
        if(contains(name))
        {
            callback(false);
        }
        else
        {
            executeConfirm
            (
                "register(bytes32,bytes)",
                CONTRACT_ARGUMENTS(ABI_FIXED(name), authData),
                auth,
                boost::bind(&Registrar::checkProfile, this, name, getSenderAddress(), true),
                callback
            );
        }
    }
}


template<class Permit, class Callback>
void Registrar::link(const std::string &name, const address_t &address, const std::string &authData, const Permit &auth, const Callback &callback)
{
    if(!validateName(name))
    {
        callback(false);
    }
    else
    {
        if(contains(name))
        {
            callback(false);
        }
        else
        {
            return executeConfirm
            (
                "link(bytes32,address,bytes)",
                CONTRACT_ARGUMENTS(ABI_FIXED(name), ABI_ADDRESS(address), authData),
                auth,
                boost::bind(&Registrar::checkProfile, this, name, getSenderAddress(), true),
                callback
            );
        }
    }
}


template<class Permit, class Callback>
void Registrar::unlink(const std::string &name, const std::string &authData, const Permit &auth, const Callback &callback)
{
    if(!contains(name))
    {
        callback(true);
    }
    else
    {
        return executeConfirm
        (
            "unlink(bytes32,bytes)",
            CONTRACT_ARGUMENTS(ABI_FIXED(name), authData),
            auth,
            boost::bind(&Registrar::checkProfile, this, name, getSenderAddress(), false),
            callback
        );
    }
}

template<class Permit>
bool Registrar::create(const std::string &name, const std::string &authData, const Permit &auth)
{
    if(!validateName(name))
    {
        return false;
    }

    if(contains(name))
    {
        return false;
    }

    return executeConfirm
    (
        "register(bytes32,bytes)",
        CONTRACT_ARGUMENTS(ABI_FIXED(name), authData),
        auth,
        boost::bind(&Registrar::checkProfile, this, name, getSenderAddress(), true)
    );
}



template<class Permit>
bool Registrar::link(const std::string &name, const address_t &address, const std::string &authData, const Permit &auth)
{
    if(!validateName(name))
    {
        return false;
    }

    if(contains(name))
    {
        return false;
    }

    return executeConfirm
    (
        "link(bytes32,address,bytes)",
        CONTRACT_ARGUMENTS(ABI_FIXED(name), ABI_ADDRESS(address), authData),
        auth,
        boost::bind(&Registrar::checkProfile, this, name, getSenderAddress(), true)
    );
}


template<class Permit>
bool Registrar::unlink(const std::string &name, const std::string &authData, const Permit &auth)
{
    if(!contains(name))
    {
        return true;
    }
    return executeConfirm
    (
        "unlink(bytes32,bytes)",
        CONTRACT_ARGUMENTS(ABI_FIXED(name), authData),
        auth,
        boost::bind(&Registrar::checkProfile, this, name, getSenderAddress(), false)
    );
}


}
