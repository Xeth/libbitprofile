#pragma once 

#include <boost/shared_ptr.hpp>
#include "types.hpp"
#include "KeyTypeName.hpp"

namespace BitProfile{


class KeyAdapter
{
    public:
        template<class Key>
        KeyAdapter(const Key &);

        const address_t & getAddress() const;
        std::pair<bool, std::string> getAuthData(const std::string &password);

        std::string getTypeName() const;

        template<class Key>
        void reset(const Key &);

        template<class Key>
        void operator = (const Key &);

    private:
        class KeyHolder;
        template<class Key> class KeyHolderImpl;

    private:
        boost::shared_ptr<KeyHolder> _holder;
};


}

#include "KeyAdapter.ipp"
