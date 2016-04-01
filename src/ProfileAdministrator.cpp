#include "ProfileAdministrator.hpp"


namespace BitProfile{


ProfileAdministrator::ProfileAdministrator(const Profile &profile, const KeyAdapter &key):
    _profile(profile),
    _key(key)
{}


void ProfileAdministrator::setGasPrice(const BigInt &price)
{
    _profile.setGasPrice(price);
}

void ProfileAdministrator::setGasLimit(const BigInt &gas)
{
    _profile.setGasLimit(gas);
}

const KeyAdapter & ProfileAdministrator::getKey() const
{
    return _key;
}

bool ProfileAdministrator::set(const std::string &key, const std::string &value, const std::string &password)
{
    std::pair<bool, std::string> result = _key.authenticate(_profile.getProvider(), password);
    if(!result.first)
    {
        return false;
    }
    _profile.setSenderAddress(_key.getAddress());
    return _profile.set(key, value, result.second);
}


bool ProfileAdministrator::setPaymentAddress(const address_t &address, const std::string &password)
{
    return set("payments", address, password);
}


bool ProfileAdministrator::changeAuth(const AddressAuth &auth, const std::string &password)
{
    std::pair<bool, std::string> result = _key.authenticate(_profile.getProvider(), password);
    if(!result.first)
    {
        return false;
    }
    _profile.setSenderAddress(_key.getAddress());
    if(_profile.transfer(auth.getAddress(), result.second))
    {
        _key.reset(AddressAuthKey(auth.getSenderAddress()));
        return true;
    }
    return false;
}


bool ProfileAdministrator::link(Registrar &registrar, const std::string &name, const std::string &password)
{
    std::pair<bool, std::string> result = _key.authenticate(_profile.getProvider(), password);
    if(!result.first)
    {
        return false;
    }
    registrar.setSenderAddress(_key.getAddress());
    return registrar.link(name, _profile.getAddress(), result.second);
}


bool ProfileAdministrator::unlink(Registrar &registrar, const std::string &password)
{
    std::pair<bool, std::string> result = _key.authenticate(_profile.getProvider(), password);
    if(!result.first)
    {
        return false;
    }
    registrar.setSenderAddress(_key.getAddress());
    return registrar.unlink(_profile.getURI().getName(), result.second);
}


bool ProfileAdministrator::move(Registrar &registrar, const std::string &name, const std::string &password, const BigInt &gas)
{
    std::pair<bool, std::string> result = _key.authenticate(_profile.getProvider(), password);
    if(!result.first)
    {
        return false;
    }

    BigInt oldGas;

    if(gas > 0)
    {
        oldGas = registrar.getGasLimit();
        registrar.setGasLimit(gas);
    }

    Resolver resolver(_profile.getProvider());
    Registrar oldRegistrar = resolver.lookupRegistrar(_profile.getURI().getContext());
    std::string oldName = _profile.getURI().getName();

    registrar.setSenderAddress(_key.getAddress());

    if(!registrar.link(name, _profile.getAddress(), result.second))
    {
        return false;
    }


    if(gas > 0)
    {
        registrar.setGasLimit(oldGas);
        Ethereum::Connector::BlockChain blockchain(_profile.getProvider());
        Ethereum::Connector::Transaction tx = blockchain.getTransaction(registrar.getLastTransaction().c_str());
        BigInt unlinkGas = gas - tx.getGas();
        if(unlinkGas > 0)
        {
            oldRegistrar.setGasLimit(unlinkGas);
        }
    }

    oldRegistrar.setSenderAddress(_key.getAddress());

    return oldRegistrar.unlink(oldName, result.second);

}


const Profile & ProfileAdministrator::getProfile() const
{
    return _profile;
}

bool ProfileAdministrator::isNull() const
{
    return _profile.isNull();
}

ProfileAdministrator ProfileAdministrator::FromDescriptor(Provider &provider, const ProfileDescriptor &descriptor)
{
    return ProfileAdministrator(Profile(provider, descriptor.getAddress()), descriptor.getProfileKey());
}


ProfileAdministrator ProfileAdministrator::CreateProfile(Registrar &regisrar, const std::string &name, const address_t &address, const std::string &password)
{
    return CreateProfile(regisrar, name, AddressAuthKey(address), password);
}


ProfileAdministrator ProfileAdministrator::CreateProfile(Registrar &regisrar, const std::string &name, const std::string &password)
{
    return CreateProfile(regisrar, name, AddressAuthKey(regisrar.getSenderAddress()), password);
}

}
