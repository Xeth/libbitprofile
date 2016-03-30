#include "ProfileDescriptor.hpp"
#include "ProfileAdministrator.hpp"

namespace BitProfile{


ProfileDescriptor::ProfileDescriptor()
{}


ProfileDescriptor::ProfileDescriptor(const Json::Value &value) :
    _data(value)
{}


ProfileDescriptor::ProfileDescriptor(const ProfileAdministrator &admin)
{
    parseProfileData(admin.getProfile());
    parseKeyData(admin.getProfile(), admin.getKey(), admin.getKey().getTypeName());
}

void ProfileDescriptor::parseProfileData(const Profile &profile)
{
    setURI(profile.getURI());
    _data["contract"] = profile.getAddress();
}


void ProfileDescriptor::setURI(const Profile::URI &uri)
{
    _data["uri"] = uri.toString();
    _data["name"] = uri.getName();
    _data["context"] = uri.getContext();
}

void ProfileDescriptor::parseKeyData(const Profile &profile, const AddressAuthKey &key)
{
    parseKeyData(profile, key, KeyTypeName<AddressAuthKey>());
}


template<class Key>
void ProfileDescriptor::parseKeyData(const Profile &profile, const Key &key, const std::string &keyType)
{
    Json::Value data;
    data["type"] = keyType;
    data["address"] = key.getAddress();
    data["contract"] = profile.getAuth();
    _data["auth"] = data;
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

address_t ProfileDescriptor::getAddress() const
{
    return _data["contract"].asString();
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


void ProfileDescriptor::reset(const Json::Value &data)
{
    _data = data;
}


}


std::ostream & operator << (std::ostream &os, const BitProfile::ProfileDescriptor &descriptor)
{
    Json::FastWriter parser;
    os << parser.write(descriptor.toJSON());
    return os;
}

std::istream & operator >> (std::istream &stream, BitProfile::ProfileDescriptor &descriptor)
{
    Json::Value data;
    Json::Reader reader;
    std::string content;
    stream.seekg(0, std::ios::end);
    content.resize(stream.tellg());
    stream.seekg(0, std::ios::beg);
    stream.read(&content[0], content.size());
    if(!reader.parse(content, data, false))
    {
        throw std::runtime_error("invalid file format");
    }
    descriptor.reset(data);
    return stream;
}


