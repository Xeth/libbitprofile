
#include <iostream>

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "bitprofile/MasterRegistrar.hpp"

#include "utils/PromptPassword.hpp"

int main(int argc, char **argv)
{


    Ethereum::Connector::Provider provider;
    provider.connect(Ethereum::Connector::Test_Net);
    std::string password = PromptPassword();
    BitProfile::MasterRegistrar registrar(provider, BitProfile::Test_Net);

    std::cout<<"creating registrar : "<<registrar.create(password)<<std::endl;
    std::cout<<"beta : "<<registrar.isBeta()<<std::endl;
    std::cout<<"size : "<<registrar.getSize()<<std::endl;

    return 0;
}

