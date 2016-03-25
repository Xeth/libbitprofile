#pragma once

#include <boost/iterator/iterator_facade.hpp>
#include "RegistrarURI.hpp"


namespace BitProfile{



class RegistrarURIListIterator;


class RegistrarURIList
{
    public:
        typedef RegistrarURIListIterator Iterator;

    public:
        RegistrarURIList(size_t);

        Iterator begin() const;
        Iterator end() const;

    private:
        size_t _size;
};



}

#include "RegistrarURIList.ipp"
