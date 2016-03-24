namespace BitProfile{


inline Contract::Contract(Provider &provider, const address_t &address) : 
    Base(provider, address),
    _observer(provider)
{}


template<class Result>
Result Contract::call(const char *method)
{
    ContractResult result = Base::call(method);
    return cast(ResultTypeTag<Result>(), result);
}


template<class Result>
Result Contract::call(const char *method, const ContractArguments &args)
{
    ContractResult result = Base::call(method, args);
    return cast(ResultTypeTag<Result>(), result);
}


inline std::string Contract::cast(ResultTypeTag<std::string>, ContractResult &result)
{
    return result.toString();
}


inline bool Contract::cast(ResultTypeTag<bool>, ContractResult &result)
{
    return result.toBool();
}


template<class CheckCallback>
bool Contract::executeConfirm(const char *method, const CheckCallback &check)
{
    txid_t txid = execute(method);
    return _observer.watch(txid) && check();
}

template<class CheckCallback>
bool Contract::executeConfirm(const char *method, const ContractArguments &args, const CheckCallback &check)
{
    txid_t txid = execute(method, args);
    return _observer.watch(txid) && check();
}

template<class CheckCallback, class Callback>
void Contract::executeConfirm(const char *method, const ContractArguments &args, const CheckCallback &check, const Callback &callback)
{
    txid_t txid = execute(method, args);
    _observer.watch(txid, ConfirmCallbackDelegate<CheckCallback, Callback>(check, callback));
}

template<class CheckCallback, class Callback>
void Contract::executeConfirm(const char *method, const CheckCallback &check, const Callback &callback)
{
    txid_t txid = execute(method);
    _observer.watch(txid, ConfirmCallbackDelegate<CheckCallback, Callback>(check, callback));
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
