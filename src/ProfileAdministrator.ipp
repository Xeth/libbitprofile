namespace BitProfile{


template<class Callback, class Key>
class ProfileAdministrator::ChangeAuthCallback
{
    public:
        ChangeAuthCallback(ProfileAdministrator *, const Key &, const Callback &);
        void operator()(bool);

    private:
        ProfileAdministrator *_admin;
        Key _key;
        Callback _callback;
};


template<class Key>
ProfileAdministrator::ProfileAdministrator(const Profile &profile, const Key &key) : 
    _profile(profile),
    _key(key)
{}




template<class Callback>
void ProfileAdministrator::set(const std::string &key, const std::string &value, const std::string &password, const Callback &callback)
{
    std::pair<bool, std::string> result = _key.authenticate(_profile.getProvider(), password);
    if(!result.first)
    {
        callback(false);
    }
    else
    {
        set(key, value, result.second, callback);
    }
}



template<class Callback>
void ProfileAdministrator::changeAuth(const AddressAuth &, const std::string &password, const Callback &callback)
{
    std::pair<bool, std::string> result = _key.authenticate(_profile.getProvider(), password);
    if(!result.first)
    {
        callback(false);
    }
    else
    {
        _profile.transfer(auth.getAddress(), result.second, ChangeAuthCallback(this, AddressAuthKey(auth.getSenderAddress()), callback));
    }

}


template<class Callback, class Key>
ProfileAdministrator::ChangeAuthCallback<Callback, Key>::ChangeAuthCallback(ProfileAdministrator *admin, const Key &key, const Callback &callback) :
    _admin(admin),
    _key(key),
    _callback(callback)
{}


template<class Callback, class Key>
void ProfileAdministrator::ChangeAuthCallback<Callback, Key>::operator()(bool result)
{
    if(result)
    {
        _admin->key.reset(_key);
        _callback(true);
    }
    else
    {
        _callback(false);
    }
}



}
