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


template<class Permit, class Callback>
class ProfileAdministrator::RenameProfileCallback
{
    public:
        RenameProfileCallback(Registrar &, ProfileAdministrator *, const std::string &name, const Permit &auth, const Callback &);

        void operator()(bool);

    private:
        Registrar &_registrar;
        ProfileAdministrator *_admin;
        std::string _name;
        Permit _auth;
        Callback _callback;
};

template<class Key>
ProfileAdministrator::ProfileAdministrator(const Profile &profile, const Key &key) : 
    _profile(profile),
    _key(key)
{}


template<class Permit, class Callback>
void ProfileAdministrator::CreateProfileAsync(Registrar &registrar, const std::string &name, const Permit &auth, const Callback &callback)
{
    CreateProfileAsync(registrar, name, AddressAuthKey(registrar.getSenderAddress()), auth, callback);
}

template<class Permit, class Callback>
void ProfileAdministrator::CreateProfileAsync(Registrar &registrar, const std::string &name, const address_t &address, const Permit &auth, const Callback &callback)
{
    CreateProfileAsync(registrar, name, AddressAuthKey(address), auth, callback);
}

template<class Permit, class Callback>
void ProfileAdministrator::set(const std::string &key, const std::string &value, const Permit &auth, const Callback &callback)
{
    std::pair<bool, std::string> result = _key.getAuthData(auth);
    if(!result.first)
    {
        callback(false);
    }
    else
    {
        _profile.setSenderAddress(_key.getAddress());
        _profile.set(key, value, result.second, auth, callback);
    }
}

template<class Permit, class Callback>
void ProfileAdministrator::setPaymentAddress(const address_t &address, const Permit &auth, const Callback &callback)
{
    std::pair<bool, std::string> result = _key.getAuthData(auth);
    if(!result.first)
    {
        callback(false);
    }
    else
    {
        _profile.setSenderAddress(_key.getAddress());
        _profile.setPaymentAddress(address, auth, callback);
    }
}


template<class Key, class Permit>
ProfileAdministrator ProfileAdministrator::CreateProfile(Registrar &registrar, const std::string &name, const Key &key, const Permit &auth)
{
    registrar.setSenderAddress(key.getAddress());
    if(registrar.create(name, key.getAuthData(auth).second, auth))
    {
        return ProfileAdministrator(registrar.get(name), key);
    }
    return ProfileAdministrator(Profile(registrar.getProvider(), ""), key);
}


template<class Key, class Permit, class Callback>
void ProfileAdministrator::CreateProfileAsync(Registrar &registrar, const std::string &name, const Key &key, const Permit &auth, const Callback &callback)
{
    registrar.setSenderAddress(key.getAddress());
    registrar.create(name, key.getAuthData(auth), auth, CreateProfileCallback<Key, Callback>(registrar, name, key, callback));
}


template<class Permit, class Callback>
void ProfileAdministrator::changeAuth(const AddressAuth &authenticator, const Permit &pass, const Callback &callback)
{
    std::pair<bool, std::string> result = _key.getAuthData(pass);
    if(!result.first)
    {
        callback(false);
    }
    else
    {
        _profile.setSenderAddress(_key.getAddress());
        _profile.transfer(authenticator.getAddress(), result.second, pass, ChangeAuthCallback<Callback, AddressAuthKey>(this, AddressAuthKey(authenticator.getSenderAddress()), callback));
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


template<class Permit, class Callback>
ProfileAdministrator::RenameProfileCallback<Permit, Callback>::RenameProfileCallback(Registrar &registrar, ProfileAdministrator *admin, const std::string &name, const Permit &auth, const Callback &callback) :
    _registrar(registrar),
    _admin(admin),
    _name(name),
    _auth(auth),
    _callback(callback)
{}

template<class Permit, class Callback>
void ProfileAdministrator::RenameProfileCallback<Permit, Callback>::operator()(bool result)
{
    if(!result)
    {
        _callback(false);
    }
    else
    {
        std::pair<bool, std::string> result = _admin->_key.getAuthData(_auth);
        if(!result.first)
        {
            _callback(false);
        }
        else
        {
            _registrar.link(_name, _admin->_profile.getAddress(), result.second, _auth, _callback);
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


template<class Permit>
bool ProfileAdministrator::set(const std::string &key, const std::string &value, const Permit &pass)
{
    std::pair<bool, std::string> result = _key.getAuthData(pass);
    if(!result.first)
    {
        return false;
    }
    _profile.setSenderAddress(_key.getAddress());
    return _profile.set(key, value, result.second, pass);
}


template<class Permit>
bool ProfileAdministrator::setPaymentAddress(const address_t &address, const Permit &pass)
{
    return set("payments", address, pass);
}


template<class Permit>
bool ProfileAdministrator::changeAuth(const AddressAuth &authenticator, const Permit &pass)
{
    std::pair<bool, std::string> result = _key.getAuthData(pass);
    if(!result.first)
    {
        return false;
    }
    _profile.setSenderAddress(_key.getAddress());
    if(_profile.transfer(authenticator.getAddress(), result.second, pass))
    {
        _key.reset(AddressAuthKey(authenticator.getSenderAddress()));
        return true;
    }
    return false;
}


template<class Permit>
bool ProfileAdministrator::link(Registrar &registrar, const std::string &name, const Permit &pass)
{
    std::pair<bool, std::string> result = _key.getAuthData(pass);
    if(!result.first)
    {
        return false;
    }
    registrar.setSenderAddress(_key.getAddress());
    return registrar.link(name, _profile.getAddress(), result.second, pass);
}


template<class Permit>
bool ProfileAdministrator::unlink(Registrar &registrar, const Permit &pass)
{
    std::pair<bool, std::string> result = _key.getAuthData(pass);
    if(!result.first)
    {
        return false;
    }
    registrar.setSenderAddress(_key.getAddress());
    return registrar.unlink(_profile.getURI().getName(), result.second, pass);
}


template<class Permit>
bool ProfileAdministrator::move(Registrar &registrar, const std::string &name, const Permit &pass, const BigInt &gas)
{
    std::pair<bool, std::string> result = _key.getAuthData(pass);
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

    Resolver resolver(_profile.getProvider(), registrar.getNetwork());
    Registrar oldRegistrar = resolver.lookupRegistrar(_profile.getURI().getContext());
    std::string oldName = _profile.getURI().getName();

    registrar.setSenderAddress(_key.getAddress());

    if(!registrar.link(name, _profile.getAddress(), result.second, pass))
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

    result = _key.getAuthData(pass);
    oldRegistrar.setSenderAddress(_key.getAddress());

    return oldRegistrar.unlink(oldName, result.second, pass);

}


template<class Permit>
ProfileAdministrator ProfileAdministrator::CreateProfile(Registrar &regisrar, const std::string &name, const address_t &address, const Permit &pass)
{
    return CreateProfile(regisrar, name, AddressAuthKey(address), pass);
}


template<class Permit>
ProfileAdministrator ProfileAdministrator::CreateProfile(Registrar &regisrar, const std::string &name, const Permit &pass)
{
    return CreateProfile(regisrar, name, AddressAuthKey(regisrar.getSenderAddress()), pass);
}

}
