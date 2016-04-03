namespace BitProfile{


template<class Contract>
ContractFactory<Contract>::ContractFactory(Provider &provider, const std::string &code) :
    Base(provider),
    _provider(provider),
    _code(code)
{}


template<class Contract>
Contract ContractFactory<Contract>::at(const address_t &address)
{
    return Contract(_provider, address);
}


template<class Contract>
Contract ContractFactory<Contract>::deploy()
{
    return cast(Base::deploy(_code));
}


template<class Contract>
Contract ContractFactory<Contract>::deploy(const arguments_t &args)
{
    return cast(Base::deploy(_code, args));
}


template<class Contract>
template<class CallBack>
void ContractFactory<Contract>::deploy(const CallBack &callback)
{
    Base::deploy(_code, CallBackWrapper<CallBack>(callback, *this));
}


template<class Contract>
template<class CallBack>
void ContractFactory<Contract>::deploy(const arguments_t &args, const CallBack &callback)
{
    Base::deploy(_code, args, CallBackWrapper<CallBack>(callback, *this));
}


template<class Contract>
Contract ContractFactory<Contract>::cast(const BaseContract &contract)
{
    return Contract(_provider, contract.getAddress());
}


template<class Contract>
template<class CallBack>
ContractFactory<Contract>::CallBackWrapper<CallBack>::CallBackWrapper(const CallBack &callback, ContractFactory<Contract> &factory) :
    _callback(callback),
    _factory(factory)
{}


template<class Contract>
template<class CallBack>
void ContractFactory<Contract>::CallBackWrapper<CallBack>::operator()(const boost::system::error_code &ec)
{
    _callback(ec);
}


template<class Contract>
template<class CallBack>
void ContractFactory<Contract>::CallBackWrapper<CallBack>::operator()(const ContractFactory<Contract>::BaseContract &base)
{
    Contract contract = _factory.cast(base);
    _callback(contract);
}




}
