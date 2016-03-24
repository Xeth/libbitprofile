#pragma once 

#include "ethrpc/Provider.hpp"
#include "ethrpc/Contract.hpp"
#include "ethrpc/TransactionObserver.hpp"

#include "types.hpp"


namespace BitProfile{



template<class CheckCallback, class Callback>
class ConfirmCallbackDelegate
{
    public:
        ConfirmCallbackDelegate(const CheckCallback &,  const Callback &);
        void operator()(bool confirmed);

    private:
        CheckCallback _check;
        Callback _callback;
};


class Contract : public Ethereum::Connector::Contract
{
    public:
        typedef Ethereum::Connector::Contract Base;
        template<class Result> class ResultTypeTag{};

    public:
       Contract(Provider &, const address_t &address);


    protected:

        template<class CheckCallback>
        bool executeConfirm(const char *, const ContractArguments &, const CheckCallback &);

        template<class CheckCallback>
        bool executeConfirm(const char *, const CheckCallback &);

        template<class CheckCallback, class Callback>
        void executeConfirm(const char *, const ContractArguments &, const CheckCallback &, const Callback &);

        template<class CheckCallback, class Callback>
        void executeConfirm(const char *, const CheckCallback &, const Callback &);

        template<class Result>
        Result call(const char *method);

        template<class Result>
        Result call(const char *method, const ContractArguments &);

        std::string cast(ResultTypeTag<std::string>, ContractResult &);
        bool cast(ResultTypeTag<bool>, ContractResult &);
        uint256_t cast(ResultTypeTag<uint256_t>, ContractResult &);

        Provider & getProvider();
        bool isNull() const;

        using Base::call;
        using Base::execute;

    private:
        TransactionObserver _observer;
        Provider &_provider;
};


}

#include "Contract.ipp"
