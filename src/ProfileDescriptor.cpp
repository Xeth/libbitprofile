#include "ProfileDescriptor.hpp"


namespace BitProfile{


ProfileDescriptor::ProfileDescriptor(const Json::Value &value) :
    _data(value)
{}


Json::Value ProfileDescriptor::serializeKey(const Profile &profile, const AddressAuthKey &key)
{
    Json::Value data;
    data["type"] = "address";
    data["address"] = key.getAddress();
    data["contract"] = profile.getAuth();
    data["secret"] = "";
    return data;
}

KeyAdapter ProfileDescriptor::getProfileKey() const
{
    const Json::Value & authData = _data["auth"];
    if(authData["type"].asString()!="address")
    {
        throw std::runtime_error("key type not implemented");
    }

    return KeyAdapter(AddressAuthKey(authData["address"].asString()));

}

const Json::Value & ProfileDescriptor::toJSON() const
{
    return _data;
}

std::string ProfileDescriptor::getURI() const
{
    return _data["uri"].asString();
}


std::string ProfileDescriptor::getName() const
{
    return _data["name"].asString();
}


std::string ProfileDescriptor::getContext() const
{
    return _data["context"].asString();
}


std::string ProfileDescriptor::getAuthType() const
{
    return _data["auth"]["type"].asString();
}


std::string ProfileDescriptor::getAuthAddress() const
{
    return _data["auth"]["address"].asString();
}


}


std::ostream & operator << (std::ostream &os, const BitProfile::ProfileDescriptor &descriptor)
{
    Json::FastWriter parser;
    os << parser.write(descriptor.toJSON());
    return os;
}


