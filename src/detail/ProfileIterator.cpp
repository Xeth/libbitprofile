#include "ProfileIterator.hpp"


namespace BitProfile{


ProfileIterator::ProfileIterator()
{}


ProfileIterator::ProfileIterator(fs::directory_iterator it) : 
    Base(it)
{}


fs::path ProfileIterator::path() const
{
    return base()->path();
}


ProfileDescriptor ProfileIterator::dereference() const
{
    std::ifstream stream(base()->path().string().c_str());
    if(!stream)
    {
        throw std::runtime_error("failed to read file");
    }
    ProfileDescriptor descriptor;
    stream >> descriptor;
    stream.close();
    return descriptor;
}


}
