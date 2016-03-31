namespace BitProfile{

template<class Callback>
void Registrar::create(const std::string &name, const std::string &authData, const Callback &callback)
{
    create(name, getSenderAddress(), authData, callback);
}

template<class Callback>
void Registrar::create(const std::string &name, const address_t &address, const std::string &authData, const Callback &callback)
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
            boost::bind(&Registrar::checkProfile, this, name, address.size()?address:getSenderAddress(), true),
            callback
        );
    }
}


template<class Callback>
void Registrar::link(const std::string &name, const address_t &address, const std::string &authData, const Callback &callback)
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
            CONTRACT_ARGUMENTS(ABI_FIXED(name), address, authData),
            boost::bind(&Registrar::checkProfile, this, name, address, true),
            callback
        );
    }
}


template<class Callback>
void Registrar::unlink(const std::string &name, const std::string &authData, const Callback &callback)
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
            boost::bind(&Registrar::checkProfile, this, name, getSenderAddress(), false),
            callback
        );
    }
}


}
