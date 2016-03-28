
namespace BitProfile{


template<class Key>
ProfileDescriptor::ProfileDescriptor(const Profile &profile, const Key &key)
{
    parseProfileData(profile);
    parseKeyData(key);
}


}
