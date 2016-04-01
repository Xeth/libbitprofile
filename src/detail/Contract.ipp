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
    return !getAddress().size();
}


inline Provider & Contract::getProvider()
{
    return _provider;
}

template<class CheckCallback>
bool Contract::executeConfirm(const char *method, const CheckCallback &check)
{
    _lastTransaction = execute(method);
    return _observer.watch(_lastTransaction) && check();
}

template<class CheckCallback>
bool Contract::executeConfirm(const char *method, const ContractArguments &args, const CheckCallback &check)
{
    _lastTransaction = execute(method, args);
    return _observer.watch(_lastTransaction) && check();
}

template<class CheckCallback, class Callback>
void Contract::executeConfirm(const char *method, const ContractArguments &args, const CheckCallback &check, const Callback &callback)
{
    _lastTransaction = execute(method, args);
    _observer.watch(_lastTransaction, ConfirmCallbackDelegate<CheckCallback, Callback>(check, callback));
}

template<class CheckCallback, class Callback>
void Contract::executeConfirm(const char *method, const CheckCallback &check, const Callback &callback)
{
    _lastTransaction = execute(method);
    _observer.watch(_lastTransaction, ConfirmCallbackDelegate<CheckCallback, Callback>(check, callback));
}


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
