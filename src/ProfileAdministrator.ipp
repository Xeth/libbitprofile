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


template<class Callback, class Key>
class ProfileAdministrator::CreateProfileCallback
{
    public:
        CreateProfileCallback(Registrar &, const std::string &name, const Key &, const Callback &);
        void operator()(bool);

    private:
        Registrar &_registrar;
        std::string _name;
        Key _key;
        Callback _callback;
};


template<class Callback>
class ProfileAdministrator::RenameProfileCallback
{
    public:
        RenameProfileCallback(Registrar &, ProfileAdministrator *, const std::string &name, const std::string &password, const Callback &);

        void operator()(bool);

    private:
        Registrar &_registrar;
        ProfileAdministrator *_admin;
        std::string _name;
        std::string _password;
        Callback _callback;
};

template<class Key>
ProfileAdministrator::ProfileAdministrator(const Profile &profile, const Key &key) : 
    _profile(profile),
    _key(key)
{}


template<class Callback>
void ProfileAdministrator::CreateProfile(Registrar &registrar, const std::string &name, const std::string &password, const Callback &callback)
{
    CreateProfile(registrar, name, AddressAuthKey(registrar.getSenderAddress()), password, callback);
}

template<class Callback>
void ProfileAdministrator::CreateProfile(Registrar &registrar, const std::string &name, const address_t &address, const std::string &password, const Callback &callback)
{
    CreateProfile(registrar, name, AddressAuthKey(address), password, callback);
}

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
        _profile.setSenderAddress(_key.getAddress());
        _profile.set(key, value, result.second, callback);
    }
}

template<class Callback>
void ProfileAdministrator::setPaymentAddress(const address_t &address, const std::string &password, const Callback &callback)
{
    std::pair<bool, std::string> result = _key.authenticate(_profile.getProvider(), password);
    if(!result.first)
    {
        callback(false);
    }
    else
    {
        _profile.setSenderAddress(_key.getAddress());
        _profile.setPaymentAddress(address, callback);
    }
}


template<class Key>
ProfileAdministrator ProfileAdministrator::CreateProfile(Registrar &registrar, const std::string &name, const Key &key, const std::string &password)
{
    registrar.setSenderAddress(key.getAddress());
    if(registrar.create(name, key.authenticate(registrar.getProvider(), password).second))
    {
        return ProfileAdministrator(registrar.get(name), key);
    }
    return ProfileAdministrator(Profile(registrar.getProvider(), ""), key);
}


template<class Key, class Callback>
void ProfileAdministrator::CreateProfile(Registrar &registrar, const std::string &name, const Key &key, const std::string &password, const Callback &callback)
{
    registrar.setSenderAddress(key.getAddress());
    registrar.create(name, key.authenticate(registrar.getProvider(), password), CreateProfileCallback<Key, Callback>(registrar, name, key, callback));
}


template<class Callback>
void ProfileAdministrator::changeAuth(const AddressAuth &auth, const std::string &password, const Callback &callback)
{
    std::pair<bool, std::string> result = _key.authenticate(_profile.getProvider(), password);
    if(!result.first)
    {
        callback(false);
    }
    else
    {
        _profile.setSenderAddress(_key.getAddress());
        _profile.transfer(auth.getAddress(), result.second, ChangeAuthCallback<Callback, AddressAuthKey>(this, AddressAuthKey(auth.getSenderAddress()), callback));
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
        _admin->_key.reset(_key);
        _callback(true);
    }
    else
    {
        _callback(false);
    }
}


template<class Callback>
ProfileAdministrator::RenameProfileCallback<Callback>::RenameProfileCallback(Registrar &registrar, ProfileAdministrator *admin, const std::string &name, const std::string &password, const Callback &callback) :
    _registrar(registrar),
    _admin(admin),
    _name(name),
    _password(password),
    _callback(callback)
{}

template<class Callback>
void ProfileAdministrator::RenameProfileCallback<Callback>::operator()(bool result)
{
    if(!result)
    {
        _callback(false);
    }
    else
    {
        std::pair<bool, std::string> result = _admin->_key.authenticate(_admin->_profile.getProvider(), _password);
        if(!result.first)
        {
            _callback(false);
        }
        else
        {
            _registrar.link(_name, _admin->_profile.getAddress(), result.second, _callback);
        }
    }
}


template<class Callback, class Key>
ProfileAdministrator::CreateProfileCallback<Callback, Key>::CreateProfileCallback(Registrar &registrar, const std::string &name, const Key &key, const Callback &callback) :
    _registrar(registrar),
    _name(name),
    _key(key),
    _callback(callback)
{}


template<class Callback, class Key>
void ProfileAdministrator::CreateProfileCallback<Callback, Key>::operator()(bool result)
{
    //return null profile if registration failed
    _callback(ProfileAdministrator(result? _registrar.get(_name): Profile(_registrar.getProvider(), ""), _key));
}

}
