#pragma once

#include "ethrpc/ContractFactory.hpp"

#include "ContractCode.hpp"
#include "types.hpp"


namespace BitProfile{


using Ethereum::Connector::Provider;


template<class Contract>
class ContractFactory : public Ethereum::Connector::ContractFactory
{
    public:
        typedef Ethereum::Connector::ContractFactory Base;
        typedef Ethereum::Connector::Contract BaseContract;

    public:

        ContractFactory(Provider &,  const char *code);

        Contract at(const address_t &address);

        Contract deploy();
        Contract deploy(const arguments_t &);

        template<class CallBack>
        void deploy(const CallBack &);

        template<class CallBack>
        void deploy(const arguments_t &, const CallBack &);

    private:
        Contract cast(const BaseContract &);

        using Base::deploy;
        using Base::at;

    private:
        template<class CallBack>
        class CallBackWrapper;

    private:
        Provider &_provider;
        const char * _code;
};


template<class Contract>
template<class CallBack>
class ContractFactory<Contract>::CallBackWrapper
{
    public:
        CallBackWrapper(const CallBack &, ContractFactory &);

        void operator()(const boost::system::error_code &);
        void operator()(const ContractFactory::BaseContract &);

    private:
        CallBack _callback;
        ContractFactory &_factory;
};


#define DECLARE_CONTRACT_FACTORY(ClassName, ContractName, ContractCode)       \
class ClassName : public ContractFactory<ContractName>                        \
{                                                                             \
    public:                                                                   \
        typedef ContractFactory<ContractName> Base;                           \
                                                                              \
    public:                                                                   \
        inline ClassName(Provider &provider) : Base(provider, ContractCode)   \
        {}                                                                    \
}


}

#include "ContractFactory.ipp"
