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
    return ProfileAdministrator(Profile(provider, descriptor.getAddress(), ProfileURI(descriptor.getContext(), descriptor.getName())), descriptor.getProfileKey());
}




}
