namespace BitProfile{


template<class Callback>
void Registrar::create(const std::string &name, const std::string &authData, const Callback &callback)
{
    if(contains(name))
    {
        callback(false);
    }
    else
    {
        executeConfirm
        (
            "register(string,string)",
            CONTRACT_ARGUMENTS(name, authData),
            boost::bind(&Registrar::checkProfile, this, name, getSenderAddress(), true),
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
            "link(string,address,string)",
            CONTRACT_ARGUMENTS(name, address, authData),
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
            "unlink(string,string)",
            CONTRACT_ARGUMENTS(name, authData),
            boost::bind(&Registrar::checkProfile, this, name, getSenderAddress(), false),
            callback
        );
    }
}


}
