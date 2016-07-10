namespace BitProfile{

template<class Permit>
bool MasterRegistrar::create(const Permit &auth)
{
    return executeConfirm
    (
        "create()",
        auth,
        boost::bind(&MasterRegistrar::checkRegistrar, this, getSize())
    );
}

template<class Permit, class Callback>
void MasterRegistrar::create(const Permit &auth, const Callback &callback)
{
    executeConfirm
    (
        "create()",
        auth,
        boost::bind(&MasterRegistrar::checkRegistrar, this, getSize()),
        callback
    );
}



}
