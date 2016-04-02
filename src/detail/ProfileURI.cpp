#include "ProfileURI.hpp"


namespace BitProfile{


ProfileURI::ProfileURI()
{}


ProfileURI::ProfileURI(const RegistrarURI &registrar, const std::string &name) :
    _context(registrar.toString()),
    _name(name)
{}

ProfileURI::ProfileURI(const std::string &context, const std::string &name) :
    _context(context),
    _name(name)
{}


bool ProfileURI::operator == (const ProfileURI &uri) const
{
    return _context==uri._context && _name == uri._name;
}


const std::string & ProfileURI::getName() const
{
    return _name;
}


std::string ProfileURI::getContext() const
{
    return _context;
}

std::string ProfileURI::toString() const
{
    std::string result;
    result = _context;
    if(result.size())
    {
        result += ':';
    }
    result += _name;
    return result;
}


}
