namespace BitProfile{


template<class Callback>
void MasterRegistrar::create(const Callback &callback)
{
    executeConfirm
    (
        "create()",
        boost::bind(&MasterRegistrar::checkRegistrar, this, getSize()),
        callback
    );
}


}
