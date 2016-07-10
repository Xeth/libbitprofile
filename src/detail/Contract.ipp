namespace BitProfile{



inline Contract::Contract(Provider &provider, const address_t &address) : 
    Base(provider, address),
    _observer(provider),
    _provider(provider)
{
    setGasLimit(uint256_t(4300000));
}


inline const txid_t & Contract::getLastTransaction() const
{
    return _lastTransaction;
}


template<class Result, DataType type>
Result Contract::call(const char *method) const
{
    ContractResult result = Base::call(method);
    return cast(ResultTypeTag<Result, type>(), result);
}


template<class Result, DataType type>
Result Contract::call(const char *method, const ContractArguments &args) const
{
    ContractResult result = Base::call(method, args);
    return cast(ResultTypeTag<Result, type>(), result);
}


inline std::string Contract::cast(ResultTypeTag<std::string, String_Type>, ContractResult &result) const
{
    return result.toString();
}

inline uint256_t Contract::cast(ResultTypeTag<uint256_t, Uint_Type>, ContractResult &result) const
{
    return result.toUint();
}


inline address_t Contract::cast(ResultTypeTag<address_t, Address_Type>, ContractResult &result) const
{
    return result.toAddress();
}


inline bool Contract::cast(ResultTypeTag<bool, Bool_Type>, ContractResult &result) const
{
    return result.toBool();
}


inline bool Contract::isNull() const
{
    const std::string & address = getAddress();
    return !address.size()||address=="0000000000000000000000000000000000000000";
}


inline Provider & Contract::getProvider()
{
    return _provider;
}


template<class CheckCallback>
inline bool Contract::watch(const std::string &txid, const CheckCallback &check)
{
    _lastTransaction = txid;
    return _observer.watch(_lastTransaction) && check();
}


template<class CheckCallback>
bool Contract::executeConfirm(const char *method, const std::string &password, const CheckCallback &check)
{
    return watch(execute(method, password), check);
}

template<class CheckCallback>
bool Contract::executeConfirm(const char *method, const ContractArguments &args, const std::string &password, const CheckCallback &check)
{
    return watch(execute(method, args, password), check);
}

template<class CheckCallback, class Callback>
void Contract::executeConfirm(const char *method, const ContractArguments &args, const std::string &password, const CheckCallback &check, const Callback &callback)
{
    return watch(execute(method, args, password), ConfirmCallbackDelegate<CheckCallback, Callback>(check, callback));
}

template<class CheckCallback, class Callback>
void Contract::executeConfirm(const char *method, const std::string &password, const CheckCallback &check, const Callback &callback)
{
    return watch(execute(method, password), ConfirmCallbackDelegate<CheckCallback, Callback>(check, callback));
}


//
template<class CheckCallback>
bool Contract::executeConfirm(const char *method, const Auth &auth, const CheckCallback &check)
{
    return watch(execute(method, auth), check);
}

template<class CheckCallback>
bool Contract::executeConfirm(const char *method, const ContractArguments &args, const Auth &auth, const CheckCallback &check)
{
    return watch(execute(method, args, auth), check);
}

template<class CheckCallback, class Callback>
void Contract::executeConfirm(const char *method, const ContractArguments &args, const Auth &auth, const CheckCallback &check, const Callback &callback)
{
    return watch(execute(method, args, auth), ConfirmCallbackDelegate<CheckCallback, Callback>(check, callback));
}

template<class CheckCallback, class Callback>
void Contract::executeConfirm(const char *method, const Auth &auth, const CheckCallback &check, const Callback &callback)
{
    return watch(execute(method, auth), ConfirmCallbackDelegate<CheckCallback, Callback>(check, callback));
}
//


template<class CheckCallback, class Callback>
ConfirmCallbackDelegate<CheckCallback, Callback>::ConfirmCallbackDelegate(const CheckCallback &check, const Callback &callback) :
    _check(check),
    _callback(callback)
{}

template<class CheckCallback, class Callback>
void ConfirmCallbackDelegate<CheckCallback, Callback>::operator()(bool confirmed)
{
    if(!confirmed)
    {
        _callback(false);
    }
    else
    {
        _callback(_check());
    }
}


}
