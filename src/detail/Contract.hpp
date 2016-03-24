#pragma once 

#include "ethrpc/Provider.hpp"
#include "ethrpc/Contract.hpp"

#include "types.hpp"


namespace BitProfile{


using Ethereum::Connector::Provider;
using Ethereum::Connector::ContractResult;
using Ethereum::Connector::ContractArguments;


class Contract : public Ethereum::Connector::Contract
{
    public:
        typedef Ethereum::Connector::Contract Base;
        template<class Result> class ResultTypeTag{};

    public:
       Contract(Provider &, const address_t &address);


    protected:

        template<class Result>
        Result call(const char *method);

        template<class Result>
        Result call(const char *method, const ContractArguments &);

        std::string cast(ResultTypeTag<std::string>, ContractResult &);
        bool cast(ResultTypeTag<bool>, ContractResult &);

        using Base::call;
        using Base::execute;

};


}

#include "Contract.ipp"
