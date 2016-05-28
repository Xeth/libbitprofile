#include <iostream>
#include <string>

#include "ethrpc/Provider.hpp"

#include "bitprofile/Resolver.hpp"
#include "bitprofile/GasEstimator.hpp"
#include "bitprofile/ProfileAdministrator.hpp"
#include "bitprofile/ProfileStore.hpp"


using namespace BitProfile;

void printRegisterHelp()
{
    std::cout<<"register [context] [name]"<<std::endl;
}

void printLinkHelp()
{
    std::cout<<"link [context] [name] [profile]"<<std::endl;
}


void printUnlinkHelp()
{
    std::cout<<"unlink [context] [profile]"<<std::endl;
}

void printEditHelp()
{
    std::cout<<"edit [uri] [key] [value]"<<std::endl;
}

void printHelp()
{
    std::cout<<"usage : [operation] [params]"<<std::endl<<std::flush;
    std::cout<<"operations : "<<std::endl;
    printRegisterHelp();
    printLinkHelp();
    printUnlinkHelp();
    printEditHelp();
}

void printInvalidArgs()
{
    std::cout<<"invalid arguments, usage: ";
}

template<class BigInt>
void printGas(const BigInt &gas)
{
    std::cout<<"gas : "<<std::dec<<gas<<std::endl;
}

int main(int argc, char **argv)
{

    if(argc<2)
    {
        printHelp();
        return 1;
    }

    std::string command(argv[1]);

    Ethereum::Connector::Provider provider;
    provider.connect(Ethereum::Connector::Test_Net);

    Resolver resolver(provider, Test_Net);
    ProfileStore store(Test_Net);
    GasEstimator estimator(provider);


    if(command=="register")
    {
        if(argc<4)
        {
            printInvalidArgs();
            printRegisterHelp();
            return 1;
        }
        Registrar registrar = resolver.lookupRegistrar(argv[2]);
        printGas(estimator.estimateRegister(registrar, argv[3]));
    }
    else
    if(command=="link")
    {
        if(argc<5)
        {
            printInvalidArgs();
            printLinkHelp();
            return 1;
        }
        Registrar registrar = resolver.lookupRegistrar(argv[2]);
        ProfileAdministrator admin = ProfileAdministrator::FromDescriptor(provider, *store.find(argv[4]));
        printGas(estimator.estimateLink(registrar, admin, argv[3]));
    }
    else
    if(command=="unlink")
    {
        if(argc<4)
        {
            printInvalidArgs();
            printUnlinkHelp();
            return 1;
        }
        Registrar registrar = resolver.lookupRegistrar(argv[2]);
        ProfileAdministrator admin = ProfileAdministrator::FromDescriptor(provider, *store.find(argv[3]));
        printGas(estimator.estimateUnlink(registrar, admin));
    }
    else
    if(command=="edit")
    {
        if(argc<5)
        {
            printInvalidArgs();
            printEditHelp();
            return 1;
        }
        ProfileAdministrator admin = ProfileAdministrator::FromDescriptor(provider, *store.find(argv[2]));
        printGas(estimator.estimateEdit(admin, argv[3], argv[4]));
    }
    else
    {
        std::cout<<"invalid command "<<std::endl;
        printHelp();
    }

    return 0;
}
