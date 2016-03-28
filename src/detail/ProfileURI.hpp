#pragma once

#include <string>
#include "RegistrarURI.hpp"


namespace BitProfile{


class ProfileURI
{
    public:
        ProfileURI();
        ProfileURI(const RegistrarURI &, const std::string &name);
        const std::string & getName() const;
        std::string getContext() const;

        bool operator == (const ProfileURI &) const;
        std::string toString() const;

    private:
        RegistrarURI _registrar;
        std::string _name;
};


}
