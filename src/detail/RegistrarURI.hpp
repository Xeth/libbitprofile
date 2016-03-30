#pragma once

#include <string>
#include <boost/lexical_cast.hpp>


namespace BitProfile{



class RegistrarURI
{
    public:
        RegistrarURI();
        RegistrarURI(size_t);

        bool operator == (const RegistrarURI &) const;
        std::string toString() const;
        size_t getIndex() const;

    private:
        size_t _index;
};


}
