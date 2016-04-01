
#include <iostream>

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "bitprofile/MasterRegistrar.hpp"
#include "bitprofile/ProfileAdministrator.hpp"
#include "bitprofile/ProfileStore.hpp"
#include "utils/PromptPassword.hpp"

int main(int argc, char **argv)
{
    if(argc<3)
    {
        std::cout<<"usage : register_profile [context] [name]"<<std::endl;
        return 1;
    }

    Ethereum::Connector::Provider provider;
    provider.connect();
    std::string password = PromptPassword();

    BitProfile::MasterRegistrar master(provider, BitProfile::Test_Net);

    std::cout<<"beta : "<<master.isBeta()<<std::endl;
    std::cout<<"master size : "<<master.getSize()<<std::endl;

    BitProfile::Registrar regisrar = master.get(boost::lexical_cast<size_t>(argv[1]));
    if(regisrar.isNull())
    {
        std::cout<<"invalid registrar : "<<argv[1]<<std::endl;
        return 2;
    }

    BitProfile::ProfileAdministrator profile = BitProfile::ProfileAdministrator::CreateProfile(regisrar, argv[2], password);

    if(profile.isNull())
    {
        std::cout<<"failed to register profile"<<std::endl;
    }
    else
    {
        std::cout<<"profile registered"<<std::endl;
        BitProfile::ProfileStore store(BitProfile::Test_Net);
        if(store.insert(BitProfile::ProfileDescriptor(profile)))
        {
            std::cout<<"profile saved"<<std::endl;
        }
        else
        {
            std::cout<<"failed to save profile"<<std::endl;
        }
    }


    return 0;
}

