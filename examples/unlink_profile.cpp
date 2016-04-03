
#include <iostream>

#include "ethrpc/Provider.hpp"
#include "bitprofile/Resolver.hpp"

#include "utils/UnlockAccount.hpp"

int main(int argc, char **argv)
{
    if(argc<2)
    {
        std::cout<<"usage : unlink_profile [uri]"<<std::endl;
        return 1;
    }

    Ethereum::Connector::Provider provider;
    provider.connect();
    UnlockAccount(provider);

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
        BitProfile::Registrar registrar = resolver.lookupRegistrar(profile.getURI().getContext());
        if(registrar.isNull())
        {
            std::cout<<"registrar not found"<<std::endl;
            return 1;
        }

        bool result = registrar.unlink(profile.getURI().getName(), "");
        std::cout<<"ulink : "<<result;

    }




    return 0;
}

