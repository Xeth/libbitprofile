#include "ProfileAdministrator.hpp"


namespace BitProfile{


ProfileAdministrator::ProfileAdministrator(const Profile &profile, const KeyAdapter &key):
    _profile(profile),
    _key(key)
{}


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
    return _profile.set(key, value, result.second);
}


bool ProfileAdministrator::setPaymentAddress(const address_t &address, const std::string &password)
{
    std::pair<bool, std::string> result = _key.authenticate(_profile.getProvider(), password);
    if(!result.first)
    {
        return false;
    }
    return _profile.setPaymentAddress(address, result.second);
}


bool ProfileAdministrator::changeAuth(const AddressAuth &auth, const std::string &password)
{
    std::pair<bool, std::string> result = _key.authenticate(_profile.getProvider(), password);
    if(!result.first)
    {
        return false;
    }
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
    return registrar.link(name, _profile.getAddress(), result.second);
}


bool ProfileAdministrator::unlink(Registrar &registrar, const std::string &password)
{
    std::pair<bool, std::string> result = _key.authenticate(_profile.getProvider(), password);
    if(!result.first)
    {
        return false;
    }
    return registrar.unlink(_profile.getAddress(), result.second);
}


bool ProfileAdministrator::rename(Registrar &registrar, const std::string &name, const std::string &password)
{
    std::pair<bool, std::string> result = _key.authenticate(_profile.getProvider(), password);
    if(!result.first)
    {
        return false;
    }
    if(!registrar.unlink(_profile.getAddress(), result.second))
    {
        return false;
    }
    return registrar.link(name, _profile.getAddress(), result.second);
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
