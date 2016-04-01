#pragma once 

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

enum DataType{String_Type, Uint_Type, Bool_Type, Int_Type, Address_Type};




class Contract : public Ethereum::Connector::Contract
{
    public:
        

    public:
       Contract(Provider &, const address_t &address);

        bool isNull() const;
        Provider & getProvider();

        const txid_t & getLastTransaction() const;

    private:
        typedef Ethereum::Connector::Contract Base;
        template<class Result, DataType type> class ResultTypeTag{};

    protected:

        template<class CheckCallback>
        bool executeConfirm(const char *, const ContractArguments &, const CheckCallback &);

        template<class CheckCallback>
        bool executeConfirm(const char *, const CheckCallback &);

        template<class CheckCallback, class Callback>
        void executeConfirm(const char *, const ContractArguments &, const CheckCallback &, const Callback &);

        template<class CheckCallback, class Callback>
        void executeConfirm(const char *, const CheckCallback &, const Callback &);

        template<class Result, DataType type>
        Result call(const char *method) const;

        template<class Result, DataType type>
        Result call(const char *method, const ContractArguments &) const;

        std::string cast(ResultTypeTag<std::string, String_Type>, ContractResult &) const;
        bool cast(ResultTypeTag<bool, Bool_Type>, ContractResult &) const;
        uint256_t cast(ResultTypeTag<uint256_t, Uint_Type>, ContractResult &) const;
        address_t cast(ResultTypeTag<address_t, Address_Type>, ContractResult &) const;


        using Base::call;
        using Base::execute;

    private:
        TransactionObserver _observer;
        Provider &_provider;
        txid_t _lastTransaction;
};





}

#include "Contract.ipp"
