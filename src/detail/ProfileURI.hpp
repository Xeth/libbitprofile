#pragma once

#include <string>
#include "RegistrarURI.hpp"


namespace BitProfile{


class ProfileURI
{
    public:
        ProfileURI();
        ProfileURI(const RegistrarURI &, const std::string &name);


        bool operator == (const ProfileURI &) const;
        std::string toString() const;

    private:
        RegistrarURI _registrar;
        std::string _name;
};


}
