#include "RegistrarURI.hpp"


namespace BitProfile{


RegistrarURI::RegistrarURI() : 
    _index(0)
{}


RegistrarURI::RegistrarURI(size_t index) :
    _index(index)
{}


bool RegistrarURI::operator == (const RegistrarURI &uri) const
{
    return _index == uri._index;
}


std::string RegistrarURI::toString() const
{
    //ToDo : optimize it
    return std::string("b") + boost::lexical_cast<std::string>(_index);
}


}
