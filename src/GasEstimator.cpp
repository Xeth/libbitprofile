#include "GasEstimator.hpp"


namespace BitProfile{


GasEstimator::GasEstimator(Ethereum::Connector::Provider &provider, Network net) :
    _estimator(provider),
    _network(net)
{}


GasEstimator::BigInt GasEstimator::estimateRegister(const std::string &name)
{
    if(_network==Main_Net)
    {
        return estimateRegister(name, DEFAULT_PROFILE_REGISTRAR, DEFAULT_PROFILE_FACTORY);
    }
    return estimateRegister(name, DEFAULT_TESTNET_PROFILE_REGISTRAR, DEFAULT_TESTNET_PROFILE_FACTORY);
}


GasEstimator::BigInt GasEstimator::estimateRegister(const std::string &name, const char *registrarAddress, const char *factoryAddress)
{
    BigInt gas = _estimator.estimate(DUMMY_ADDRESS, registrarAddress, BigInt(0), Method::Encode("register(string,string)", CONTRACT_ARGUMENTS(name, "")));
    gas += _estimator.estimate(DUMMY_ADDRESS, DUMMY_ADDRESS, BigInt(0), ContractConstructor::Encode(ContractCode::Profile, CONTRACT_ARGUMENTS(ABI_ADDRESS(DUMMY_ADDRESS))));
    gas += _estimator.estimate(DUMMY_ADDRESS, DUMMY_ADDRESS, BigInt(0), ContractConstructor::Encode(ContractCode::AddressAuth, CONTRACT_ARGUMENTS(ABI_ADDRESS(DUMMY_ADDRESS))));
    gas += _estimator.estimate(DUMMY_ADDRESS, factoryAddress, BigInt(0), Method::Encode("create(address,string)", CONTRACT_ARGUMENTS(ABI_ADDRESS(DUMMY_ADDRESS), "")));
    return gas;
}


GasEstimator::BigInt GasEstimator::estimateLink(const std::string &name, const address_t &address)
{
    return estimateLink(name, address, _network==Main_Net? DEFAULT_PROFILE_REGISTRAR : DEFAULT_TESTNET_PROFILE_REGISTRAR);
}

GasEstimator::BigInt GasEstimator::estimateLink(const std::string &name, const address_t &address, const char *registrarAddress)
{
    return _estimator.estimate(DUMMY_ADDRESS, registrarAddress, BigInt(0), Method::Encode("link(string,address,string)", CONTRACT_ARGUMENTS(name, ABI_ADDRESS(address), "")));
}


GasEstimator::BigInt GasEstimator::estimateUnlink(const std::string &name)
{
    return estimateUnlink(name, _network==Main_Net?DEFAULT_PROFILE_REGISTRAR:DEFAULT_TESTNET_PROFILE_REGISTRAR);
}

GasEstimator::BigInt GasEstimator::estimateUnlink(const std::string &name, const char *registrarAddress)
{
    return _estimator.estimate(DUMMY_ADDRESS, registrarAddress, BigInt(0), Method::Encode("unlink(string,string)", CONTRACT_ARGUMENTS(name,"")));
}

GasEstimator::BigInt GasEstimator::estimateEdit(const std::string &name, const std::string &value)
{
    return estimateEdit(name, value, _network==Main_Net? DEFAULT_PROFILE : DEFAULT_TESTNET_PROFILE);
}

GasEstimator::BigInt GasEstimator::estimateEdit(const std::string &name, const std::string &value, const char *address)
{
    return _estimator.estimate(DUMMY_ADDRESS, address, BigInt(0), Method::Encode("set(string,string,string)", CONTRACT_ARGUMENTS(name,value,"")));
}

}
