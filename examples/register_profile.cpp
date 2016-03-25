
#include <iostream>

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "bitprofile/MasterRegistrar.hpp"

#include "utils/UnlockAccount.hpp"

int main(int argc, char **argv)
{
    if(argc<3)
    {
        std::cout<<"usage : register_profile [context] [name]"<<std::endl;
        return 1;
    }

    Ethereum::Connector::Provider provider;
    provider.connect();
    UnlockAccount(provider);

    BitProfile::MasterRegistrar master(provider, BitProfile::MasterRegistrar::Test_Net);

    std::cout<<"beta : "<<master.isBeta()<<std::endl;
    std::cout<<"master size : "<<master.getSize()<<std::endl;

    BitProfile::Registrar regisrar = master.get(boost::lexical_cast<size_t>(argv[1]));
    if(regisrar.isNull())
    {
        std::cout<<"invalid registrar : "<<argv[1]<<std::endl;
        return 2;
    }

    if(!regisrar.create(argv[2]))
    {
        std::cout<<"failed to register profile"<<std::endl;
    }
    else
    {
        std::cout<<"profile registered"<<std::endl;
    }

    BitProfile::Profile profile = regisrar.get(argv[2]);

    std::cout<<"profile registered : "<<profile.getAddress()<<std::endl;
    std::cout<<"name : "<<argv[2]<<std::endl;

    return 0;
}

