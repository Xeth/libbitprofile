
namespace BitProfile{


template<class Key>
ProfileDescriptor::ProfileDescriptor(const Profile &profile, const Key &key)
{
    const Profile::URI & uri = profile.getURI();
    _data["uri"] = uri.toString();
    _data["name"] = uri.getName();
    _data["context"] = uri.getContext();
    _data["auth"] = parseKey(profile, key);
}


}
