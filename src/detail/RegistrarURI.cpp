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
    std::string result = boost::lexical_cast<std::string>(_index);
    if(result.size()<3)
    {
        result.insert(0, 3-result.size(), '0');
    }
    result.insert(0,1,'b');
    return result;
}

size_t RegistrarURI::getIndex() const
{
    return _index;
}


}
