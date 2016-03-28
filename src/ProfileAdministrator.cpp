#include "ProfileAdministrator.hpp"


namespace BitProfile{


bool ProfileAdministrator::set(const std::string &key, const std::string &value, const std::string &password)
{
    std::pair<bool, std::string> result = _key.authenticate(_profile.getProvider(), password);
    if(!result.first)
    {
        return false;
    }
    return _profile.set(key, value, result.second);
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


const Profile & ProfileAdministrator::getProfile() const
{
    return _profile;
}

bool ProfileAdministrator::isNull() const
{
    return _profile.isNull();
}


}