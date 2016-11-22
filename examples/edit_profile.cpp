
#include <iostream>

#include "ethrpc/Provider.hpp"
#include "bitprofile/Resolver.hpp"
#include "utils/PromptPassword.hpp"

int main(int argc, char **argv)
{
    if(argc<4)
    {
        std::cout<<"usage : edit_profile [uri] [key] [value]"<<std::endl;
        return 1;
    }

    std::string password = PromptPassword();

    Ethereum::Connector::Provider provider;
    provider.connect(Ethereum::Connector::Test_Net);

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
        std::cout<<"edit : "<<profile.set(argv[2], argv[3], "", password)<<std::endl;
        std::cout<<"profile data["<<argv[2]<<"]="<<profile.get(argv[2])<<std::endl;
    }




    return 0;
}

