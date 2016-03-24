#pragma once 

#include <stdexcept>

#include "PromptPassword.hpp"
#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"


inline void UnlockAccount(Ethereum::Connector::Provider &provider)
{
    std::string password = PromptPassword();

    Ethereum::Connector::Wallet wallet(provider);
    if(!wallet.unlockAccount(wallet.getCoinBase(), password))
    {
        std::cout<<"failed to unlock default account"<<std::endl<<std::flush;
        throw std::runtime_error("unlock failed");
    }
}

