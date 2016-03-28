
#include <iostream>

#include "ethrpc/Provider.hpp"
#include "bitprofile/MasterRegistrar.hpp"


using namespace BitProfile;


int main(int argc, char **argv)
{

    Ethereum::Connector::Provider provider;
    provider.connect();

    MasterRegistrar registrar(provider, BitProfile::Test_Net);
    MasterRegistrar::URIList list = registrar.getURIList();

    std::cout<<"registrars : "<<std::endl;
    for(MasterRegistrar::URIList::Iterator it = list.begin(), end = list.end(); it!=end; ++it)
    {
        std::cout<<"* "<<it->toString()<<std::endl;
    }

    std::cout<<std::endl;

    return 0;
}

