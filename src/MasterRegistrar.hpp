#pragma once


#include "detail/Contract.hpp"
#include "detail/defines.hpp"
#include "detail/RegistrarURI.hpp"
#include "detail/RegistrarURIList.hpp"

#include "Registrar.hpp"
#include "Network.hpp"


namespace BitProfile{


class MasterRegistrar : public Contract
{
    public:
        typedef RegistrarURIList URIList;

    public:
        MasterRegistrar(Provider &);
        MasterRegistrar(Provider &, Network);
        MasterRegistrar(Provider &, const address_t &);

        Registrar get(size_t index);
        bool isBeta();
        size_t getSize();

        bool create();

        template<class Callback>
        void create(const Callback &);

        URIList getURIList();

    private:
        bool checkRegistrar(size_t index);
};


}

#include "MasterRegistrar.ipp"
