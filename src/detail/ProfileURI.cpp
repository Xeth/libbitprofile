#include "ProfileURI.hpp"


namespace BitProfile{


ProfileURI::ProfileURI()
{}


ProfileURI::ProfileURI(const RegistrarURI &registrar, const std::string &name) :
    _registrar(registrar),
    _name(name)
{}



bool ProfileURI::operator == (const ProfileURI &uri) const
{
    return _registrar==uri._registrar && _name == uri._name;
}


const std::string & ProfileURI::getName() const
{
    return _name;
}


std::string ProfileURI::getContext() const
{
    return _registrar.toString();
}

std::string ProfileURI::toString() const
{
    std::string result;
    result = _registrar.toString();
    if(result.size())
    {
        result += ':';
    }
    result += _name;
    return result;
}


}
