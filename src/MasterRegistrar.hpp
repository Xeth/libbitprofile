#pragma once


#include "detail/Contract.hpp"
#include "detail/defines.hpp"

#include "Registrar.hpp"


namespace BitProfile{


class MasterRegistrar : public Contract
{
    public:
        enum Network
        {
            Test_Net,
            Main_Net
        };

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

    private:
        bool checkRegistrar(size_t index);
};


}

#include "MasterRegistrar.ipp"
