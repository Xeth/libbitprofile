namespace BitProfile{


inline Contract::Contract(Provider &provider, const address_t &address) : 
    Base(provider, address)
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



}
