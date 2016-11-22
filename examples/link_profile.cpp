
#include <iostream>

#include "ethrpc/Provider.hpp"
#include "bitprofile/Resolver.hpp"

#include "utils/PromptPassword.hpp"

int main(int argc, char **argv)
{
    if(argc<4)
    {
        std::cout<<"usage : edit_profile [uri] [registrar] [name]"<<std::endl;
        return 1;
    }

    Ethereum::Connector::Provider provider;
    provider.connect(Ethereum::Connector::Test_Net);
    std::string password = PromptPassword();
    BitProfile::Resolver resolver(provider, BitProfile::Test_Net);
    BitProfile::Profile profile = resolver.lookupProfile(argv[1]);

    if(profile.isNull())
    {
        std::cout<<"profile not found"<<std::endl;
    }
    else
    {
        std::cout<<"profile found : "<<profile.getAddress()<<std::endl;
        std::cout<<"uri : "<<argv[1]<<std::endl;
        bool auth = profile.authenticate(profile.getSenderAddress(), BitProfile::Auth::Owner);
        std::cout<<"auth : "<<auth<<std::endl<<std::flush;
        BitProfile::Registrar registrar = resolver.lookupRegistrar(argv[2]);
        if(registrar.isNull())
        {
            std::cout<<"registrar not found"<<std::endl;
            return 1;
        }

        bool result = registrar.link(argv[3], profile.getAddress(), "", password);
        std::cout<<"link : "<<result;

    }




    return 0;
}

