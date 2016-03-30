#include "GasEstimator.hpp"


namespace BitProfile{


GasEstimator::GasEstimator(Ethereum::Connector::Provider &provider) :
    _estimator(provider)
{}


GasEstimator::BigInt GasEstimator::estimateRegister(const Registrar &registrar, const std::string &name)
{
    return estimateRegister(name, registrar.getAddress().c_str(), registrar.getProfileFactory().c_str(), DUMMY_ADDRESS);
}


GasEstimator::BigInt GasEstimator::estimateRegister(const std::string &name, const char *registrarAddress, const char *factoryAddress, const char *sender)
{
    BigInt gas = _estimator.estimate(sender, registrarAddress, BigInt(0), Method::Encode("register(string,string)", CONTRACT_ARGUMENTS(name, "")));
    gas += _estimator.estimate(sender, DUMMY_ADDRESS, BigInt(0), ContractConstructor::Encode(ContractCode::Profile, CONTRACT_ARGUMENTS(ABI_ADDRESS(DUMMY_ADDRESS))));
    gas += _estimator.estimate(sender, DUMMY_ADDRESS, BigInt(0), ContractConstructor::Encode(ContractCode::AddressAuth, CONTRACT_ARGUMENTS(ABI_ADDRESS(DUMMY_ADDRESS))));
    gas += _estimator.estimate(sender, factoryAddress, BigInt(0), Method::Encode("create(address,string)", CONTRACT_ARGUMENTS(ABI_ADDRESS(DUMMY_ADDRESS), "")));
    return gas;
}


GasEstimator::BigInt GasEstimator::estimateLink(const Registrar &registrar, const ProfileAdministrator &admin, const std::string &name)
{
    return estimateLink(name, admin.getProfile().getAddress(), registrar.getAddress().c_str(), admin.getKey().getAddress().c_str());
}

GasEstimator::BigInt GasEstimator::estimateLink(const std::string &name, const address_t &address, const char *registrarAddress, const char *sender)
{
    return _estimator.estimate(sender, registrarAddress, BigInt(0), Method::Encode("link(string,address,string)", CONTRACT_ARGUMENTS(name, ABI_ADDRESS(address), "")));
}


GasEstimator::BigInt GasEstimator::estimateUnlink(const Registrar &registrar, const ProfileAdministrator &admin)
{
    return estimateUnlink(admin.getProfile().getURI().getName(), registrar.getAddress().c_str(), admin.getKey().getAddress().c_str());
}

GasEstimator::BigInt GasEstimator::estimateUnlink(const std::string &name, const char *registrarAddress, const char *sender)
{
    return _estimator.estimate(sender, registrarAddress, BigInt(0), Method::Encode("unlink(string,string)", CONTRACT_ARGUMENTS(name,"")));
}

GasEstimator::BigInt GasEstimator::estimateEdit(const ProfileAdministrator &admin, const std::string &name, const std::string &value)
{
    return estimateEdit(name, value, admin.getProfile().getAddress().c_str(), admin.getKey().getAddress().c_str());
}

GasEstimator::BigInt GasEstimator::estimateEdit(const std::string &name, const std::string &value, const char *address, const char *sender)
{
    return _estimator.estimate(sender, address, BigInt(0), Method::Encode("set(string,string,string)", CONTRACT_ARGUMENTS(name,value,"")));
}

}
