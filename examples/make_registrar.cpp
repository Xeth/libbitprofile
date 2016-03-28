
#include <iostream>

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "bitprofile/MasterRegistrar.hpp"

#include "utils/UnlockAccount.hpp"

int main(int argc, char **argv)
{


    Ethereum::Connector::Provider provider;
    provider.connect();
    UnlockAccount(provider);

    BitProfile::MasterRegistrar registrar(provider, BitProfile::Test_Net);

    std::cout<<"creating registrar : "<<registrar.create()<<std::endl;
    std::cout<<"beta : "<<registrar.isBeta()<<std::endl;
    std::cout<<"size : "<<registrar.getSize()<<std::endl;

    return 0;
}

