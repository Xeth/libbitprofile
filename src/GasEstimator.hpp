#pragma once

#include "ethrpc/GasEstimator.hpp"
#include "ethrpc/abi/ContractConstructor.hpp"
#include "ethrpc/abi/Method.hpp"

#include "Network.hpp"
#include "detail/types.hpp"
#include "detail/defines.hpp"
#include "detail/ContractCode.hpp"


namespace BitProfile{



class GasEstimator
{
    public:
        typedef Ethereum::Connector::BigInt BigInt;

    public:

        GasEstimator(Ethereum::Connector::Provider &, Network);

        BigInt estimateRegister(const std::string &name);
        BigInt estimateEdit(const std::string &key, const std::string &value);
        BigInt estimateUnlink(const std::string &name);
        BigInt estimateLink(const std::string &name, const address_t &address);

    private:
        BigInt estimateRegister(const std::string &name, const char *registrarAddress, const char *factoryAddress);
        BigInt estimateEdit(const std::string &name, const std::string &value, const char *address);
        BigInt estimateLink(const std::string &name, const address_t &address, const char *registrar );
        BigInt estimateUnlink(const std::string &name, const char *registrar);

    private:
        typedef Ethereum::ABI::Method Method;
        typedef Ethereum::ABI::ContractConstructor ContractConstructor;

    private:
        Ethereum::Connector::GasEstimator _estimator;
        const Network _network;
};


}
