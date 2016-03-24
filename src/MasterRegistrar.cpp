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


Registrar MasterRegistrar::get(size_t index)
{
    return Registrar(getProvider(), call<std::string>("get(uint)", CONTRACT_ARGUMENTS(index)));
}


size_t MasterRegistrar::getSize()
{
    return call<uint256_t>("size()").template convert_to<size_t>();
}


bool MasterRegistrar::isBeta()
{
    return call<bool>("beta()");
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
