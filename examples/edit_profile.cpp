
#include <iostream>

#include "ethrpc/Provider.hpp"
#include "bitprofile/Resolver.hpp"

#include "utils/UnlockAccount.hpp"

int main(int argc, char **argv)
{
    if(argc<4)
    {
        std::cout<<"usage : edit_profile [uri] [key] [value]"<<std::endl;
        return 1;
    }

    Ethereum::Connector::Provider provider;
    provider.connect();
    UnlockAccount(provider);

    BitProfile::Resolver resolver(provider, BitProfile::MasterRegistrar::Test_Net);
    BitProfile::Profile profile = resolver.lookupProfile(argv[1]);

    if(profile.isNull())
    {
        std::cout<<"profile not found"<<std::endl;
    }
    else
    {
        std::cout<<"profile found : "<<profile.getAddress()<<std::endl;
        std::cout<<"uri : "<<argv[1]<<std::endl;
        std::cout<<"edit : "<<profile.set(argv[2], argv[3])<<std::endl;
        std::cout<<"profile data["<<argv[2]<<"]="<<profile.get(argv[2])<<std::endl;
    }




    return 0;
}

