#include "MasterRegistrar.hpp"


namespace BitProfile{


MasterRegistrar::MasterRegistrar(Provider &provider) : 
    Contract(provider, DEFAULT_MASTER_REGISTRAR)
{}


MasterRegistrar::MasterRegistrar(Provider &provider, Network net) :
    Contract(provider, (net==Main_Net) ? DEFAULT_MASTER_REGISTRAR : DEFAULT_TESTNET_MASTER_REGISTRAR)
{}


MasterRegistrar::MasterRegistrar(Provider &provider, const address_t &address) :
    Contract(provider, address)
{}


MasterRegistrar::URIList MasterRegistrar::getURIList()
{
    return URIList(getSize());
}


Registrar MasterRegistrar::get(size_t index)
{
    return Registrar(getProvider(), call<address_t, Address_Type>("get(uint256)", CONTRACT_ARGUMENTS(uint256_t(index))), RegistrarURI(index));
}


size_t MasterRegistrar::getSize()
{
    return call<uint256_t, Uint_Type>("size()").template convert_to<size_t>();
}


bool MasterRegistrar::isBeta()
{
    return call<bool, Bool_Type>("beta()");
}


bool MasterRegistrar::create()
{
    return executeConfirm
    (
        "create()",
        boost::bind(&MasterRegistrar::checkRegistrar, this, getSize())
    );
}


bool MasterRegistrar::checkRegistrar(size_t index)
{
    return getSize()>=index;
}


}
