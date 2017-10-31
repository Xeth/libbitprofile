#pragma once

#include "ethrpc/GasEstimator.hpp"
#include "abi/ContractConstructor.hpp"
#include "abi/Method.hpp"

#include "Network.hpp"
#include "Registrar.hpp"
#include "Profile.hpp"
#include "ProfileAdministrator.hpp"

#include "detail/types.hpp"
#include "detail/defines.hpp"
#include "detail/ContractCode.hpp"


namespace BitProfile{



class GasEstimator
{

    public:

        GasEstimator(Ethereum::Connector::Provider &);

        BigInt estimateRegister(const Registrar &, const std::string &name);
        BigInt estimateEdit(const ProfileAdministrator &, const std::string &key, const std::string &value);
        BigInt estimateUnlink(const Registrar &, const ProfileAdministrator &);
        BigInt estimateLink(const Registrar &, const ProfileAdministrator &, const std::string &name);


    private:
        BigInt estimateRegister(const std::string &name, const char *registrarAddress, const char *factoryAddress, const char *sender);
        BigInt estimateEdit(const std::string &name, const std::string &value, const char *profile, const char *sender);
        BigInt estimateLink(const std::string &name, const address_t &address, const char *registrar, const char *sender);
        BigInt estimateUnlink(const std::string &name, const char *registrar, const char *sender, const char *auth);

    private:
        typedef Ethereum::ABI::Method Method;
        typedef Ethereum::ABI::ContractConstructor ContractConstructor;

    private:
        Ethereum::Connector::GasEstimator _estimator;
};


}
