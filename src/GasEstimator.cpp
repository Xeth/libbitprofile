#include "GasEstimator.hpp"


namespace BitProfile{


GasEstimator::GasEstimator(Ethereum::Connector::Provider &provider) :
    _estimator(provider)
{}


BigInt GasEstimator::estimateRegister(const Registrar &registrar, const std::string &name)
{
    return estimateRegister(name, registrar.getAddress().c_str(), registrar.getProfileFactory().c_str(), DUMMY_ADDRESS);
}


BigInt GasEstimator::estimateRegister(const std::string &name, const char *registrarAddress, const char *factoryAddress, const char *sender)
{
    BigInt gas = _estimator.estimate(sender, registrarAddress, BigInt(0), Method::Encode("register(bytes32,bytes)", CONTRACT_ARGUMENTS(ABI_FIXED(name), "")));
    gas += _estimator.estimate(sender, DUMMY_ADDRESS, BigInt(0), ContractConstructor::Encode(ContractCode::Profile, CONTRACT_ARGUMENTS(ABI_ADDRESS(DUMMY_ADDRESS))));
    gas += _estimator.estimate(sender, DUMMY_ADDRESS, BigInt(0), ContractConstructor::Encode(ContractCode::AddressAuth, CONTRACT_ARGUMENTS(ABI_ADDRESS(DUMMY_ADDRESS))));
    gas += _estimator.estimate(sender, factoryAddress, BigInt(0), Method::Encode("create(address,bytes)", CONTRACT_ARGUMENTS(ABI_ADDRESS(DUMMY_ADDRESS), "")));
    return gas;
}


BigInt GasEstimator::estimateLink(const Registrar &registrar, const ProfileAdministrator &admin, const std::string &name)
{
    return estimateLink(name, admin.getProfile().getAddress(), registrar.getAddress().c_str(), admin.getKey().getAddress().c_str());
}

BigInt GasEstimator::estimateLink(const std::string &name, const address_t &address, const char *registrarAddress, const char *sender)
{
    return _estimator.estimate(sender, registrarAddress, BigInt(0), Method::Encode("link(bytes32,address,bytes)", CONTRACT_ARGUMENTS(ABI_FIXED(name), ABI_ADDRESS(address), "")));
}


BigInt GasEstimator::estimateUnlink(const Registrar &registrar, const ProfileAdministrator &admin)
{
    return estimateUnlink(admin.getProfile().getURI().getName(), registrar.getAddress().c_str(), admin.getKey().getAddress().c_str());
}

BigInt GasEstimator::estimateUnlink(const std::string &name, const char *registrarAddress, const char *sender)
{
    return _estimator.estimate(sender, registrarAddress, BigInt(0), Method::Encode("unlink(bytes32,bytes)", CONTRACT_ARGUMENTS(ABI_FIXED(name),"")));
}

BigInt GasEstimator::estimateEdit(const ProfileAdministrator &admin, const std::string &name, const std::string &value)
{
    return estimateEdit(name, value, admin.getProfile().getAddress().c_str(), admin.getKey().getAddress().c_str());
}

BigInt GasEstimator::estimateEdit(const std::string &name, const std::string &value, const char *address, const char *sender)
{
    return _estimator.estimate(sender, address, BigInt(0), Method::Encode("set(bytes32,bytes,bytes)", CONTRACT_ARGUMENTS(ABI_FIXED(name),value,"")));
}

}
