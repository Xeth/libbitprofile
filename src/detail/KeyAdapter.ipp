namespace BitProfile{



class KeyAdapter::KeyHolder
{
    public:
        virtual const address_t & getAddress() const = 0;
        virtual std::string getTypeName() const = 0;
        virtual std::pair<bool, std::string> getAuthData(const std::string &password) = 0;
};


template<class Key>
class KeyAdapter::KeyHolderImpl : public KeyAdapter::KeyHolder
{
    public:
        KeyHolderImpl(const Key &);

        std::string getTypeName() const;
        const address_t & getAddress() const;
        std::pair<bool, std::string> getAuthData(const std::string &password);

    private:
        Key _key;
};


template<class Key>
KeyAdapter::KeyHolderImpl<Key>::KeyHolderImpl(const Key &key) :
    _key(key)
{}


template<class Key>
const address_t & KeyAdapter::KeyHolderImpl<Key>::getAddress() const
{
    return _key.getAddress();
}


template<class Key>
std::pair<bool, std::string> KeyAdapter::KeyHolderImpl<Key>::getAuthData(const std::string &password)
{
    return _key.getAuthData(password);
}


template<class Key>
std::string KeyAdapter::KeyHolderImpl<Key>::getTypeName() const
{
    return KeyTypeName<Key>();
}


template<class Key>
KeyAdapter::KeyAdapter(const Key &key) :
    _holder(new KeyHolderImpl<Key>(key))
{}

template<class Key>
void KeyAdapter::reset(const Key &key)
{
    _holder.reset(new KeyHolderImpl<Key>(key));
}


template<class Key>
void KeyAdapter::operator = (const Key &key)
{
    _holder.reset(new KeyHolderImpl<Key>(key));
}





}
